/* ************************************************************************** */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:44:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "utils.hpp"
#include "Ford-Johnson-Algoritm.hpp"

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
#include <ctime>
#include <deque>
#include <iomanip>
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

void	PmergeMe::run(char **numbers, int n)
{
	std::vector<int>			v;
	std::deque<int>	d;
	int	vecComp,deqComp;

	fillContainer(v, d, numbers, n);
	std::multiset<unsigned int>	ref(v.begin(), v.end());
	int max = maxComp(n);
	std::cout << std::left << std::setw(16) << "list"<< ": "  << printContainer(v, 0) << std::endl;

	// VECTOR
	g_comparisons = 0;
	clock_t vecStart = clock();
	sort(v, countComp);
	clock_t vecEnd = clock();
	vecComp = g_comparisons;

	// DEQUE
	g_comparisons = 0;
	clock_t deqStart = clock();
	sort(d, countComp);
	clock_t deqEnd = clock();
	deqComp = g_comparisons;

	double vecUs = static_cast<double>(vecEnd - vecStart) / CLOCKS_PER_SEC * 1e6;
	double deqUs = static_cast<double>(deqEnd - deqStart) / CLOCKS_PER_SEC * 1e6;

	// SORT TEST
	std::cout << std::left << std::setw(16) << "sorted list"<< ": " << printContainer(v, 0) << std::endl;
	if (!isSorted(v) || !sameElements(ref, v)
		|| !isSorted(d) || !sameElements(ref, d))
	{
		std::cout << std::left << std::setw(16) << "sorted list"<< ": " << printContainer(v, 0) << std::endl;
		std::cout << std::left << std::setw(16) << "sorted list"<< ": " << printContainer(d, 0) << std::endl;
		std::cout << "ITS NOT SORTED !" << std::endl;
		throw (std::runtime_error("OOPS"));
	}
	// MAX COMP TEST
	std::cout << std::left << std::setw(16) << "comparisons" << ": " << g_comparisons << "/" << max << std::endl;
	if (vecComp > max
		|| deqComp > max)
		throw (std::runtime_error("Too many comparisons"));

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << n << " elements with std::vector : " << vecUs << " us" << std::endl;
	std::cout << "Time to process a range of " << n << " elements with std::deque  : " << deqUs << " us" << std::endl;
}
