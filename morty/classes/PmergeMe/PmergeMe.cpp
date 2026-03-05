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
