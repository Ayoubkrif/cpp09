

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

#include "Helpers.hpp"
