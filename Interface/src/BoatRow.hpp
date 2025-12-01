#ifndef BOAT_ROW_H
#define BOAT_ROW_H

#include <gtkmm.h>
#include "BoatManager.hpp"  // Contient la définition de la classe Boat


using namespace Gtk;

/**
 * @brief Représente une ligne dans le menu déroulant des presets de bateaux.
 * 
 * Chaque ligne contient :
 * - Une image à gauche (par défaut : ressources/default.png)
 * - Le nom du bateau au centre
 * - Un bouton "..." à droite pour des actions contextuelles
 */
class BoatRow : public ListBoxRow {
public:
	/**
	 * @brief Constructeur
	 * @param boat Instance de Boat contenant les données à afficher
	 */
	BoatRow(Boat boat_in);
	~BoatRow() {}

	Boat boat;

private:
	// Conteneur horizontal principal
	Box box;

	// Image du bateau (icône ou miniature)
	Image image;

	// Nom du bateau
	Label nameLabel;
};

class BoatList: public ListBox {
public:
	BoatList();
	~BoatList() {}	
};


#endif