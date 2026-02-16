/* ************************************************************************** */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/15 18:23:31 by aykrifa           #+#    #+#             */
/* ************************************************************************** */
/*   csvReader.cpp                                      :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/15 16:45:49 by aykrifa           #+#    #+#             */
/* ************************************************************************** */
/*   mimeTypesMapFill.cpp                               :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/01/31 18:15:29 by aykrifa           #+#    #+#             */
/* ************************************************************************** */
/*   nbrToString.cpp                                    :+:      :+:    :+:   */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*   Created: 2025/12/16 14:15:21 by cbordeau          #+#    #+#             */
/* ************************************************************************** */

#include <sstream>

static std::string	nbrToString(size_t nbr)
{
	std::ostringstream oss;
	oss << nbr;
	std::string str = oss.str();
	return str;
}

#include <map>
#include <fstream>

static std::map<std::string, std::string>	csvReader(const char* path)
{
    std::ifstream ifs(path, std::ios::binary);
    if (ifs.fail())
		throw (std::runtime_error("Cannot open " + std::string(path)));

	std::map<std::string, std::string>	DataBase;

	std::string	line;
	int			lineCount = 0;;
	while (std::getline(ifs, line))
	{
        std::stringstream lineStream(line);
        lineCount++;
		if (lineCount == 1)
			continue ;
		std::pair<std::string, std::string>	cell;
		int									cellCount = 0;

        std::string word;
		// tant que je trouve un token
		while (getline(lineStream, word, ','))
		{
			// throw si trop de token par ligne
			if (cellCount >= 2)
				throw (std::runtime_error("too much cells on a line" + nbrToString(lineCount)));
			// on l'ajoute a la paire date valeur
			else if (cellCount == 0)
				cell.first = word;
			else if (cellCount == 1)
				cell.second = word;
			cellCount++;
		}
		DataBase.insert(cell);
    }
	return (DataBase);
}

#include "BitcoinExchange.hpp"

const std::map<std::string, std::string>	BitcoinExchange::csv = csvReader(DB);

BitcoinExchange::BitcoinExchange(void)
{}

BitcoinExchange::BitcoinExchange(const char *path) : _input(path)
{}
