#pragma once

#include <gtkmm.h>
#include "BoatManager.hpp"  // Contient la définition de la classe Boat

/**
 * @brief Représente une ligne dans le menu déroulant des presets de bateaux.
 * 
 * Chaque ligne contient :
 * - Une image à gauche (par défaut : ressources/default.png)
 * - Le nom du bateau au centre
 * - Un bouton "..." à droite pour des actions contextuelles
 */
class BoatRow : public Gtk::ListBoxRow {
public:
    /**
     * @brief Constructeur
     * @param boat Instance de Boat contenant les données à afficher
     */
    BoatRow(const Boat& boat);

private:
    // Conteneur horizontal principal
    Gtk::Box box;

    // Image du bateau (icône ou miniature)
    Gtk::Image image;

    // Nom du bateau
    Gtk::Label nameLabel;

    // Bouton contextuel "..."
    Gtk::Button menuButton;
};