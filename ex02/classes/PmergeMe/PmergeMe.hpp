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

template <typename Iterator, typename T>
Iterator
StrideLowerBound
(Iterator first, Iterator last, const T& value, std::size_t step)
{
    typedef typename std::iterator_traits<Iterator>::difference_type diff_t;
    diff_t total = std::distance(first, last);
    diff_t count = total / step;
    diff_t lo = 0, hi = count;

    while (lo < hi) {
        diff_t mid = lo + (hi - lo) / 2;
        Iterator Candidate = first;
        std::advance(Candidate, mid * step + (step - 1));  // offset n-1
        if (*Candidate < value) lo = mid + 1;
        else hi = mid;
    }

    Iterator result = first;
    if (lo < count) std::advance(result, lo * step); // si entre 0 et count alors retourner le debut du block
    else result = last;  // sinon tous les représentants étaient < value

    return result;
}

template <typename Container>
Container
createinsertionOrder
(typename Container::size_type length)
{
	int current = 3;
	int prev = 1;
	int next;
	Container jacobList;

	if (length == 0)
	   return jacobList;
	// initial term
	jacobList.push_back(1);

	// when jacoblist is full
	while (jacobList.size() != length)
	{
		// if list is between 2 jacob number, bound at lenght
		if (current > static_cast<int>(length))
			current = length;

		// fill terms between 2 jacob with unused numbers
		for (int i = current; i != prev; i--)
			jacobList.push_back(i);

		// find next term
		next = current + 2 * prev;

		// update prev and current
		prev = current;
		current = next;
	}
	return jacobList;
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

#include <set>

// 1) Vérifie si un container est trié (ordre croissant)
template <typename Container>
bool isSorted(const Container& c) {
    typename Container::const_iterator it = c.begin();
    if (it == c.end()) return true;          // container vide => trié
    typename Container::const_iterator next = it;
    ++next;
    for (; next != c.end(); ++it, ++next) {
        if (*next < *it) return false;       // ordre strict croissant non respecté
    }
    return true;
}

// 2) Vérifie que le container a exactement les mêmes éléments que le multiset
//    (mêmes valeurs ET mêmes multiplicités, ordre indifférent)
template <typename T, typename Container>
bool sameElements(const std::multiset<T>& ref, const Container& c) {
    // Comparaison de taille rapide pour éliminer les cas évidents
    if (ref.size() != static_cast<typename std::multiset<T>::size_type>(
                          std::distance(c.begin(), c.end())))
        return false;

    // On construit un multiset à partir du container et on compare
    std::multiset<T> other(c.begin(), c.end());
    return ref == other;
}

//Helpers
#include <iostream>
template <typename Container>
struct ContainerPrinter
{
    const Container& container;
    int sizeOfElement;

    ContainerPrinter(const Container& c, int s)
        : container(c), sizeOfElement(s) {}
};

template <typename Container>
ContainerPrinter<Container>
printContainer
(const Container& c, int s)
{
    return ContainerPrinter<Container>(c, s);
}

template <typename Container>
std::ostream&
operator<<
(std::ostream& os, const ContainerPrinter<Container>& p)
{
    int count = 0;
    for (typename Container::const_iterator it = p.container.begin();
         it != p.container.end(); ++it)
    {
        if (count != 0)
        {
			if (p.sizeOfElement == 0)
                os << ",";
            else if (count % (p.sizeOfElement * 2) == 0)
                os << "|";
            else if (count % p.sizeOfElement == 0)
                os << ",";
            else
                os << " ";
        }
        os << *it;
        ++count;
    }
    return os;
}
