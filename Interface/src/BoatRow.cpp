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
    image.set_pixel_size(24);
    image.set_valign(Gtk::Align::CENTER);
    image.set_halign(Gtk::Align::START);

    // Mise en page
    box.set_margin_top(5);
    box.set_margin_bottom(5);
    box.set_margin_start(10);
    box.set_margin_end(10);
    box.set_valign(Gtk::Align::CENTER);

    // Ajuster comportements d'expansion / alignement pour une jolie mise en page
    nameLabel.set_halign(Gtk::Align::CENTER);
    // Demander à ce que le label prenne l'espace horizontal disponible
    nameLabel.set_hexpand(true);

    menuButton.set_halign(Gtk::Align::END);
    menuButton.set_valign(Gtk::Align::CENTER);

    // Ajout des widgets dans la ligne (image à gauche, label centré expansé, bouton à droite)
    box.append(image);
    box.append(nameLabel);
    box.append(menuButton);

    // Ajouter le conteneur à la ligne
    set_child(box);           // remplace add()

    // show_all_children() supprimé en GTK 4
}