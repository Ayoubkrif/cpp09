/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/17 16:20:37 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <exception>
#include <iostream>
//🟰🔧💥
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage :\n\t\t./RPN \"1 2 - 3 + 4 / 5 +\"" << std::endl;
		return (1);
	}
	try
	{
		(RPN(argv[1]));
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
