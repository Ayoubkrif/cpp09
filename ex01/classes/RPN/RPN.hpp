/* ************************************************************************** */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:25:00 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#pragma once

#include <list>
#include <stack>
#include <string>
class RPN
{
	public:
		RPN(void);
		RPN(const RPN &);
		~RPN(void);

		RPN &operator=(const RPN &);
		RPN(const char *);
	private:
		void	compute(char);
		std::stack<int, std::list<int> >	_Stack;
		std::string							_token;
		int									tokenCount;
};
