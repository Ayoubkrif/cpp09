/* ************************************************************************** */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:44:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include <deque>
#include <vector>
#include "PmergeMe.hpp"


static std::vector<unsigned int>
recursiveSort
(std::vector<unsigned int> &input)
{
	for (unsigned int i = 0; i < input.size(); i += 2)
	{
		;
	}
	return (input);
}

void	PmergeMe::sort(char **numbers, int n)
{
	std::vector<unsigned int>	v;
	std::deque<unsigned int>		d;

	fillContainer(v, d, numbers, n);
	iter(v, print<unsigned int>);
	recursiveSort(v);
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
