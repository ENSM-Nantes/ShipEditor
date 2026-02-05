#ifndef BOAT_ROW_H
#define BOAT_ROW_H

#include <gtkmm.h>
#include "BoatManager.hpp" 

#define PATH_JSON_BOATS ("../res/boats/")

class BoatRow : public Gtk::ListBoxRow {
public:
  BoatRow(Boat aBoatIn);
  Boat mBoat;

protected:

  Gtk::Box mBox;
  Gtk::Image mImage;
  Gtk::Label mNameLabel;
};


#endif
