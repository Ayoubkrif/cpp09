/* ************************************************************************** */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*   Created: 2026/02/22 11:44:41 by aykrifa           #+#    #+#             */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "utils.hpp"
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

#include <algorithm>
#include <deque>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

int g_comparisons = 0;

static bool
countComp
(int a, int b)
{
	g_comparisons++;
	return a < b;
}

// Put greaters elements of the main chain after smallers
void
sort2By2
(std::vector<int> &main, std::vector<int>::size_type sizeOfElement)
{
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
		// Compare last number of each elements
		if (countComp(*secondRangeElementToCompare, *firstRangeElementToCompare))
			// Put smaller before larger
			std::swap_ranges(firstRangeBegin, firstRangeEnd, secondRangeBegin);
	}
}

// append pending elements that lost against greaters in pend chain
// trim them from main chain by putting it in newmain chain that is swapped
// so i need to put the first element in the main / i don't need to call this function if there is less than 3 element
void
extractPend
(std::vector<int> &main, std::vector<int> &pend, int sizeOfElement)
{
	std::vector<int> newMain;
	// alloc main size in vector
	newMain.reserve(main.size() + sizeOfElement);
	// new main chain is composed by first element + odd element
	newMain.insert(newMain.end(), main.begin(), main.begin() + sizeOfElement);

	pend.reserve(main.size() / 2);

	bool	even = true;

	// for each pair of block of number (element)
	for (std::vector<int>::iterator rangeBegin = main.begin() + 2 * sizeOfElement; rangeBegin != main.end(); rangeBegin += sizeOfElement)
	{
		std::vector<int>::iterator rangeEnd = rangeBegin + sizeOfElement;

		// pending elements are even elements except first one
		if (even)
			pend.insert(pend.end(), rangeBegin, rangeEnd);

		// new main chain is composed by first element + odd element
		else
			newMain.insert(newMain.end(), rangeBegin, rangeEnd);

		even = !even;
	}
	main.swap(newMain);
}

//binary insertion
// BORNE EXCLUSIF ?? (+1)
int
placeNumber
(std::vector<int> &main, std::vector<int> &pend, int nbToPlaceId, int borne, int sizeOfElement)
{
	std::vector<int>::iterator toInsertBegin = pend.begin() + nbToPlaceId - sizeOfElement + 1;
	std::vector<int>::iterator toInsertEnd = pend.begin() + nbToPlaceId + 1;

	int	toCompare = pend[nbToPlaceId];
	// me
	// orphan has no winner pair: borne may exceed main.size(), clamp to end
	std::vector<int>::iterator searchEnd = main.begin() + borne + 1;
	if (searchEnd > main.end())
		searchEnd = main.end();
	std::vector<int>::iterator place = StrideLowerBound(main.begin(), searchEnd, toCompare, sizeOfElement, countComp);
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

	std::cout << "size of jacob:" << insertionOrder.size() << std::endl;
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
			std::cout << "mainBoundInsertion = " << mainBoundInsertion << std::endl;
			lastInsertedMain = placeNumber(main, pend, pendToInsertId, mainBoundInsertion, sizeOfElement);
		}
		prevJacob = *jacob;
	}
}

#include <iomanip>

void
appendCrumbs
(std::vector<int> &main, const std::vector<int> &crumbs)
{
	main.insert(main.end(), crumbs.begin(), crumbs.end());
}

// extract incomplete trailing block (miettes) into crumb, trim main to complete blocks only
void
extractCrumbs
(std::vector<int> &main, std::vector<int> &crumbs, int sizeOfElement, int numberOfElements)
{
	std::vector<int>::size_type completeSize = numberOfElements * sizeOfElement;
	crumbs.assign(main.begin() + completeSize, main.end());
	main.erase(main.begin() + completeSize, main.end());
}

void
recursiveSort
(std::vector<int> &main, int sizeOfElement)
{
	std::cout << std::left << std::setw(16) << "complete chain" << ": " << printContainer(main, sizeOfElement) << std::endl;
	int	numberOfElements = main.size() / sizeOfElement;

	// SAFE
	// extract crumb to not handle it in this recursion level
	// crumb are numbers that are too few to compose an element
	std::vector<int> crumbs;
	extractCrumbs(main, crumbs, sizeOfElement, numberOfElements);

	// SAFE
	// determine the greater 2 by 2
	// then swap the greater right to the smaller
	sort2By2(main, sizeOfElement);

	std::cout << std::left << std::setw(16) << "after swap" << ": " << printContainer(main, sizeOfElement) << std::endl;
	
	// SAFE
	// if there is less than 3 element,
	// elements already sorted
	// ie no pend
	if (numberOfElements < 3)
		return ;

	// SAFE
	// if we can compose at least 2 pair, recursively launch the algoritm
	if (numberOfElements >= 4)
		recursiveSort(main, sizeOfElement * 2);

	std::cout << std::left << std::setw(16) << "after recursion" << ": " << printContainer(main, sizeOfElement) << std::endl;
	
	// SAFE BUT should put the element that lost against smaller main first in the main chain
	// extract pending element that has to be inserted in the main chain = losers of sort2By2 + unpaired element
	std::vector<int> pend;
	extractPend(main, pend, sizeOfElement);
	std::cout << std::left << std::setw(16) << "Main chain" << ": " << printContainer(main, sizeOfElement) << std::endl;
	std::cout << std::left << std::setw(16) << "Pending Elements" << ": " << printContainer(pend, sizeOfElement) << std::endl;
	
	// UNSAFE BUG COME FROM HERE
	// insert pending element into main chain:
		// in the right insertion order
		// following the bound of each element
	// to decrease comparison
	insertPend(main, pend, sizeOfElement);

	// SAFE
	// append crumb that we extracted before to handle it in a lower recursion
	appendCrumbs(main, crumbs);
}

void	PmergeMe::sort(char **numbers, int n)
{
	std::vector<int>			v;
	std::deque<unsigned int>	d;

	std::vector<int> j = createinsertionOrder<std::vector<int> >(9);
	std::cout << std::left << std::setw(16) << "list"<< ": "  << printContainer(j, 0) << std::endl;
	
	return; 
	fillContainer(v, d, numbers, n);
	std::multiset<unsigned int>	ref(v.begin(), v.end());
	int max = maxComp(n);
	g_comparisons = 0;
	std::cout << std::left << std::setw(16) << "list"<< ": "  << printContainer(v, 0) << std::endl;
	recursiveSort(v, 1);
	if (!isSorted(v) || !sameElements(ref, v))
		throw (std::runtime_error("OOPS"));
	if (g_comparisons > max)
		throw (std::runtime_error("Too many comparisons"));
	std::cout << std::left << std::setw(16) << "sorted list"<< ": " << printContainer(v, 1) << std::endl;
	std::cout << std::left << std::setw(16) << "comparisons" << ": " << g_comparisons << "/" << max << std::endl;
}

