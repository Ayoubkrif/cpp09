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

template
<typename T>
void	iter(T *array, unsigned int size, void f(T const &))
{
	for (unsigned int i = 0; i < size; ++i)
	{
		f(array[i]);
	}
}

template
<typename T>
void	iter(T *array, unsigned int size, void f(T &))
{
	for (unsigned int i = 0; i < size; ++i)
	{
		f(array[i]);
	}
}

template
<typename Container, typename Func>
void	iter(Container& container, Func f)
{
	for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
	{
		f(*it);
	}
}

#include <iostream>

template
<typename T>
void	print(T const &t)
{
	std::cout << t << " ";
}

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
