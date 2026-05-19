# CLAUDE.md — ex02 PmergeMe (Ford-Johnson)

## Règle 1 — Déplacement de fonctions

Quand tu déplaces une fonction d'un fichier à un autre, tu déplaces **aussi ses commentaires**.
Tu peux reformuler un commentaire s'il est peu clair, mais tu ne le supprimes pas.

## Règle 2 — Format des déclarations de fonctions

Les déclarations de fonctions s'écrivent sur **3 lignes** :

```
ret_type
name
(args)
```

Quand il y a un qualificateur de classe (méthode), **4 lignes** :

```
ret_type
ClassName::name
(args)
```

Exemples déjà présents dans le code :

```cpp
void
sort2By2
(std::vector<int> &main, std::vector<int>::size_type sizeOfElement)

PmergeMe
::PmergeMe
(void)
```

## Règle 3 — Algorithme Ford-Johnson (le vrai)

L'implémentation suit l'algorithme Ford-Johnson tel qu'il est codé dans `Ford-Johnson-algorithm/v2`.

### Les 3 étapes de la récursion (`recursiveSort` / `PMerge`)

1. **`sort2By2` / `swapMain`** — On parcourt les paires d'éléments (blocs de `sizeOfElement`).
   Pour chaque paire, on compare les représentants (dernier élément du bloc) et on met le plus grand après le plus petit.

2. **Récursion** — Si la chaîne contient encore ≥ 2 éléments (de taille `sizeOfElement * 2`), on rappelle la fonction avec `sizeOfElement * 2`.

3. **`extractPend` / `createPend`** — On sépare la chaîne en deux :
   - `main` : les éléments "gagnants" (les plus grands de chaque paire)
   - `pend` : les éléments "perdants" (les plus petits de chaque paire) + l'orphelin éventuel

4. **`insertPend`** — On insère les éléments de `pend` dans `main` en **binary insertion**, dans l'ordre dicté par la séquence de Jacobsthal (`createinsertionOrder` / `createJacobList`).

### Ordre d'insertion Jacobsthal

La liste d'insertion est générée par `createinsertionOrder<Container>(length)` :
- Terme initial : `1`
- On remplit entre deux termes de Jacobsthal en décrémentant
- Si un terme dépasse `length`, on le borne à `length`
- Formule du terme suivant : `next = current + 2 * prev`

### Binary insertion (`placeNumber` / `StrideLowerBound`)

Pour insérer un élément de `pend` :
- On cherche sa borne inférieure dans `main` avec `StrideLowerBound` (lower_bound adapté aux blocs de taille `sizeOfElement`)
- La borne de recherche est le représentant de la **paire associée dans `main`**, ajusté par `considerPreviousInsertion` pour tenir compte des insertions précédentes dans le même groupe Jacobsthal

### Gestion des insertions précédentes (`considerPreviousInsertion` / `holdingToConsider`)

Quand on descend entre deux termes de Jacobsthal (boucle décroissante), les insertions précédentes dans le même groupe décalent les indices dans `main`.
Pour chaque insertion précédente dont l'index est ≤ à l'index cible, on incrémente l'index cible de `sizeOfElement`.
