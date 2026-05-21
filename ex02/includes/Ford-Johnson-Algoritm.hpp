#pragma once

#include <iterator>
#include <vector>
#include <algorithm>

template <typename Iterator, typename T, typename Compare>
Iterator
StrideLowerBound
(Iterator first, Iterator last, const T& value, std::size_t step, Compare comp)
{
    typedef typename std::iterator_traits<Iterator>::difference_type diff_t;
    diff_t total = std::distance(first, last);
    diff_t count = total / step;
    diff_t lo = 0, hi = count;

    while (lo < hi) {
        diff_t mid = lo + (hi - lo) / 2;
        Iterator Candidate = first;
        std::advance(Candidate, mid * step + (step - 1));  // offset n-1
        if (comp(*Candidate, value)) lo = mid + 1;
        else hi = mid;
    }

    Iterator result = first;
    if (lo < count) std::advance(result, lo * step); // si entre 0 et count alors retourner le debut du block
    else result = last;  // sinon tous les représentants étaient < value

    return result;
}

// INFO: return a container that sort the indexes of the element to insert
// in the right order of insertion
// it don't handle 1 because the first element is already in the main chain
// it follow the jacobstahl sequence
template <typename Container>
Container
createinsertionOrder
(typename Container::size_type length)
{
	int currentJacob = 3;
	int prevJacob = 1;
	int nextJacob;
	Container insertionOrder;

	if (length == 0)
	   return insertionOrder;

	// INFO: since we don't fill it fully
	while (insertionOrder.size() != length)
	{
		// INFO: if list is between 2 jacob number, bound at lenght
		if (currentJacob > static_cast<int>(length))
			currentJacob = length + 1;

		// INFO: fill terms between 2 jacob with unused numbers
		for (int i = currentJacob; i != prevJacob; i--)
			insertionOrder.push_back(i - 2);

		// INFO: find next term
		nextJacob = currentJacob + 2 * prevJacob;

		// INFO: update prev and current
		prevJacob = currentJacob;
		currentJacob = nextJacob;
	}
	return insertionOrder;
}

/*
 * INFO: Variables:
 *		nbToPlaceId	(int)			: emplacement de la borne superieure qui a ete decalee, ce sera determine par cette fonction
 *		holding		(vector int)	: emplacement des insertions precedente ?
 *		sizeOfElement(int)			: taille d'un element donc ici valeur de decalage apres chaque comparaison reussie
 *		toAdd		(int)			: nombre d'element de decalage pour chaque element insere avant
 * Resume:
 *		Pour chaque element dans holding:
 *			Si holding est plus petit que nbToPlaceId
 *				-decale nbToPlaceId de sizeOfElement
 *				-incremente toAdd
 *		retourne toAdd
 *	Explication:
 *		Chaque fois que une precendente insertion (holding) est avant notre prochaine insertion:
 *			decaler (augmanter de sizeofelement l'index) nbToPlaceId
 *
 * */
template <typename Container, typename Type>
void considerPreviousInsertion
(const Container& prevInsertion, Type& nbToPlaceId, int sizeOfElement)
{
    for (typename Container::const_iterator it = prevInsertion.begin();
         it != prevInsertion.end(); ++it)
    {
        if (*it <= nbToPlaceId)
            nbToPlaceId += sizeOfElement;
    }
}

// INFO: Put greaters elements of the main chain after smallers
template <typename Container, typename Compare>
void
sort2By2
(Container &main, int sizeOfElement, Compare comp)
{
	int	step = sizeOfElement * 2;
	// INFO: for each pair of block of number (element)
	for (typename Container::iterator secondRangeElementToCompare = main.begin() + step - 1;
	secondRangeElementToCompare < main.end();
	secondRangeElementToCompare += step)
	{
		typename Container::iterator	firstRangeBegin = secondRangeElementToCompare + 1 - step;
		typename Container::iterator	firstRangeEnd = firstRangeBegin + sizeOfElement;
		typename Container::iterator	firstRangeElementToCompare = firstRangeEnd - 1;
		typename Container::iterator	secondRangeBegin = firstRangeEnd;
		// INFO: Compare last number of each elements
		if (comp(*secondRangeElementToCompare, *firstRangeElementToCompare))
			// INFO: Put smaller before larger
			std::swap_ranges(firstRangeBegin, firstRangeEnd, secondRangeBegin);
	}
}

// INFO: append pending elements that lost against greaters in pend chain
// PERF: trim them from main chain by putting it in newmain chain that is swapped
template <typename Container>
void
extractPend
(Container &main, Container &pend, int sizeOfElement)
{
	Container newMain;
	// INFO: new main chain is composed by first element + odd element
	newMain.insert(newMain.end(), main.begin(), main.begin() + 2 * sizeOfElement);

	bool	even = true;

	// INFO :for each pair of block of number (element)
	for (typename Container::iterator rangeBegin = main.begin() + 2 * sizeOfElement; rangeBegin != main.end(); rangeBegin += sizeOfElement)
	{
		typename Container::iterator rangeEnd = rangeBegin + sizeOfElement;

		// INFO: pending elements are even elements except first one
		if (even)
			pend.insert(pend.end(), rangeBegin, rangeEnd);

		// INFO: new main chain is composed by first element + odd element
		else
			newMain.insert(newMain.end(), rangeBegin, rangeEnd);

		even = !even;
	}
	// PERF: swap ownership of mainchain
	main.swap(newMain);
}

template <typename Container, typename Compare>
int
placeNumber
(Container &main, Container &pend, int nbToPlaceId, int borne, int sizeOfElement, Compare comp)
{
	// INFO: Info de l'element a inserer
	typename Container::iterator toInsertBegin = pend.begin() + nbToPlaceId;
	typename Container::iterator toInsertEnd = toInsertBegin + sizeOfElement;
	// NOTE: Representant est le dernier nombre de la range
	typename Container::value_type	toCompare = *(toInsertEnd - 1);

	// INFO: Index de la borne dans le main
	// la borne pour l'orphelin vaut main.size()-1, passee depuis insertPend
	typename Container::iterator searchEnd = main.begin() + borne;

	// INFO: Binary search tout les sizeOfElement le lower bound de notre element a inserer
	typename Container::iterator place = StrideLowerBound(main.begin(), searchEnd, toCompare, sizeOfElement, comp);

	// INFO: index a considerer pour trouver les prochaines bornes a cause du decalage
	// NOTE: calculé avant insert — place est invalidé après pour deque
	typename Container::difference_type i = place - main.begin();

	// PERF: insertion range
	main.insert(place, toInsertBegin, toInsertEnd);

	return i;
}

template <typename Container, typename Compare>
void
insertPend
(Container &main, Container pend, int sizeOfElement, int numberOfElements, Compare comp)
{
	std::vector<int> insertionIndexesSinceLastJacobsthal;

	// INFO: cree l'ordre dans lequel les pends vont etre inseres
	std::vector<int> insertionOrder = createinsertionOrder<std::vector<int> >(pend.size() / sizeOfElement);

	// INFO: sera utile pour savoir si on est passe d'un jacob a un autre dans la liste
	// ou si on a decremente entre deux
	int prevInsertId = 0;

	// INFO: valeur de decalage initial pour trouver les bornes
	// compte tenu du fait qu'il ya un element perdant au debut de la main chain
	int mainShift = sizeOfElement;

	// INFO: si numberOfElements est impair, le dernier element de pend est un orphelin
	bool hasOdd = numberOfElements % 2 != 0;
	// NOTE: il ya autant de pend que d'element dans la liste d'ordre d'insertion
	int pendCount = static_cast<int>(insertionOrder.size());

	// INFO: pour chaque pend dans la liste d'ordre d'insertion
	for (std::vector<int>::iterator toInsertId = insertionOrder.begin(); toInsertId != insertionOrder.end(); ++toInsertId)
	{
		int pendToInsertId = *toInsertId * sizeOfElement;

		// INFO: new jacob : les insertions precedentes sont toutes avant la nouvelle borne
		// donc on flush et on accumule leur decalage dans mainShift
		if (prevInsertId <= *toInsertId)
		{
			mainShift += insertionIndexesSinceLastJacobsthal.size() * sizeOfElement;
			insertionIndexesSinceLastJacobsthal.clear();
		}

		// INFO: borne exclusive (debut du bloc suivant la paire associee)
		// orphelin : main.end() = tout le main
		// sinon : debut du bloc apres la paire associee, decale par les insertions precedentes du groupe
		int mainBoundInsertion;
		if (hasOdd && *toInsertId == pendCount - 1)
			mainBoundInsertion = static_cast<int>(main.size());
		else
		{
			mainBoundInsertion = pendToInsertId + mainShift + sizeOfElement;
			considerPreviousInsertion(insertionIndexesSinceLastJacobsthal, mainBoundInsertion, sizeOfElement);
		}

		int insertionIndex = placeNumber(main, pend, pendToInsertId, mainBoundInsertion, sizeOfElement, comp);
		insertionIndexesSinceLastJacobsthal.push_back(insertionIndex);
		prevInsertId = *toInsertId;
	}
}

template <typename Container>
void
appendCrumbs
(Container &main, const Container &crumbs)
{
	main.insert(main.end(), crumbs.begin(), crumbs.end());
}

// INFO: extract incomplete trailing block (miettes) into crumb, trim main to complete blocks only
template <typename Container>
void
extractCrumbs
(Container &main, Container &crumbs, int sizeOfElement, int numberOfElements)
{
	typename Container::size_type completeSize = numberOfElements * sizeOfElement;
	crumbs.assign(main.begin() + completeSize, main.end());
	main.erase(main.begin() + completeSize, main.end());
}

template <typename Container, typename Compare>
void
recursiveSort
(Container &main, int sizeOfElement, Compare comp)
{
	int	numberOfElements = main.size() / sizeOfElement;

	// INFO: extract crumb to not handle it in this recursion level
	// crumb are numbers that are too few to compose an element
	Container crumbs;
	extractCrumbs(main, crumbs, sizeOfElement, numberOfElements);

	// INFO: determine the greater 2 by 2
	// then swap the greater right to the smaller
	sort2By2(main, sizeOfElement, comp);

	// PERF: if there is less than 3 element,
	// elements already sorted
	// ie no pend
	if (numberOfElements < 3)
	{
		appendCrumbs(main, crumbs);
		return ;
	}

	// INFO: if we can compose at least 2 pair, recursively launch the algoritm
	if (numberOfElements >= 4)
		recursiveSort(main, sizeOfElement * 2, comp);

	// INFO: compose the main chain : all winners and the first loser
	// others are pending elements
	Container pend;
	extractPend(main, pend, sizeOfElement);

	// INFO: insert pending element into main chain:
		// in the right insertion order
		// following the bound of each element
		// to decrease comparison
	insertPend(main, pend, sizeOfElement, numberOfElements, comp);

	// INFO: append crumb that we extracted before to handle it in a lower recursion
	appendCrumbs(main, crumbs);
}

template <typename Container, typename Compare>
void
sort
(Container &v, Compare comp)
{
	recursiveSort(v, 1, comp);
}
