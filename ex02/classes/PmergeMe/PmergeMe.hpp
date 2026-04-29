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

#include <iostream>

template <typename Container>
void print(Container& container)
{
    for (typename Container::iterator it = container.begin(); it != container.end(); ++it)
    {
		std::cout << it->first << " ";
    }
}

#include <limits>
#include <stdexcept>
#include <cerrno>
#include <cstdlib>

template
<typename C1, typename C2>
void	fillContainer(C1& container1, C2& container2, char** numbers, int n)
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
		std::pair<unsigned int, int>	pair(static_cast<unsigned int>(number), -1);
		container1.push_back(pair);
		container2.push_back(pair);
	}
}

#include <vector>
#include <algorithm>

template
<typename T>
void
rotateRange
(std::vector<T> &input, unsigned int start, unsigned int middle, unsigned int last)
{
	typename std::vector<T>::iterator	it_start = input.begin() + start;
	typename std::vector<T>::iterator	it_middle = input.begin() + middle;
	typename std::vector<T>::iterator	it_last = input.begin() + last;
	std::rotate(it_start, it_middle, it_last);
}
