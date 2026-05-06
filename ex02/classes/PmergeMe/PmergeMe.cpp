/* ************************************************************************** */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:44:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include <algorithm>
#include <deque>
#include <utility>
#include <vector>
#include "PmergeMe.hpp"


// Put greaters elements of the main chain after smallers
// duplicate smallers in a chain named pend
void
swapMain
(std::vector<int> &main, std::vector<int>::size_type sizeOfElement)
{
	std::vector<int> newMain;
	// alloc main size in vector
    newMain.reserve(main.size());

	int	step = sizeOfElement * 2;
	// for each pair of block of number (element)
	for (std::vector<int>::iterator firstRangeBegin = main.begin();
	firstRangeBegin < main.end();
	firstRangeBegin += step)
	{
		std::vector<int>::iterator	firstRangeEnd = firstRangeBegin + sizeOfElement;
		std::vector<int>::iterator	firstRangeElementToCompare = firstRangeEnd - 1;

		std::vector<int>::iterator	secondRangeBegin = firstRangeEnd;
		std::vector<int>::iterator	secondRangeEnd = firstRangeBegin + step;
		std::vector<int>::iterator	secondRangeElementToCompare = secondRangeEnd - 1;
		// Compare last number of each elements
		if (*firstRangeElementToCompare > *secondRangeElementToCompare)
		{
			// Put greaters elements after smallers
            newMain.insert(newMain.end(), secondRangeBegin, secondRangeEnd);
            newMain.insert(newMain.end(), firstRangeBegin, firstRangeEnd);
		}
		else
			// Put greaters elements after smallers
            newMain.insert(newMain.end(), firstRangeBegin, secondRangeEnd);
	}
	// append orphans
    newMain.insert(newMain.end(), main.begin() + newMain.size(), main.end());
	main.swap(newMain);
}

void
swapMainChain
(std::vector<int> &main, std::vector<int>::size_type sizeOfElement)
{
	for (int i = sizeOfElement - 1; i + sizeOfElement < main.size(); i += sizeOfElement * 2)
	{
		if (main[i] > main[i + sizeOfElement])
		{
			rotatewithstdrotate(main, sizeOfElement, i, i + sizeOfElement);
		}
	}
}

// trim pending elements that lost against winners
void
trimSmallersFromMainChain
(std::vector<int> &main, int sizeOfElement)
{
	// maxPair before end or before reminder elements
	size_t maxPair = (main.size() / sizeOfElement);

	std::vector<int>::iterator it = main.begin();
	for (size_t i = 0; i < maxPair; i++)
	{
			it = main.erase(it, it + sizeOfElement);
			it += sizeOfElement;
	}
}

int	holdingToConsider(std::vector<int> holding, int nbToPlaceId, int sizeOfElement)
{
	int toAdd = 0;

	for (std::vector<int>::iterator it = holding.begin(); it != holding.end(); ++it)
	{
		if (*it <= nbToPlaceId)
		{
			toAdd += 1;
			nbToPlaceId += sizeOfElement;
		}
	}
	return toAdd;
}

//binary insertion
int	placeNumber(std::vector<int> *main, std::vector<int> pend, int nbToPlaceId, int borne, int sizeOfElement)
{
	std::vector<int> toInsert;
	int	toCompare = pend[nbToPlaceId];

	for (int j = nbToPlaceId - sizeOfElement + 1; j <= nbToPlaceId; j++)
		toInsert.push_back(pend[j]);
	int i = 0;
	if (borne == sizeOfElement - 1)
	{
		insert(main, toInsert, i);
		return i;
	}
	int temp, downBorne = 0, upBorne = (borne + 1) / sizeOfElement;
	while(upBorne - downBorne != 1 && upBorne != downBorne)
	{
		temp = downBorne + ((upBorne - downBorne) / 2);
		VectComp++;
		if (toCompare < (*main)[(temp * sizeOfElement) - 1])
			upBorne = temp;
		else
			downBorne = temp;
	}
	i += downBorne * sizeOfElement;
	insert(main, toInsert, i);
	return i;
}

void
insertPend
(std::vector<int> &main, std::vector<int> pend, int sizeOfElement)
{
	int prevJacob = 0;
	int decalage = 0;
	std::vector<int> holding;
	int prevId = 0;
	int nbToPlaceId;
	int pairId = 0;

	std::vector<int> jacobList = createJacobList<std::vector<int> >(pend.size() / sizeOfElement);

	for (std::vector<int>::iterator jacob = jacobList.begin(); jacob != jacobList.end(); ++jacob)
	{
		nbToPlaceId = *jacob * sizeOfElement - 1;
		if (prevJacob > *jacob)
		{
			holding.push_back(prevId);
			pairId = nbToPlaceId + decalage;
			pairId += sizeOfElement * holdingToConsider(holding, pairId, sizeOfElement);
			prevId = placeNumber(main, pend, nbToPlaceId, pairId, sizeOfElement);
		}
		else if (prevJacob < *jacob)
		{
			if (*jacob != 1)
				decalage += sizeOfElement;
			decalage += holding.size() * sizeOfElement;
			holding.clear();

			pairId = nbToPlaceId + decalage;
			prevId = placeNumber(main, pend, nbToPlaceId, pairId, sizeOfElement);
		}
		prevJacob = *jacob;
	}
}

void
recursiveSort
(std::vector<int> &main, int sizeOfElement)
{
	std::vector<int> pend;

	swapMain(main, sizeOfElement);
	if (main.size() / (sizeOfElement) >= 2)
		recursiveSort(main, sizeOfElement * 2);
	pend = createPend(main, sizeOfElement);
	insertPend(main, pend, sizeOfElement);
}

void	PmergeMe::sort(char **numbers, int n)
{
	std::vector<int>	v;
	std::deque<unsigned int>	d;

	fillContainer(v, d, numbers, n);
	iter(v, print<unsigned int>);
	std::cout << std::endl;
	recursiveSort(v, 1);
	iter(v, print<unsigned int>);
	std::cout << std::endl;
}

PmergeMe
::PmergeMe
(void)
{
	throw (std::runtime_error("Should not be called !"));
}

PmergeMe
::PmergeMe
(const PmergeMe &copy)
{
	(void)copy;
	throw (std::runtime_error("Should not be called !"));
}

PmergeMe	&PmergeMe
::operator=
(const PmergeMe &rhs)
{
	(void)rhs;
	throw (std::runtime_error("Should not be called !"));
	return (*this);
}

PmergeMe
::~PmergeMe
(void){}
