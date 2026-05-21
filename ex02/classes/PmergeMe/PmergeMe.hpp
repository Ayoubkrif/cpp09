/* ************************************************************************** */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:54:28 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

class PmergeMe
{
	public:
		static void	run(char **, int);
	private:
		PmergeMe(void);
		PmergeMe(const PmergeMe &);
		PmergeMe	&operator=(const PmergeMe &);
		~PmergeMe(void);
};

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

#include "Helpers.hpp"
