/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:03:39 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */



#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <istream>
#include <cmath>
#include <vector>
#include <deque>
#include <set>
#include <climits>
#include <cerrno>
#include <map>
#include <algorithm>

class PmergeMe
{

public:

	PmergeMe(int ac, char** av);
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	std::vector<size_t> generateJacobsthalList(size_t limit);
	void run();

private:

	std::vector<int>			_vec;
	std::vector<std::string> 	_NotSorted;
	double 						_vecTime;

	
	void			 	parseArguments(int ac, char** av);
    std::vector<int> 	sortVector(std::vector<int>& tmp_vec);
    void 				printBefore();
    void 				printAfter(const std::vector<int>& tmp_vec);
    void 				printTimes();
	bool 				isNumeric(const std::string &token);

};
