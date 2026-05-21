/* ************************************************************************** */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:44:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "utils.hpp"
PmergeMe
::PmergeMe
(void)
{
	throw (std::runtime_error("Should not be called !"));
}

PmergeMe
::PmergeMe
(const PmergeMe &copy)
{
	(void)copy;
	throw (std::runtime_error("Should not be called !"));
}

PmergeMe	&PmergeMe
::operator=
(const PmergeMe &rhs)
{
	(void)rhs;
	throw (std::runtime_error("Should not be called !"));
	return (*this);
}

PmergeMe
::~PmergeMe
(void){}

#include <algorithm>
#include <deque>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

int g_comparisons = 0;

static bool
countComp
(int a, int b)
{
	g_comparisons++;
	return a < b;
}

// INFO: Put greaters elements of the main chain after smallers
void
sort2By2
(std::vector<int> &main, std::vector<int>::size_type sizeOfElement)
{
	int	step = sizeOfElement * 2;
	// INFO: for each pair of block of number (element)
	for (std::vector<int>::iterator secondRangeElementToCompare = main.begin() + step - 1;
	secondRangeElementToCompare < main.end();
	secondRangeElementToCompare += step)
	{
		std::vector<int>::iterator	firstRangeBegin = secondRangeElementToCompare + 1 - step;
		std::vector<int>::iterator	firstRangeEnd = firstRangeBegin + sizeOfElement;
		std::vector<int>::iterator	firstRangeElementToCompare = firstRangeEnd - 1;
		std::vector<int>::iterator	secondRangeBegin = firstRangeEnd;
		// INFO: Compare last number of each elements
		if (countComp(*secondRangeElementToCompare, *firstRangeElementToCompare))
			// INFO: Put smaller before larger
			std::swap_ranges(firstRangeBegin, firstRangeEnd, secondRangeBegin);
	}
}

// INFO: append pending elements that lost against greaters in pend chain
// PERF: trim them from main chain by putting it in newmain chain that is swapped
void
extractPend
(std::vector<int> &main, std::vector<int> &pend, int sizeOfElement)
{
	std::vector<int> newMain;
	// PERF: alloc main size in vector
	newMain.reserve(main.size() + sizeOfElement);
	// INFO: new main chain is composed by first element + odd element
	newMain.insert(newMain.end(), main.begin(), main.begin() + 2 * sizeOfElement);

	pend.reserve(main.size() / 2);

	bool	even = true;

	// INFO :for each pair of block of number (element)
	for (std::vector<int>::iterator rangeBegin = main.begin() + 2 * sizeOfElement; rangeBegin != main.end(); rangeBegin += sizeOfElement)
	{
		std::vector<int>::iterator rangeEnd = rangeBegin + sizeOfElement;

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

int
placeNumber
(std::vector<int> &main, std::vector<int> &pend, int nbToPlaceId, int borne, int sizeOfElement)
{
	// INFO: Info de l'element a inserer
	std::vector<int>::iterator toInsertBegin = pend.begin() + nbToPlaceId - sizeOfElement + 1;
	std::vector<int>::iterator toInsertEnd = pend.begin() + nbToPlaceId + 1;
	int	toCompare = pend[nbToPlaceId];

	// INFO: Index de la borne dans le main
	// WARN: ne gere pas le non paire
	// TODO: Borner en amont a end le non paire
	std::vector<int>::iterator searchEnd = main.begin() + borne + 1;

	// INFO: Binary search tout les sizeOfElement le lower bound de notre element a inserer
	std::vector<int>::iterator place = StrideLowerBound(main.begin(), searchEnd, toCompare, sizeOfElement, countComp);

	// PERF: insertion range
	main.insert(place, toInsertBegin, toInsertEnd); // BUG: cause des acces avant le debut du vector

	// INFO: index a considerer pour trouver les prochaines bornes a cause du decalage
	std::vector<int>::difference_type i = place - main.begin();
	return i;
}

void
insertPend
(std::vector<int> &main, std::vector<int> pend, int sizeOfElement)
{
	std::vector<int> insertionIndexesSinceLastJacobsthal;

	// INFO: cree l'ordre dans lequel les pends vont etre inseres
	std::vector<int> insertionOrder = createinsertionOrder<std::vector<int> >(pend.size() / sizeOfElement);

	std::cout << "size of jacob:" << insertionOrder.size() << std::endl;

	// INFO: sera utile pour savoir si on est passe d'un jacob a un autre dans la liste
	// ou si on a decremente entre deux
	int prevInsertId = 0;

	// INFO: valeur de decalage initial pour trouver les bornes
	// compte tenu du fait qu'il ya un element perdant au debut de la main chain
	int mainShift = sizeOfElement;

	// INFO: pour chaque pend dans la liste de jacob
	// WARN: ne gere plus l'element non paire
	// TODO: il faut determiner sa borne dans la for
	// sans le calculer a chaque iteration
	for (std::vector<int>::iterator toInsertId = insertionOrder.begin(); toInsertId != insertionOrder.end(); ++toInsertId)
	{
		// INFO: index of the element
		int pendToInsertId = *toInsertId * sizeOfElement;

		// INFO: between 2 jacob
		if (prevInsertId > *toInsertId)
		{
			// INFO: trouve la paire sans le decalge de holding
			int mainBoundInsertion = pendToInsertId + mainShift;
			// INFO: decale en fonction des insertions precedente pour tomber sur la borne exactement
			considerPreviousInsertion(insertionIndexesSinceLastJacobsthal, mainBoundInsertion, sizeOfElement);
	
			// INFO: insere et edite lastInsertedMain a l'insertion actuelle
			// puis ajoute la position dans le main de l'insertion precedente
			int insertionIndex = placeNumber(main, pend, pendToInsertId, mainBoundInsertion, sizeOfElement);
			insertionIndexesSinceLastJacobsthal.push_back(insertionIndex);
		}
		// INFO: new jacob
		else
		{
			// INFO: les insertions precedentes sont forcement avant le nouveau jacob
			// donc decale de taille de previous insertion * sizeofelement (=nombres inseres avant la nouvelle borne)
			// puis flush le vector
			mainShift += insertionIndexesSinceLastJacobsthal.size() * sizeOfElement;
			insertionIndexesSinceLastJacobsthal.clear();

			// INFO: trouve la paire
			int mainBoundInsertion = pendToInsertId + mainShift;
			std::cout << "mainBoundInsertion = " << mainBoundInsertion << std::endl;

			// INFO: insere et edite lastInsertedMain a l'insertion actuelle
			// puis ajoute la position dans le main de l'insertion precedente
			int insertionIndex = placeNumber(main, pend, pendToInsertId, mainBoundInsertion, sizeOfElement);
			insertionIndexesSinceLastJacobsthal.push_back(insertionIndex);
		}
		prevInsertId = *toInsertId;
	}
}

#include <iomanip>

void
appendCrumbs
(std::vector<int> &main, const std::vector<int> &crumbs)
{
	main.insert(main.end(), crumbs.begin(), crumbs.end());
}

// INFO: extract incomplete trailing block (miettes) into crumb, trim main to complete blocks only
void
extractCrumbs
(std::vector<int> &main, std::vector<int> &crumbs, int sizeOfElement, int numberOfElements)
{
	std::vector<int>::size_type completeSize = numberOfElements * sizeOfElement;
	crumbs.assign(main.begin() + completeSize, main.end());
	main.erase(main.begin() + completeSize, main.end());
}

void
recursiveSort
(std::vector<int> &main, int sizeOfElement)
{
	std::cout << std::left << std::setw(16) << "complete chain" << ": " << printContainer(main, sizeOfElement) << std::endl;
	int	numberOfElements = main.size() / sizeOfElement;

	// INFO: extract crumb to not handle it in this recursion level
	// crumb are numbers that are too few to compose an element
	std::vector<int> crumbs;
	extractCrumbs(main, crumbs, sizeOfElement, numberOfElements);

	// INFO: determine the greater 2 by 2
	// then swap the greater right to the smaller
	sort2By2(main, sizeOfElement);

	std::cout << std::left << std::setw(16) << "after swap" << ": " << printContainer(main, sizeOfElement) << std::endl;
	
	// HACK: if there is less than 3 element,
	// elements already sorted
	// ie no pend
	if (numberOfElements < 3)
	{
		appendCrumbs(main, crumbs);
		return ;
	}

	// INFO: if we can compose at least 2 pair, recursively launch the algoritm
	if (numberOfElements >= 4)
		recursiveSort(main, sizeOfElement * 2);

	std::cout << std::left << std::setw(16) << "after recursion" << ": " << printContainer(main, sizeOfElement) << std::endl;
	
	// INFO: compose the main chain : all winners and the first loser
	// others are pending elements
	std::vector<int> pend;
	extractPend(main, pend, sizeOfElement);
	std::cout << std::left << std::setw(16) << "Main chain" << ": " << printContainer(main, sizeOfElement) << std::endl;
	std::cout << std::left << std::setw(16) << "Pending Elements" << ": " << printContainer(pend, sizeOfElement) << std::endl;
	
	// INFO: insert pending element into main chain:
		// in the right insertion order
		// following the bound of each element
		// to decrease comparison
	// WARN: UNSAFE BUG COME FROM HERE
	insertPend(main, pend, sizeOfElement);

	std::cout << std::left << std::setw(16) << "main post-insert" << ": " << printContainer(main, sizeOfElement) << std::endl;
	std::cout << std::left << std::setw(16) << "pend post-insert" << ": " << printContainer(pend, sizeOfElement) << std::endl;

	// INFO: append crumb that we extracted before to handle it in a lower recursion
	appendCrumbs(main, crumbs);
}

void	PmergeMe::sort(char **numbers, int n)
{
	std::vector<int>			v;
	std::deque<unsigned int>	d;

	fillContainer(v, d, numbers, n);
	std::multiset<unsigned int>	ref(v.begin(), v.end());
	int max = maxComp(n);
	g_comparisons = 0;
	std::cout << std::left << std::setw(16) << "list"<< ": "  << printContainer(v, 0) << std::endl;
	recursiveSort(v, 1);
	std::cout << std::left << std::setw(16) << "sorted list"<< ": " << printContainer(v, 1) << std::endl;
	if (!isSorted(v) || !sameElements(ref, v))
	{
		throw (std::runtime_error("OOPS"));
	}
	std::cout << std::left << std::setw(16) << "comparisons" << ": " << g_comparisons << "/" << max << std::endl;
	if (g_comparisons > max)
		throw (std::runtime_error("Too many comparisons"));
}

