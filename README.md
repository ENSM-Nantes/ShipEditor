# Ship Editor

## Fonctionnalités principales
- Pouvoir choisir facilement un des bâteaux utilisables
- Pouvoir observer quels bâteaux sont utilisables
- Modifier les presets de bâteaux, ajouter/supprimer/customiser des presets
- Pouvoir observer les caractéristiques des différents presets des bâteaux

## Dépendances Linux
```
sudo apt-get install libgtk-4-dev libgtkmm-4.0-dev libjsoncpp-dev
```

## Dépendances Windows
- Installer MYS2

```
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gtk4
pacman -S mingw-w64-ucrt-x86_64-gtkmm-4.0
pacman -S mingw-w64-ucrt-x86_64-jsoncpp
pacman -S mingw-w64-ucrt-x86_64-cmake
pacman -S mingw-w64-ucrt-x86_64-toolchain

```

## Compilation sur Linux
```
mkdir build
cd build
cmake ../src
make
```

## Compilation sur Windows
```
cd src
windres resources.rc -o resources.o
cd ..
mkdir build
cd build
cmake ../src
cmake --build .
```

##Génération installeur Win64
- Exécuter install.nsi depuis install/

## Example
![alt text](https://github.com/ENSM-Nantes/ShipEditor/blob/main/res/Screenshot_ShipEditorv2.png)