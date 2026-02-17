/* ************************************************************************** */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:22:16 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype>
#include <cstdlib>
#include <stdexcept>

RPN::RPN(void)
{
	throw (std::runtime_error("Should not be called !"));
}

RPN::RPN(const RPN &src)
{
	(void)src;
	throw (std::runtime_error("Should not be called !"));
}

RPN::~RPN(void)
{
}

RPN &RPN::operator=(const RPN &rhs)
{
	throw (std::runtime_error("Should not be called !"));
	if (this != &rhs)
	{
	}
	return (*this);
}

#include <sstream>

static std::string	nbrToString(size_t nbr)
{
	std::ostringstream oss;
	oss << nbr;
	std::string str = oss.str();
	return str;
}

RPN::RPN(const char *expr)
{
	std::stringstream	tokenStream(expr);

	// while token availaible
	while (tokenStream >> _token)
	{
		// break if all expr computed ?
		if (_token.empty())
			break ;
		// 
		if (_token.size() != 1)
			throw (std::runtime_error("Token "+ nbrToString(tokenCount) + ":'"+_token+"' is too large or empty"));
		if (std::isdigit(_token[0]))
			_Stack.push(std::atoi(_token.c_str()));
		else
			compute(_token[0]);
	}
}

void	RPN::compute(char op)
{
	int	first, second;
	first = _Stack.top();
	_Stack.pop();
	second = _Stack.top();
	_Stack.pop();
	switch (op)
	{
		case '+':
			first += second;
		break ;
		case '-':
			first -= second;
		break ;
		case '*':
			first *= second;
		break ;
		case '/':
			first /= second;
		break ;
		default:
			throw (std::runtime_error("Unrecognised token "+ nbrToString(tokenCount) + ":'"+_token+"'"));
	}
	_Stack.push(first);
}
