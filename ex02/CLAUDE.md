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
ClassName
::name
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

### Les étapes de la récursion (`recursiveSort`)

> **OPTI :** On extrait les nombres ne formant pas un élément complet (`extractCrumbs`), puis on les réattache au retour (`appendCrumbs`).

1. **`sort2By2`** — On parcourt les paires d'éléments (blocs de `sizeOfElement`). Pour chaque paire, on compare les représentants (dernier élément du bloc) et on swap pour mettre le plus grand après le plus petit.
   > **STABLE** — ne pas modifier.

2. **Récursion** — Si la chaîne contient ≥ 4 éléments (de taille `sizeOfElement * 2`), on rappelle la fonction avec `sizeOfElement * 2`.

   > **OPTI :** Si `numberOfElements < 3`, pas de pend possible — on retourne directement.

3. **`extractPend`** — On sépare la chaîne en deux :
   - `main` : le premier perdant + tous les gagnants
   - `pend` : les autres perdants + l'orphelin éventuel (dernier élément si nombre d'éléments impair)

4. **`insertPend`** — On insère les éléments de `pend` dans `main` par **binary insertion**, dans l'ordre dicté par la séquence de Jacobsthal (`createinsertionOrder`).

### Ordre d'insertion Jacobsthal

La liste est générée par `createinsertionOrder<Container>(length)`.

Le premier perdant est déjà trié dans la main chain, donc on commence à l'**index 1** (2ème terme de Jacobsthal = 3), puis on décrémente jusqu'au terme précédent, etc. Les valeurs sont des indices 0-indexés dans `pend`.

Exemple pour 9 pend à insérer (10 perdants dont le premier est dans main) :
```
indices pend : 1, 0, 3, 2, 8, 7, 6, 5, 4
```
On insère le 2ème élément, puis le 1er, puis le 4ème, etc.

> **STABLE** — ne pas modifier.

### Binary insertion (`placeNumber` / `StrideLowerBound`)

Pour insérer un élément de `pend` :
- On cherche sa borne inférieure dans `main` avec `StrideLowerBound` (lower_bound adapté aux blocs de taille `sizeOfElement`).
- La borne de recherche (`mainBoundInsertion`) est le représentant de la **paire associée dans `main`**, calculée dans `insertPend`.
- **Cas orphelin :** si l'élément est le dernier de `pend` et que le total est impair, il n'a pas de paire associée — sa borne est `main.size() - 1` (recherche dans tout le main jusqu'à `main.end()`).

### Gestion des insertions précédentes (`insertionIndexesSinceLastJacobsthal`, `mainShift`, `mainBoundInsertion`)

Quand on descend entre deux termes de Jacobsthal (boucle décroissante), les insertions précédentes dans le même groupe décalent les positions dans `main`.
- `mainShift` : décalage de base accumulé entre deux groupes Jacobsthal.
- `insertionIndexesSinceLastJacobsthal` : positions des insertions dans le groupe courant, utilisées par `considerPreviousInsertion` pour ajuster `mainBoundInsertion`.
- `insertionIndex` : position effective dans `main` après insertion, enregistrée pour les prochains éléments du groupe.
