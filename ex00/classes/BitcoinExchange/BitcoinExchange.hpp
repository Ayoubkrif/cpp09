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
	public:
		BitcoinExchange(const char *);
		~BitcoinExchange(void);

	private:
		const static std::map<std::string, float>	csv;

/**/		BitcoinExchange(void);
/**/		BitcoinExchange	operator=(const BitcoinExchange &);

};

std::string	nbrToString(size_t nbr);
