/* ************************************************************************** */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/05/04 21:21:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include "utils.hpp"

// upper bound on comparisons for Ford-Johnson sort of n elements
int
maxComp
(int n)
{
	int sum = 0;
	for (int k = 1; k <= n; ++k)
	{
		double value = (3.0 / 4.0) * k;
		sum += static_cast<int>(ceil(log(value) / log(2.0)));
	}
	return sum;
}

void
rotateRange
(std::vector<unsigned int> &input, unsigned int start, unsigned int middle, unsigned int last)
{
	std::vector<unsigned int>::iterator	it_start = input.begin() + start;
	std::vector<unsigned int>::iterator	it_middle = input.begin() + middle;
	std::vector<unsigned int>::iterator	it_last = input.begin() + last;
	std::rotate(it_start, it_middle, it_last);
}
