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

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <cstdlib>

static std::string	nbrToString(size_t nbr)
{
	std::ostringstream oss;
	oss << nbr;
	std::string str = oss.str();
	return str;
}

#include <map>
#include <fstream>

static std::map<std::string, float>	csvReader(const char* path)
{
    std::ifstream ifs(path, std::ios::binary);
    if (ifs.fail())
		throw (std::runtime_error("Cannot open " + std::string(path)));

	std::map<std::string, float>	DataBase;

	std::string	line;
	int			lineCount = 0;;
	while (std::getline(ifs, line))
	{
        std::stringstream lineStream(line);
        lineCount++;
		if (lineCount == 1)
			continue ;
		std::pair<std::string, float>	cell;
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
				cell.second = std::atof(word.c_str());
			cellCount++;
		}
		DataBase.insert(cell);
    }
	return (DataBase);
}

#include "BitcoinExchange.hpp"

const char	*DB = "data.csv";
const std::map<std::string, float>	BitcoinExchange::csv = csvReader(DB);

BitcoinExchange::BitcoinExchange(void)
{
	throw (std::runtime_error("Should not be called !"));
}

BitcoinExchange	BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	(void)rhs;
	throw (std::runtime_error("Should not be called !"));
}

BitcoinExchange::~BitcoinExchange(void)
{}

bool	isLeapYear(int year)
{
	if (!(year%400) || ((year%100) && !(year%4)))
		return (true);
	return (false);
	// if (!(year%400))
	// 	return (true);
	// if (!(year%100))
	// 	return (false);
	// if (!(year%4))
	// 	return (true);
	// return (false);
}

static const int maxDaysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool	checkDateFormat(const std::string &date)
{
	// must be 10 size 4 + 1 + 2 + 1 + 2
	if (date.size() != 10)
		return (false);

	// 4 + 1 th , 4 + 1 +2 + 1 th characters are -
	// others are digits
	for (unsigned int i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
		{
			if (date[i] != '-')
				return (false);
		}
		else
		{
			if (!std::isdigit(date[i]))
				return (false);
		}
	}
	const char	*dateStr = date.c_str();
	// 4 + 1 + (1&2) get value (MM)
	int	MM = std::atoi(dateStr + 5) - 1;
	if (MM > 11 || MM < 0)
		return (false);
	// 4 + 1 + 2 + 1 +(1&2)    (DD)
	int	DD = std::atoi(dateStr + 8);
	int	YYYY = std::atoi(dateStr);
	if (DD > maxDaysInMonths[MM] + (MM == 1 && isLeapYear(YYYY)))
		return (false);
	return (true);
}

#include <limits>

BitcoinExchange::BitcoinExchange(const char *path)
{
    std::ifstream ifs(path, std::ios::binary);
    if (ifs.fail())
		throw (std::runtime_error("Cannot open " + std::string(path)));

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
		// while token availaible
		while (lineStream >> word)
		{
			cellCount++;
			if (cellCount == 1)
			{
				cell.first = word;
			}
			else if (cellCount == 2)
			{
				if (word != "|")
					break ;
			}
			else if (cellCount == 3)
			{
				cell.second = word;
			}
		}
		if (cellCount != 3)
		{
			std::cout << "Bad input line "+nbrToString(lineCount)+": '"+ line+"'" << std::endl;
			continue ;
		}
		// check date format / value
		if (!checkDateFormat(cell.first))
		{
			std::cout << "Bad date line "+nbrToString(lineCount)+": '"+ line+"'" << std::endl;
			continue ;
		}
		// check num format / value
		if (cell.second.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cout << "Value must be number only line "+nbrToString(lineCount)+": '"+ line+"'" << std::endl;
			continue ;
		}
		long int	nb = std::strtol(cell.second.c_str(), NULL, 10);

		if (errno || nb < 0 || nb > 1000)
		{
			std::cout << "Value must be between 0 and 999 "+nbrToString(lineCount)+": '"+ line+"'" << std::endl;
			continue ;
		}
		// check lower date
		std::map<std::string, float>::const_iterator it = csv.lower_bound(cell.first);
		if (it == csv.begin())
		{
			std::cout << "No data for "+ cell.first << " line " << nbrToString(lineCount)+": '"+ line+"'" << std::endl;
			continue ;
		}
		// print value num * map[date].value
		std::cout << cell.first+" => "+cell.second+" = " << (it->second * nb) << std::endl;
	}
}
