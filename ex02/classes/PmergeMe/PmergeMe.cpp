/* ************************************************************************** */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:44:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include <deque>
#include <vector>
#include "PmergeMe.hpp"


void
insertRange
(std::vector<unsigned int> &input, unsigned int from, unsigned int size, unsigned int to)
{
	std::vector<unsigned int>::iterator	it_to(&input.at(to));
	std::vector<unsigned int>::iterator	it_from(&input.at(from));
	std::vector<unsigned int>::iterator	it_last(&input.at(from + size));

	input.insert(it_to, it_from, it_last);
}

void
eraseRange
(std::vector<unsigned int> &input, unsigned int from, unsigned int size)
{
	std::vector<unsigned int>::iterator	it_from(&input.at(from));
	std::vector<unsigned int>::iterator	it_last(&input.at(from + size));

	input.erase(it_from, it_last);
}

/*static std::vector<unsigned int>*/
void
recursiveSort
(std::vector<unsigned int> &input, unsigned int sizeOfElement)
{
	unsigned int sizeOfPair = 2 * sizeOfElement;
	for // each possible pair
	(unsigned int i = 0; (i) * sizeOfPair <= input.size(); i += 2)
	{
		if (input[i * sizeOfElement] < input[(i + 1) * sizeOfElement])
		{
			// low->high
			insertRange(input, i * sizeOfElement, sizeOfElement, (i + 1) * sizeOfElement);
			// low->high->low
			eraseRange(input, i * sizeOfElement, sizeOfElement);
			// high->low
		}
	}
	if // si on peut faire au moins une paire de paire
	(sizeOfPair * 2 <= input.size())
		recursiveSort(input, sizeOfPair);
	return ;
}

void	PmergeMe::sort(char **numbers, int n)
{
	std::vector<unsigned int>	v;
	std::deque<unsigned int>	d;

	fillContainer(v, d, numbers, n);
	iter(v, print<unsigned int>);
	std::cout << std::endl;
	recursiveSort(v, 1);
	iter(v, print<unsigned int>);
	std::cout << std::endl;
}

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
