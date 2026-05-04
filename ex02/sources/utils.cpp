/* ************************************************************************** */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/05/04 21:21:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include <algorithm>
#include <deque>
#include <vector>

void
rotateRange
(std::vector<unsigned int> &input, unsigned int start, unsigned int middle, unsigned int last)
{
	std::vector<unsigned int>::iterator	it_start = input.begin() + start;
	std::vector<unsigned int>::iterator	it_middle = input.begin() + middle;
	std::vector<unsigned int>::iterator	it_last = input.begin() + last;
	std::rotate(it_start, it_middle, it_last);
}
