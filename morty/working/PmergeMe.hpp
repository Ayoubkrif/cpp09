#ifndef PMERGEME_HPP
#define PMERGEME_HPP

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

class PmergeMe {

public:

	PmergeMe(int ac, char** av);
	~PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	std::vector<size_t> generateJacobsthalList(size_t limit);
	void run();

private:

	std::vector<int> 	_vec;
	std::deque<int> 	_deque;
	double 				_vecTime;
    double 				_dequeTime;

	
	void			 	parseArguments(int ac, char** av);
    std::vector<int> 	sortVector(std::vector<int>& tmp_vec);
    std::deque<int> 	sortDeque(std::deque<int>& tmp_deque);
    void 				printBefore();
    void 				printAfter(const std::vector<int>& tmp_vec);
    void 				printTimes();
	bool 				isNumeric(const std::string &token);

};

#endif // PmergeMe_HPP
