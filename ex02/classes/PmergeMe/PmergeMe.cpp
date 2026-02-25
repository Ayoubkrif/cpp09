/* ************************************************************************** */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:44:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include <algorithm>
#include <deque>
#include <vector>
#include "PmergeMe.hpp"


void
rotateRange
(std::vector<unsigned int> &input, unsigned int start, unsigned int middle, unsigned int last)
{
	std::vector<unsigned int>::iterator	it_start = input.begin() + start;
	std::vector<unsigned int>::iterator	it_middle = input.begin() + middle;
	std::vector<unsigned int>::iterator	it_last = input.begin() + last;
	std::rotate(it_start, it_middle, it_last);
}

/*static std::vector<unsigned int>*/
void
recursiveSort
(std::vector<unsigned int> &input, unsigned int sizeOfElement)
{
	unsigned int sizeOfPair = 2 * sizeOfElement;
	for //for each pair:
	(unsigned int i = 0; (i + 1) * sizeOfPair <= input.size(); i++)
	{
	//COMPARE:
		// last number of the current element
		// last number of the next element
		if (input[i * sizeOfPair] > input[(i * sizeOfPair) + sizeOfElement])
		{
			// put larger at the end
			rotateRange(input, i * sizeOfPair, (i * sizeOfPair) + sizeOfElement, (i + 1) * sizeOfPair);
		}
	}
	if // if we can pair elements made by ACTUAL pairs
	(sizeOfPair * 2 <= input.size())
		recursiveSort(input, sizeOfPair);
}

void	PmergeMe::sort(char **numbers, int n)
{
	std::vector<unsigned int>	v;
	std::deque<unsigned int>	d;

	fillContainer(v, d, numbers, n);
	iter(v, print<unsigned int>);
	std::cout << std::endl;
	recursiveSort(v, 1);
	// rotateRange(v, 0, v.size() / 2, v.size());
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
