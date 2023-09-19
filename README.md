# Notice - api_annuaire

**Groupe : Haithem, Aziz, Clément**

**Description** : programme en C permettant de lire un annuaire et de l'administrer (tri, insertion, suppression...)

## Prérequis

Ces packages sont nécessaires pour la compilation du projet.

- **gcc**
- **cmake**
- **make** (seulement sous Linux / MacOS)

Pour installer ces packages sous une distribution debian :
```
sudo apt install gcc make cmake;
```
Pour installer ces packages sous Windows :

- **gcc** : https://sourceforge.net/projects/mingw/
- **cmake** : https://cmake.org/download/

## Installation

Pour compiler le programme et obtenir un fichier executable, il faut invoquer cmake :

Sous Linux / MacOS :
```
cmake .
make
```
Sous Windows :
```
cmake -S /path/to/source-dir -B /path/to/build-dir
cmake --build /path/to/build-dir --config Release
```

## Utilisation

Une documentation Doxygen permet de voir l'utilité et une description des fonctions contenues dans ce programme.

Elle se trouve dans le dossier `html` du projet, il suffit de lancer `index.html` dans un navigateur.

```
Chemin complet : html/index.html
```
