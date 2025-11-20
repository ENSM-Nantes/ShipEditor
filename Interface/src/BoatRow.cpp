#include "BoatRow.hpp"
#include <iostream> // a été utile pour debug donc je le laisse au cas où
#include <giomm/file.h>
#include <gtkmm/picture.h>

BoatRow::BoatRow(const Boat& boat) : 
box(Gtk::Orientation::HORIZONTAL, 10), 
nameLabel(boat.displayName), 
menuButton("⋯") // Unicode pour "..."
{
    // Charger une image par défaut
    try {
        auto file = Gio::File::create_for_path("../ressources/default.png");
        auto texture = Gdk::Texture::create_from_file(file);
        image.set(texture);
    } catch (const Glib::Error& e) {
        std::cerr << "Erreur chargement image : " << e.what() << std::endl;
    }

    // Définir une taille fixe pour l'image (optionnel)
    image.set_pixel_size(12);

    // Mise en page
    box.set_margin_top(5);
    box.set_margin_bottom(5);
    box.set_margin_start(10);
    box.set_margin_end(10);
    box.set_valign(Gtk::Align::CENTER);

    // Ajout des widgets dans la ligne
    box.append(image);        // remplace pack_start
    box.append(nameLabel);
    box.append(menuButton);

    // Ajouter le conteneur à la ligne
    set_child(box);           // remplace add()

    // show_all_children() supprimé en GTK 4
}