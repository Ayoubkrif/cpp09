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

template<typename Container>
void	fordJohnsonSort(Container& sequence)
{
    size_t size = sequence.size();
    if (size <= 1)
        return;
    if (size == 2)
	{
        if (sequence[0] > sequence[1])
            std::swap(sequence[0], sequence[1]);
        return;
    }

	// determine unpaired element
    bool hasUnpairElement = (size % 2 == 1);
    int unpairElement = hasUnpairElement ? sequence[size - 1] : 0;

	// STEP 1 PAIR and SWAP
    size_t numberOfPairs = size / 2;
    std::vector< std::pair<int, int> > valuePairs;
    for (size_t pairIndex = 0; pairIndex < numberOfPairs; ++pairIndex)
	{
        if (sequence[2 * pairIndex] > sequence[2 * pairIndex + 1])
            valuePairs.push_back(std::make_pair(sequence[2 * pairIndex], sequence[2 * pairIndex + 1]));
        else
            valuePairs.push_back(std::make_pair(sequence[2 * pairIndex + 1], sequence[2 * pairIndex]));
    }
    if (valuePairs.size() > 1)
	{
        Container maxElems;
        for (size_t pairIndex = 0; pairIndex < valuePairs.size(); ++pairIndex)
            maxElems.push_back(valuePairs[pairIndex].first);
        
        fordJohnsonSort(maxElems);

        std::vector< std::pair<int, int> > orderedPairs(valuePairs.size());
        std::vector<bool> pairAlreadyUsed(valuePairs.size(), false);

        for (size_t maxIndex = 0; maxIndex < maxElems.size(); ++maxIndex) {
            for (size_t pairIndex = 0; pairIndex < valuePairs.size(); ++pairIndex) {
                if (!pairAlreadyUsed[pairIndex] && valuePairs[pairIndex].first == maxElems[maxIndex]) {
                    orderedPairs[maxIndex] = valuePairs[pairIndex];
                    pairAlreadyUsed[pairIndex] = true;
                    break;
                }
            }
        }
        valuePairs = orderedPairs;
    }
    Container sortedChain;

    if (!valuePairs.empty())
        sortedChain.push_back(valuePairs[0].second);

    for (size_t pairIndex = 0; pairIndex < valuePairs.size(); ++pairIndex)
        sortedChain.push_back(valuePairs[pairIndex].first);

    if (valuePairs.size() > 1) {
        std::vector<size_t> jacobsthalNumbers = generateJacobsthalSequence(valuePairs.size() + 2);
        std::vector<bool> alreadyInserted(valuePairs.size(), false);
        alreadyInserted[0] = true;

        for (size_t jacobIndex = 2; jacobIndex < jacobsthalNumbers.size(); ++jacobIndex) {
            size_t currentJacobsthal = jacobsthalNumbers[jacobIndex];
            size_t previousJacobsthal = jacobsthalNumbers[jacobIndex - 1];

            for (size_t pos = std::min(currentJacobsthal, valuePairs.size()); pos > previousJacobsthal && pos > 0; --pos) {
                size_t pairIndex = pos - 1;
                if (pairIndex < valuePairs.size() && !alreadyInserted[pairIndex]) {
                    size_t searchLimit = sortedChain.size();
                    for (size_t chainIndex = 0; chainIndex < sortedChain.size(); ++chainIndex) {
                        if (sortedChain[chainIndex] == valuePairs[pairIndex].first) {
                            searchLimit = chainIndex;
                            break;
                        }
                    }
                    
                    size_t insertIndex = findInsertionIndex(sortedChain, valuePairs[pairIndex].second, 0, searchLimit);
                    sortedChain.insert(sortedChain.begin() + insertIndex, valuePairs[pairIndex].second);
                    alreadyInserted[pairIndex] = true;
                }
            }
        }
        for (size_t pairIndex = 1; pairIndex < valuePairs.size(); ++pairIndex) {
            if (!alreadyInserted[pairIndex]) {
                size_t searchLimit = sortedChain.size();
                for (size_t chainIndex = 0; chainIndex < sortedChain.size(); ++chainIndex) {
                    if (sortedChain[chainIndex] == valuePairs[pairIndex].first) {
                        searchLimit = chainIndex;
                        break;
                    }
                }
                size_t insertIndex = findInsertionIndex(sortedChain, valuePairs[pairIndex].second, 0, searchLimit);
                sortedChain.insert(sortedChain.begin() + insertIndex, valuePairs[pairIndex].second);
            }
        }
    }
    if (hasUnpairElement) {
        size_t insertIndex = findInsertionIndex(sortedChain, unpairElement, 0, sortedChain.size());
        sortedChain.insert(sortedChain.begin() + insertIndex, unpairElement);
    }
    
    sequence = sortedChain;
}

/*static std::vector<unsigned int>*/
std::vector<std::pair<unsigned int, unsigned int> >
recursiveSort
(std::vector<std::pair<unsigned int, unsigned int> > &input)
{
	std::vector<std::pair<unsigned int, unsigned int> >	main;
	std::vector<std::pair<unsigned int, unsigned int> >	pend;
	for //for each pair:
	(unsigned int i = 0; (i + 1) * 2 <= input.size(); i++)
	{
	//COMPARE:
		// last number of the current element
		// last number of the next element
		if (input[(i * 2)].first > input[(i * 2) + 1]. first)
		{
			// put winners in main
			main.push_back(std::make_pair(input[(i * 2)].first, i));
			// others in pend
			pend.push_back(input[(i * 2) + 1 ]);
			// put larger at the end
			rotateRange(input, i * 2, (i * 2) + 1, (i + 1) * 2);
		}
		else
		{
			// put winners in main
			main.push_back(std::make_pair(input[(i * 2) + 1].first, i));
			// others in pend
			pend.push_back(input[(i * 2)]);
		}
	}
	if (input.size() % 2)
	{
		pend.push_back(input.at(input.size() - 1));
	}
	std::cout << "main: ";
	print(main);
	std::cout << std::endl;
	std::cout << "pend: ";
	print(pend);
	std::cout << std::endl;
	if // if we can pair elements made by ACTUAL pairs
	(2 <= main.size())
		recursiveSort(main);
	// jai un main trie avec l'index de son pend
	// jai un pend
	// je doit inserer tout les pends dans mon main
	return (main); // puis retourner le main pour l'appel du dessous
}
//
// problemes: une fois tries j'ai en second l'indice des mains casses
// et des pends pas casses.
// il faut pouvoir iterer sur les pends

void	PmergeMe::sort(char **numbers, int n)
{
	std::vector<std::pair<unsigned int, unsigned int> >	v;
	std::deque<std::pair<unsigned int, unsigned int> >	d;

	fillContainer(v, d, numbers, n);
	print(v);
	std::cout << std::endl;
	recursiveSort(v);
	// rotateRange(v, 0, v.size() / 2, v.size());
	print(v);
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
