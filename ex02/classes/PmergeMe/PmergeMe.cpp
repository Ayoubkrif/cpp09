/* ************************************************************************** */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:44:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include <algorithm>
#include <deque>
#include <vector>
#include "PmergeMe.hpp"

void
swapMain
(std::vector<int> &main, std::vector<int>::size_type sizeOfElement)
{
	for (int i = sizeOfElement - 1; i + sizeOfElement < main->size(); i += sizeOfElement * 2)
	{
		if (main[i] > main[i + sizeOfElement])
		{
			swap(main, sizeOfElement, i, i + sizeOfElement);
		}
		// VectComp++;
	}
}

std::vector<int>
createPend
(std::vector<int> &main, int sizeOfElement)
{
	std::vector<int> pend;
	int i = 0;
	std::vector<int>::size_type maxPair = (main.size() / sizeOfElement); //division is usefull to remove non complete elements

	std::vector<int>::iterator it = main.begin();
	while (it != main.end() && pend.size() < maxPair * sizeOfElement)
	{
		if (std::distance(it, main.end()) < sizeOfElement && i == 0)
			break;
		if (i == sizeOfElement)
		{
			i = 0;
			it += sizeOfElement;
		}
		else
		{
			pend.push_back(*it);
			it = main.erase(it);
			i += 1;
		}
	}
	return pend;
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
