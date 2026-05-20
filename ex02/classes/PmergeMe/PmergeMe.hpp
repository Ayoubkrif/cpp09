/* ************************************************************************** */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:54:28 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

class PmergeMe
{
	public:
		static void	sort(char **, int);
	private:
		PmergeMe(void);
		PmergeMe(const PmergeMe &);
		PmergeMe	&operator=(const PmergeMe &);
		~PmergeMe(void);
};

#include <limits>
#include <stdexcept>
#include <cerrno>
#include <cstdlib>

template <typename C1, typename C2>
void
fillContainer
(C1& container1, C2& container2, char** numbers, int n)
{
	for (int i = 0; i < n; i++)
	{
		char*	endptr;
		errno = 0;
		long	number = std::strtol(numbers[i], &endptr, 10);
		
		if (errno)
			throw std::runtime_error("Invalid input:"+std::string(numbers[i]));
		if (*endptr != '\0')
			throw std::runtime_error("Invalid input:"+std::string(numbers[i]));
		if (number < std::numeric_limits<unsigned int>::min())
			throw std::runtime_error("Invalid input:"+std::string(numbers[i]));
		if (number > std::numeric_limits<unsigned int>::max())
			throw std::runtime_error("Invalid input:"+std::string(numbers[i]));
		
		container1.push_back(static_cast<unsigned int>(number));
		container2.push_back(static_cast<unsigned int>(number));
	}
}

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

// return a container that sort the indexes of the element to insert
// in the right order of insertion
// it don't handle 1 because the first element is already in the main chain
#include <iostream>
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

	// when jacoblist is full
	while (insertionOrder.size() != length)
	{
		// if list is between 2 jacob number, bound at lenght
		if (currentJacob > static_cast<int>(length))
			currentJacob = length + 1;

		// fill terms between 2 jacob with unused numbers
		for (int i = currentJacob; i != prevJacob; i--)
			insertionOrder.push_back(i - 2);

		// find next term
		nextJacob = currentJacob + 2 * prevJacob;

		// update prev and current
		prevJacob = currentJacob;
		currentJacob = nextJacob;
	}
	return insertionOrder;
}

/*
 * Variables:
 *		nbToPlaceId	(int)			: emplacement de la borne superieure qui a ete decalee, ce sera determine par cette fonction
 *		holding		(vector int)	: emplacement des insertions precedente ?
 *		sizeOfElement(int)			: taille d'un element donc ici valeur de decalage apres chaque comparaison reussie
 *		toAdd		(int)			: nombre d'element de decalage pour chaque element insere avant
 *
 * Resume:
 *		Pour chaque element dans holding:
 *			Si holding est plus petit que nbToPlaceId
 *				-decale nbToPlaceId de sizeOfElement
 *				-incremente toAdd
 * 
 *		retourne toAdd
 *
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
