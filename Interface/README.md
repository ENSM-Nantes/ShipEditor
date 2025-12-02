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
- **C++** 
- **WSL** 

## Dépendances
```
sudo apt-get install libgtk-4-dev libgtkmm-4.0-dev libjsoncpp-dev
```

## Compilation
Dans le dossier Interface créez une première fois le dossier build et allez à l'intérieur:
```
mkdir build
cd build
```

Exécutez la commande suivante pour créer les fichiers nécessaire pour la compilation:
```
cmake ../src
```

Nous allons ensuite compiler le porgramme avec la commande suivante. A chaque fois que vous voulez recompiler le programme éxécutez la.
```
make
```

## Exécution
Pour éxécuter le programme après l'avoir compiler, il faut aller dans le dossier build et éxécuter le fichier *ShipEditor*
