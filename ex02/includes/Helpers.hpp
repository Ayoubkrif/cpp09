/* ************************************************************************** */
/*   Helpers.hpp                                                              */
/*   By: aykrifa <aykrifa@student.42.fr>                                      */
/* ************************************************************************** */

#pragma once

#include <set>
#include <iostream>

// 1) Vérifie si un container est trié (ordre croissant)
template <typename Container>
bool
isSorted
(const Container& c)
{
    typename Container::const_iterator it = c.begin();
    if (it == c.end()) return true;
    typename Container::const_iterator next = it;
    ++next;
    for (; next != c.end(); ++it, ++next) {
        if (*next < *it) return false;
    }
    return true;
}

// 2) Vérifie que le container a exactement les mêmes éléments que le multiset
//    (mêmes valeurs ET mêmes multiplicités, ordre indifférent)
template <typename T, typename Container>
bool
sameElements
(const std::multiset<T>& ref, const Container& c)
{
    if (ref.size() != static_cast<typename std::multiset<T>::size_type>(
                          std::distance(c.begin(), c.end())))
        return false;
    std::multiset<T> other(c.begin(), c.end());
    return ref == other;
}

// surcharge pour imprimer le contenu des containers en fonction de la taille d'un element 
template <typename Container>
struct ContainerPrinter
{
    const Container& container;
    int sizeOfElement;

    ContainerPrinter(const Container& c, int s)
        : container(c), sizeOfElement(s) {}
};

template <typename Container>
ContainerPrinter<Container>
printContainer
(const Container& c, int s)
{
    return ContainerPrinter<Container>(c, s);
}

template <typename Container>
std::ostream&
operator<<
(std::ostream& os, const ContainerPrinter<Container>& p)
{
    int count = 0;
    for (typename Container::const_iterator it = p.container.begin();
         it != p.container.end(); ++it)
    {
        if (count != 0)
        {
            if (p.sizeOfElement == 0)
                os << ",";
            else if (count % (p.sizeOfElement * 2) == 0)
                os << "|";
            else if (count % p.sizeOfElement == 0)
                os << ",";
            else
                os << " ";
        }
        os << *it;
        ++count;
    }
    return os;
}
