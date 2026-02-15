/* ************************************************************************** */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/15 18:19:45 by aykrifa           #+#    #+#             */
/* ************************************************************************** */


#pragma once

#include <string>
#include <map>
class BitcoinExchange
{
	static const char	DB[];
	static std::map<std::string, std::string>	csv;
	public:
		std::map<std::string, std::string>	csvReader(const char* path);
};

std::string	nbrToString(size_t nbr);
