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
// BORNE EXCLUSIF ?? (+1)
int	placeNumber(std::vector<int> &main, std::vector<int> &pend, int nbToPlaceId, int borne, int sizeOfElement)
{
	std::vector<int>::iterator toInsertBegin = pend.begin() + nbToPlaceId - sizeOfElement + 1;
	std::vector<int>::iterator toInsertEnd = pend.begin() + nbToPlaceId + 1;

	int	toCompare = pend[nbToPlaceId];
	// me
	// cherche la borne inferieure du debut a la borne EXCLUE ?
	std::vector<int>::iterator place = StrideLowerBound(main.begin(), main.begin() + borne, toCompare, sizeOfElement);
	main.insert(place, toInsertBegin, toInsertEnd);

	std::vector<int>::difference_type i = place - main.begin();
	return i;
}

void
insertPend
(std::vector<int> &main, std::vector<int> pend, int sizeOfElement)
{
	std::vector<int> insertedSinceLastJacobsthal;
	int lastInsertedMain = 0;

	// cree l'ordre dans lequel les pends vont etre inseres
	std::vector<int> insertionOrder = createinsertionOrder<std::vector<int> >(pend.size() / sizeOfElement);

	// self explanatory
	// sera utile pour savoir si on est passe d'un jacob a un autre dans la liste ou si on a decremente entre deux
	int prevJacob = 0;

	// valeur de decalage a l'initialisation de PairId
	int mainShift = 0;

	// pour chaque pend dans la liste de jacob
	for (std::vector<int>::iterator jacob = insertionOrder.begin(); jacob != insertionOrder.end(); ++jacob)
	{
		// le dernier nombre de son element
		int pendToInsertId = *jacob * sizeOfElement - 1;
		// between 2 jacob
		if (prevJacob > *jacob)
		{
			// ajoute la paire precedente a holding
			insertedSinceLastJacobsthal.push_back(lastInsertedMain);
			// trouve la paire sans le decalge de holding
			int mainBoundInsertion = pendToInsertId + mainShift;
			// decale en fonction de holding
			considerPreviousInsertion(insertedSinceLastJacobsthal, mainBoundInsertion, sizeOfElement);
	
			// insere et edite lastInsertedMain a l'insertionm actuelle
			lastInsertedMain = placeNumber(main, pend, pendToInsertId, mainBoundInsertion, sizeOfElement);
		}
		// new jacob
		else if (prevJacob < *jacob)
		{
			// decale de 1 sizeof element a chaque nouveau jacob sauf le premier
			if (*jacob != 1)
				mainShift += sizeOfElement;
			// decale de taille de holding * sizeofelement
			// Pareil que de decaler de jacob actu - precedent jacob 
			// mais vu que la liste a ete generee avec les gradients decremente,
			// oblige de faire avec la taille de holding qui est egale au nombre d'iteration de l'autre if
			// et donc on doit push back holding au debut du if
			// (alors qu ele plus logique c'est apres linsertion pour arreter de trimballer lastInsertedMain dans le code)
			mainShift += insertedSinceLastJacobsthal.size() * sizeOfElement;
			insertedSinceLastJacobsthal.clear();

			// trouve la paire
			int mainBoundInsertion = pendToInsertId + mainShift;
			// insere et edite lastInsertedMain a l'insertion actuelle
			lastInsertedMain = placeNumber(main, pend, pendToInsertId, mainBoundInsertion, sizeOfElement);
		}
		prevJacob = *jacob;
	}
}

#include <iomanip>
void
recursiveSort
(std::vector<int> &main, int sizeOfElement)
{
	std::vector<int> pend;

	sort2By2(main, sizeOfElement);
	std::cout << std::left << std::setw(16) << "afterswap" << ": " << printContainer(main, sizeOfElement) << std::endl;
	if (main.size() / (sizeOfElement) >= 2)
		recursiveSort(main, sizeOfElement * 2);
	extractPend(main, pend, sizeOfElement);
	std::cout << std::left << std::setw(16) << "MAIN CHAIN" << ": " << printContainer(main, sizeOfElement) << std::endl;
	std::cout << std::left << std::setw(16) << "PENDING ELEMENTS" << ": " << printContainer(pend, sizeOfElement) << std::endl;
	insertPend(main, pend, sizeOfElement);
	std::cout << std::left << std::setw(16) << "ENDED WITH" << ": " << printContainer(main, sizeOfElement) << std::endl;
	std::cout << std::left << std::setw(16) << "SHOULD BE EMPTY" << ": " << printContainer(pend, sizeOfElement) << std::endl;
}

void	PmergeMe::sort(char **numbers, int n)
{
	std::vector<int>			v;
	std::deque<unsigned int>	d;

	fillContainer(v, d, numbers, n);
	std::cout << std::left << std::setw(16) << "before"<< ": "  << printContainer(v, 1) << std::endl;
	recursiveSort(v, 1);
	std::cout << std::left << std::setw(16) << "after"<< ": " << printContainer(v, 1) << std::endl;
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
