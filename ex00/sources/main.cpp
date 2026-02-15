/* ************************************************************************** */
/*   main.cpp                                           :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/15 15:50:34 by aykrifa           #+#    #+#             */
/* ************************************************************************** */


#include "bitcoin.hpp"
#include <exception>
#include <iostream>
#include <map>
#include <string>

const char	*DB = "data.csv";

int	main(int argc, char *argv[])
{
	(void)argc, (void)argv;
	try
	{
		std::map<std::string, std::string>	csv;
		csvReader(DB, csv);
		std::cout << csv.size() << " lines:" << std::endl;
		for (std::map<std::string, std::string>::iterator it = csv.begin(); it != csv.end(); it++)
			std::cout << it->first+","+it->second << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
