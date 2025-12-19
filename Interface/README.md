# Interface GTK - Simulateur de navigation SOMOS (ENSM)

Bienvenue dans le dossier `Interface` du projet SOMOS, développé par deux étudiants de Centrale Nantes avec des enseignants de l'École Nationale Supérieure Maritime (ENSM). Ce module constitue une des interfaces graphiques du simulateur de navigation en haute mer, conçu pour offrir une expérience immersive et pédagogique aux utilisateurs.

## 🌊 Contexte

Le projet SOMOS vise à modéliser et simuler des scénarios de navigation réalistes en haute mer. L'interface GTK permet aux utilisateurs d'interagir avec le simulateur via une interface intuitive, réactive et adaptée aux besoins de la formation maritime.

## 🧭 Fonctionnalités principales

- Pouvoir choisir facilement un des bâteaux utilisables
- Pouvoir observer quels bâteaux sont utilisables
- Modifier les presets de bâteaux, ajouter/supprimer/customiser des presets
- Pouvoir observer les caractéristiques des différents presets des bâteaux
- Modéliser le bâteaux du preset choisi

## 🛠️ Technologies utilisées

- **GTK 4** 
- **C / C++** 
- **MSYS** Pour run et tester nos codes sur Windows
- **Raspberry Pi** pour tester nos codes sur Linux

## Compilation
Dans le dossier Interface créez une première fois le dossier build et allez à l'intérieur:
```
mkdir build
cd build
```

Exécutez la commande suivante pour créer les fichiers nécessaire pour la compilation:
```
cmake -G"Unix Makefiles" ../src/
```

Nous allons ensuite compiler le porgramme avec la commande suivante. A chaque fois que vous voulez recompiler le programme éxécutez la.
```
make
```

## Exécution
Pour éxécuter le programme après l'avoir compiler, il faut aller dans le dossier build et éxécuter le fichier *ShipEditor*

# Informations

## Fonctionnalités réalisées

- liste des bateaux
- éditions des variables
- enregistrement des données
- lecture des données
- ajout de nouveaux bateaux
- renommage des bateaux
- popup informant une erreur de formatage
- popup informant des données non enregistrées
- popup informant le bon/mauvais enregistrement des données

## Bugs / informations

- le renommage crée un nouveau dossier au lieu de le renommer
- le bouton *delete* n'effectue aucune action
- seul la virgule est valide pour les nombres réelles: l'utilisation du point ne fera que tronquer la partie décimale
- l'insertion d'une chaine de caractères après un nombre ne fait pas appaître d'erreur de formatage, seul le nombre est convertit jusqu'à la chaine de caractère et le reste n'est pas pris en compte
- l'ajout ou la suppression d'élément d'une liste tel que pour *pano* n'est pas réversible: l'action effectue une modification directement dans la copie locale du bateau
- certains champs ont une valeur abérante, proposition: le champ n'était pas initialisé dans le fichier

## Fonctionnalités à prévoir

- suppression de bateaux
- visualisation 3D du bateau ou une image
- voir les champs non enregistrés
