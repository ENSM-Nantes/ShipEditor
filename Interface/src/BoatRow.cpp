#include "BoatRow.hpp"
#include <iostream> // a été utile pour debug donc je le laisse au cas où

BoatRow::BoatRow(const Boat& boat) : 
box(Gtk::ORIENTATION_HORIZONTAL, 10), 
nameLabel(boat.displayName), 
menuButton("⋯") // Unicode pour "..."
{
    // Définir une taille fixe pour l'image (optionnel)
    image.set_pixel_size(48);

    // Charger une image par défaut
    try {
        image.set("ressources/default.png"); // Attention à ne pas modifier ce chemin
    } catch (const Glib::FileError& e) {
        std::cerr << "Erreur chargement image : " << e.what() << std::endl;
    }

    // Mise en page
    box.set_margin_top(5);
    box.set_margin_bottom(5);
    box.set_margin_start(10);
    box.set_margin_end(10);
    box.set_valign(Gtk::ALIGN_CENTER);

    // Ajout des widgets dans la ligne
    box.pack_start(image, Gtk::PACK_SHRINK);
    box.pack_start(nameLabel, Gtk::PACK_EXPAND_WIDGET);
    box.pack_start(menuButton, Gtk::PACK_SHRINK);

    // Ajouter le conteneur à la ligne
    add(box);

    // Afficher tous les enfants
    show_all_children();
}