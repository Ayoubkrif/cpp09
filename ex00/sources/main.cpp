/* ************************************************************************** */
/*   main.cpp                                           :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/15 15:50:34 by aykrifa           #+#    #+#             */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"
#include <exception>
#include <iostream>

int	main(int argc, char *argv[])
{
	(void)argc, (void)argv;
	try
	{
		BitcoinExchange("input.txt");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
