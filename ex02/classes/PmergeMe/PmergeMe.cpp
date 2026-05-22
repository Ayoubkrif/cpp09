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
	std::cout << std::left << std::setw(16) << "unsorted list" << printContainer(v, 0) << std::endl;

	// VECTOR
	g_comparisons = 0;
	struct timespec vecStart, vecEnd;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &vecStart);
	sort(v, countComp);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &vecEnd);
	vecComp = g_comparisons;

	double vecMs = ((vecEnd.tv_sec - vecStart.tv_sec) * 1e9 + (vecEnd.tv_nsec - vecStart.tv_nsec)) / 1e6;

	// DEQUE
	g_comparisons = 0;
	struct timespec deqStart, deqEnd;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &deqStart);
	sort(d, countComp);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &deqEnd);
	deqComp = g_comparisons;

	double deqMs = ((deqEnd.tv_sec - deqStart.tv_sec) * 1e9 + (deqEnd.tv_nsec - deqStart.tv_nsec)) / 1e6;

	// SORT TEST
	std::cout << std::left << std::setw(16) << "sorted list" << printContainer(v, 0) << std::endl;
	if (!isSorted(v) || !sameElements(ref, v)
		|| !isSorted(d) || !sameElements(ref, d))
	{
		std::cout << std::left << std::setw(16) << "vec" << printContainer(v, 0) << std::endl;
		std::cout << std::left << std::setw(16) << "deq" << printContainer(d, 0) << std::endl;
		std::cout << "ITS NOT SORTED !" << std::endl;
		throw (std::runtime_error("OOPS"));
	}
	// MAX COMP TEST
	std::cout << std::left << std::setw(16) << "comparisons" << g_comparisons /*<< "/" << max */<< std::endl;
	if (vecComp > max
		|| deqComp > max)
		throw (std::runtime_error("Too many comparisons"));

	std::cout << std::left << std::setw(16) << std::fixed << std::setprecision(6)
		<< "std::vector" << vecMs << " ms" << std::endl;
	std::cout << std::left << std::setw(16) << std::fixed << std::setprecision(6)
		<< "std::deque" << deqMs << " ms" << std::endl;
}
