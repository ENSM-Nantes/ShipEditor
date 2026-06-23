#ifndef BOAT_ROW_H
#define BOAT_ROW_H

#include <gtkmm.h>
#include "BoatManager.hpp" 

#ifdef _WIN32
#define PATH_JSON_BOATS ("C:\\Program Files\\Bridge Command SOMOS 3.1\\resources\\models\\Ships\\")
#else
#define PATH_JSON_BOATS ("../../bc/resources/models/Ships/")
//#define PATH_JSON_BOATS ("../bridgecommand/models/Ownship/")
#endif

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
