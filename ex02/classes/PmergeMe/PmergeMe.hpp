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
	std::cout << t << std::endl;
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
		
		container1.push_back(static_cast<unsigned int>(number));
		container2.push_back(static_cast<unsigned int>(number));
	}
}
