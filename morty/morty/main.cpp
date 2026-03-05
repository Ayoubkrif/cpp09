#include "PmergeMe.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char** argv) 
{
	try {
		PmergeMe ford_johnson(argc, argv);
		ford_johnson.run();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
