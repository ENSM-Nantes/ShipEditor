#include "BoatRow.hpp"
#include <giomm/file.h>
#include <gtkmm/picture.h>

BoatRow::BoatRow(Boat aBoatIn) : 
  mBox(Gtk::Orientation::HORIZONTAL, 10), 
  mNameLabel(aBoatIn.displayName)
{

  mBoat = aBoatIn;

  try {
    unsigned char extensionSize = 0;
      if(mBoat.mesh.fileName.substr(mBoat.mesh.fileName.size()-2) == ".x")
	{
	  extensionSize = 1;
	}
      else
	extensionSize = 3;
      
    auto file = Gio::File::create_for_path(mBoat.imgPath + "/" + mBoat.mesh.fileName.substr(0, mBoat.mesh.fileName.size() - extensionSize) + "jpg");
    auto texture = Gdk::Texture::create_from_file(file);
    mImage.set(texture);
  } catch (const Glib::Error& e) {
    auto file = Gio::File::create_for_path("../res/default.png");
    auto texture = Gdk::Texture::create_from_file(file);
    mImage.set(texture);
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

