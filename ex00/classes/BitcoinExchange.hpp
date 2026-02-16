/* ************************************************************************** */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/15 18:19:45 by aykrifa           #+#    #+#             */
/* ************************************************************************** */


#pragma once

#include <string>
#include <map>

const char	*DB = "data.csv";

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		BitcoinExchange(const char *);
		~BitcoinExchange(void);

		BitcoinExchange	operator=(const BitcoinExchange &);

	private:
		const static std::map<std::string, std::string>	csv;
		std::string	_input;
};

std::string	nbrToString(size_t nbr);
