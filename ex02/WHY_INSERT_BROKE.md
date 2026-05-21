# Pourquoi `placeNumber` cassait le tri sur `deque`

## Le code fautif

```cpp
main.insert(place, toInsertBegin, toInsertEnd);          // ← insert

typename Container::difference_type i = place - main.begin(); // ← UB ici
return i;
```

## Ce que fait `main.insert(place, ...)`

`insert` glisse les éléments existants pour faire de la place, puis écrit le nouveau bloc.  
Après cet appel, **`place` n'est plus un itérateur valide** — la norme C++ dit qu'il est *invalidé*.

## Pourquoi ça marchait quand même sur `vector`

Un `vector` stocke ses éléments dans **un seul bloc contigu en mémoire**.  
Quand on insère sans réallocation, les éléments à droite de `place` sont décalés d'un cran,
mais l'adresse mémoire que `place` contenait n'a pas bougé.  
Le standard dit que l'itérateur est "invalide", mais en pratique sur toutes les implémentations :
- `place` pointe sur le premier élément inséré (qui vient d'être écrit à cette adresse)
- `place - main.begin()` donne donc l'index d'insertion — c'est la bonne valeur

**C'est un accident.** Le comportement est indéfini selon le standard, mais prévisible sur vector.

## Pourquoi ça explosait sur `deque`

Un `deque` est fait de **plusieurs blocs discontinus** reliés par un tableau de pointeurs.  
Insérer au milieu peut :
- réorganiser les blocs internes
- déplacer le tableau de pointeurs
- changer la base de calcul des offsets

Après l'insert, `place` peut pointer vers n'importe quoi.  
`place - main.begin()` retourne une valeur aléatoire.

Cette valeur est stockée dans `insertionIndexesSinceLastJacobsthal` et utilisée par
`considerPreviousInsertion` pour ajuster les bornes des insertions suivantes.  
Avec des bornes fausses, les éléments sont insérés au mauvais endroit → tri corrompu.

L'aspect "certaines fois" venait du fait que pour de petites entrées ou certains ordres,
le garbage retourné tombait par chance sur la bonne valeur.

## Le fix

```cpp
// calculé AVANT l'insert — place est encore valide
typename Container::difference_type i = place - main.begin();

main.insert(place, toInsertBegin, toInsertEnd);

return i;
```

`place - main.begin()` avant l'insert donne l'index de la position d'insertion dans `main`.
C'est exactement ce dont `insertPend` a besoin pour les insertions suivantes.
L'insert ne change pas cet index — il le confirme.

## Règle à retenir

> Après un `insert` sur n'importe quel container standard,
> tout itérateur qui pointait dans ce container est **invalide**.
> Pour `vector` sans réallocation c'est un accident heureux.
> Pour `deque`, c'est toujours cassé.
> Calculer ce dont on a besoin **avant** l'insert, pas après.
