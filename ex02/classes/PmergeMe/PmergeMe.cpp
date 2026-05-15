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
sort2By2
(std::vector<int> &main, std::vector<int>::size_type sizeOfElement)
{
	std::vector<int> newMain;
	// alloc main size in vector
	newMain.reserve(main.size());
	int	step = sizeOfElement * 2;
	// for each pair of block of number (element)
	for (std::vector<int>::iterator secondRangeElementToCompare = main.begin() + step - 1;
	secondRangeElementToCompare < main.end();
	secondRangeElementToCompare += step)
	{
		std::vector<int>::iterator	firstRangeBegin = secondRangeElementToCompare + 1 - step;
		std::vector<int>::iterator	firstRangeEnd = firstRangeBegin + sizeOfElement;
		std::vector<int>::iterator	firstRangeElementToCompare = firstRangeEnd - 1;
		std::vector<int>::iterator	secondRangeBegin = firstRangeEnd;
		std::vector<int>::iterator	secondRangeEnd = secondRangeElementToCompare + 1;
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

// append pending elements that lost against greaters in pend chain
// trim them from main chain by putting it in newmain chain that is swapped
void
extractPend
(std::vector<int> &main, std::vector<int> &pend, int sizeOfElement)
{
	std::vector<int> newMain;
	// alloc main size in vector
	newMain.reserve(main.size());
	pend.reserve(main.size());
	int step = sizeOfElement * 2;
	// for each pair of block of number (element)
	for (std::vector<int>::iterator secondRangeElementToCompare = main.begin() + step - 1;
	secondRangeElementToCompare < main.end();
	secondRangeElementToCompare += step)
	{
		std::vector<int>::iterator	firstRangeBegin = secondRangeElementToCompare + 1 - step;
		std::vector<int>::iterator	firstRangeEnd = firstRangeBegin + sizeOfElement;
		std::vector<int>::iterator	secondRangeBegin = firstRangeEnd;
		std::vector<int>::iterator	secondRangeEnd = secondRangeElementToCompare + 1;
		// greater is already after smaller after swapMain
		// so second range goes to main, first range goes to pend
		newMain.insert(newMain.end(), secondRangeBegin, secondRangeEnd);
		pend.insert(pend.end(), firstRangeBegin, firstRangeEnd);
	}
	// append orphans in main
	newMain.insert(newMain.end(), main.begin() + newMain.size() + pend.size(), main.end());
	main.swap(newMain);
}

//binary insertion
int	placeNumber(std::vector<int> &main, std::vector<int> pend, int nbToPlaceId, int borne, int sizeOfElement)
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










/*
 * Variables:
 *		nbToPlaceId	(int)			: ?
 *		holding		(vector int)	: valeurs des insertions precedente ?
 *		sizeOfElement(int)			: valeur de decalage apres chaque comparaison reussie
 *		toAdd		(int)			: valeur retournee, commence a zero
 *
 * Resume:
 *		Pour chaque element dans holding:
 *			Si holding est plus petit que nbToPlaceId
 *				-decale nbToPlaceId de sizeOfElement
 *				-incremente toAdd
 * 
 *		retourne toAdd
 * */





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


























void
insertPend
(std::vector<int> &main, std::vector<int> pend, int sizeOfElement)
{
	std::vector<int> holding;
	int prevId = 0;

	// cree l'ordre dans lequel les pends vont etre inseres
	std::vector<int> jacobList = createJacobList<std::vector<int> >(pend.size() / sizeOfElement);

	// self explanatory
	// sera utile pour savoir si on est passe d'un jacob a un autre dans la liste ou si on a decremente entre deux
	int prevJacob = 0;

	// valeur de decalage a l'initialisation de PairId
	int decalage = 0;

	// pour chaque pend dans la liste de jacob
	for (std::vector<int>::iterator jacob = jacobList.begin(); jacob != jacobList.end(); ++jacob)
	{
		// le dernier nombre de son element
		int nbToPlaceId = *jacob * sizeOfElement - 1;
		// between 2 jacob
		if (prevJacob > *jacob)
		{
			// ajoute la paire precedente a holding
			holding.push_back(prevId);
			// trouve la paire sans le decalge de holding
			int pairId = nbToPlaceId + decalage;
			// decale en fonction de holding
			pairId += sizeOfElement * holdingToConsider(holding, pairId, sizeOfElement);
	
			// insere et edite prevId a l'insertionm actuelle
			prevId = placeNumber(main, pend, nbToPlaceId, pairId, sizeOfElement);
		}
		// new jacob
		else if (prevJacob < *jacob)
		{
			// decale de 1 sizeof element a chaque nouveau jacob sauf le premier
			if (*jacob != 1)
				decalage += sizeOfElement;
			// decale de taille de holding * sizeofelement
			// Pareil que de decaler de jacob actu - precedent jacob 
			// mais vu que la liste a ete generee avec les gradients decremente,
			// oblige de faire avec la taille de holding qui est egale au nombre d'iteration de l'autre if
			// et donc on doit push back holding au debut du if
			// (alors qu ele plus logique c'est apres linsertion pour arreter de trimballer prevId dans le code)
			decalage += holding.size() * sizeOfElement;
			holding.clear();

			// trouve la paire
			int pairId = nbToPlaceId + decalage;
			// insere et edite prevId a l'insertionm actuelle
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

	sort2By2(main, sizeOfElement);
	if (main.size() / (sizeOfElement) >= 2)
		recursiveSort(main, sizeOfElement * 2);
	extractPend(main, pend, sizeOfElement);
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
