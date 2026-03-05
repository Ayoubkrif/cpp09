#include "PmergeMe.hpp"
#include <iterator>
#include <stdexcept>
#include <vector>

PmergeMe::PmergeMe(int ac, char** av) : _vecTime(0)
{
    parseArguments(ac, av);
}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec = other._vec;
	}
	return *this;
}

void PmergeMe::parseArguments(int ac, char** av)
{
	if (ac < 2)
		throw std::runtime_error("Error : less than 1 argument");
	
	std::set<int> set;

	for (int i = 1; av[i]; i++)
	{
		std::istringstream 	iss(av[i]);
		std::string			token;
	
		while (iss >> token)
		{
			if (!isNumeric(token))
				throw std::runtime_error("Error : only integers numbers are allowed");	

			errno	= 0;
			char* 	endptr;
			long 	value = std::strtol(token.c_str(), &endptr, 10);

			if ((value == LONG_MAX && errno == ERANGE)|| *endptr != '\0' || value > INT_MAX)
				throw std::runtime_error("Error : probably overflow");
			if (value < 0)
				throw std::runtime_error("Error : negative number detected");
			
			int ivalue = static_cast<int>(value);
			std::set<int>::iterator it = set.find(ivalue);
			
			if (it != set.end())
				throw std::runtime_error ("Error : double integer detected");
			_vec.push_back(ivalue);
			_NotSorted.push_back(token);
			set.insert(ivalue);
		}
	}
}

bool PmergeMe::isNumeric(const std::string &token)
{
	const char* str = token.c_str();

	for (int i = 0; str[i]; i++)
	{
		if (!isdigit(static_cast<unsigned char>(str[i])))
			return false;
	}
	return true;
}

int			count = 0;

struct CompCounter
{
    CompCounter(void){}

    bool operator()(int a, int b) const
	{
		count++;
        return a < b;
    }
};

CompCounter	counter;

int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

int	vectcompFinal = 0;
void PmergeMe::run()
{
	printBefore();

	int	compVec = 0;
	int	compDeq = 0;
	int	compMax = F(_vec.size());

	clock_t start = clock();
	std::vector<int> tmp_vec = _vec;
	tmp_vec = sortVector(tmp_vec);
	clock_t end = clock();
	_vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	compVec = count;
	count = 0;


	printAfter(tmp_vec);
	printTimes();
	if (compMax < compVec || compMax < compDeq)
	{
		std::cerr << "MAX:" << compMax << std::endl;
		std::cerr << "Vec:" << compVec <<"("<<compVec - vectcompFinal<<")"<<"("<< vectcompFinal <<")"<< std::endl;
		std::cerr << "exceed by:" << compVec - compMax << std::endl;
		for (std::vector<std::string>::iterator it = _NotSorted.begin(); it < _NotSorted.end(); it++)
		{
			std::cerr << *it + " ";
		}
		std::cerr << std::endl;
	}
	throw (std::runtime_error("Arthur psm"));
}

void PmergeMe::printBefore()
{
	std::cout << std::left << std::setw(10) << "Before: ";
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::printAfter(const std::vector<int>& tmp_vec)
{
	std::cout << std::left << std::setw(10) << "After: ";
	for (std::vector<int>::const_iterator it = tmp_vec.begin(); it != tmp_vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::printTimes()
{
	std::cout << std::fixed << std::setprecision(5);

	std::cout 
	<< "Time to process a range of " << _vec.size() 
	<< " elements with std::vector<> : " << _vecTime * 1000 << " ms\n"
	<< std::endl; 
}

std::vector<int> PmergeMe::sortVector(std::vector<int>& tmp_vec)
{
	if (tmp_vec.size() <= 1)
		return tmp_vec;

	std::vector<std::pair<int, int> > 	pairs;
	std::vector<int> 					grands;
	int unpaired 						= -1;
	bool hasUnpaired 					= (tmp_vec.size() % 2 != 0);

	for (size_t i = 0; i + 1 < tmp_vec.size(); i += 2)
	{
		
		int a = tmp_vec[i];
		int b = tmp_vec[i + 1];
		vectcompFinal++;
		if (counter(a, b))
			pairs.push_back(std::make_pair(b, a));
		else
			pairs.push_back(std::make_pair(a, b));
	}
	if (hasUnpaired)
		unpaired = tmp_vec.back();
	for (size_t i = 0; i < pairs.size(); i++)
		grands.push_back(pairs[i].first);
	std::vector<int> sortedGrands = sortVector(grands);

	std::vector<size_t> jacobliste = generateJacobsthalList(pairs.size() + hasUnpaired);
	for (size_t i = 0; i < pairs.size(); i++)
	{
		size_t big = std::lower_bound(sortedGrands.begin(), sortedGrands.end(), pairs[jacobliste[i]].first) - sortedGrands.begin();
		int small = pairs[jacobliste[i]].second;
		std::vector<int>::iterator it = std::lower_bound(sortedGrands.begin(), sortedGrands.begin() + big /*+ 1*/, small, counter);
		sortedGrands.insert(it, small);
	}

	if (hasUnpaired)
	{
		std::vector<int>::iterator it = std::lower_bound(sortedGrands.begin(), sortedGrands.end(), unpaired, counter);
		sortedGrands.insert(it, unpaired);
	}
	return sortedGrands;
}

std::vector<size_t> PmergeMe::generateJacobsthalList(size_t limit)
{
    std::vector<size_t> jacoblist;
    size_t j0 = 0;
    size_t j1 = 1;
	jacoblist.push_back(j0);
	jacoblist.push_back(j1);

    while (1)
    {
		size_t next = j1 + 2 * j0;
        if (next >= limit || limit <= 1)
			break;
		j0 = j1;
        j1 = next;
		jacoblist.push_back(j1);
    }
	jacoblist.push_back(limit);

	std::vector<size_t> indices;
	for (size_t i = 1; i < jacoblist.size(); i++)
	{
		size_t start = jacoblist[i - 1];
		size_t end   = jacoblist[i];

		for (size_t i = end; i > start; --i)
			indices.push_back(i - 1);
	}

	// for (size_t i = 0; i < indices.size(); i++)
	// 	std::cout << indices[i] << " ";
	// std::cout << std::endl;

	return (indices);
}
