/* ************************************************************************** */
/*   main.cpp                                           :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:36:37 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include <exception>
#include <iostream>
#include <vector>
#include "PmergeMe.hpp"

int	main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << "Usage: ./PmergeMe n1 n2 ..." << std::endl;
		return (1);
	}
	try
	{
		PmergeMe::sort(argv + 1, argc - 1);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
