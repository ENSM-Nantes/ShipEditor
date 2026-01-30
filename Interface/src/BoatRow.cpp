#include "BoatRow.hpp"
#include <giomm/file.h>
#include <gtkmm/picture.h>

BoatRow::BoatRow(Boat aBoatIn) : 
  mBox(Gtk::Orientation::HORIZONTAL, 10), 
  mNameLabel(aBoatIn.displayName)
{

  mBoat = aBoatIn;

  try {
    auto file = Gio::File::create_for_path("../ressources/default.png");
    auto texture = Gdk::Texture::create_from_file(file);
    mImage.set(texture);
  } catch (const Glib::Error& e) {
    std::cerr << "Erreur chargement image : " << e.what() << std::endl;
  }

  // Définir une taille fixe pour l'image (optionnel)
  mImage.set_pixel_size(24);

  // Mise en page
  mBox.set_margin_top(5);
  mBox.set_margin_bottom(5);
  mBox.set_margin_start(10);
  mBox.set_margin_end(10);
  mBox.set_valign(Gtk::Align::CENTER);

  // Ajout des widgets dans la ligne
  mBox.append(mImage);        // remplace pack_start
  mBox.append(mNameLabel);

  // Ajouter le conteneur à la ligne
  set_child(mBox);           // remplace add()
}


BoatList::BoatList(): ListBox() {
  // ListBox qui recevra les BoatRow
  set_selection_mode(Gtk::SelectionMode::NONE);
  
  mBoats = BoatManager::LoadBoats("../../FileConverter/transformation");

  // Remplir la ListBox avec des BoatRow
  for (Boat b : mBoats)
    {
      BoatRow* row = Gtk::manage(new BoatRow(b));
      this->append(*row);
    }
}

BoatList::~BoatList()
{
  for(unsigned char i=0;i<mBoats.size();i++)
    { 
      delete get_row_at_index(i);
    }
}
