#include "BoatRow.hpp"

#include <giomm/file.h>
#include <gtkmm/picture.h>

BoatRow::BoatRow(Boat boat_in) : 
box(Gtk::Orientation::HORIZONTAL, 10), 
nameLabel(boat_in.displayName)
{

	boat = boat_in;

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

	// Mise en page
	box.set_margin_top(5);
	box.set_margin_bottom(5);
	box.set_margin_start(10);
	box.set_margin_end(10);
	box.set_valign(Gtk::Align::CENTER);

	// Ajout des widgets dans la ligne
	box.append(image);        // remplace pack_start
	box.append(nameLabel);

	// Ajouter le conteneur à la ligne
	set_child(box);           // remplace add()
}


BoatList::BoatList(): ListBox() {
	// ListBox qui recevra les BoatRow
	this->set_selection_mode(Gtk::SelectionMode::NONE);

	// Charger les bateaux depuis les JSON via BoatManager
	BoatManager manager;
	std::vector<Boat> boats = manager.loadBoats("../../FileConverter/transformation");

	// Remplir la ListBox avec des BoatRow
	for (Boat b : boats) {
		BoatRow* row = Gtk::manage(new BoatRow(b));
		this->append(*row);
	}
}