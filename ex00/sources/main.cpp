/* ************************************************************************** */
/*   main.cpp                                           :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/15 15:50:34 by aykrifa           #+#    #+#             */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

int	main(int argc, char *argv[])
{
	try
	{
		if (argc != 2)
			throw (std::runtime_error("Usage ./btc input_file"));
		BitcoinExchange((const char *)argv[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
