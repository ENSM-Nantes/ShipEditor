#ifndef BOAT_ROW_H
#define BOAT_ROW_H

#include <gtkmm.h>
#include "BoatManager.hpp" 

class BoatRow : public Gtk::ListBoxRow {
public:
  BoatRow(Boat aBoatIn);
  Boat mBoat;

protected:

  Gtk::Box mBox;
  Gtk::Image mImage;
  Gtk::Label mNameLabel;
};

class BoatList: public Gtk::ListBox {
public:
  BoatList();
  ~BoatList();


private:

  std::vector<Boat> mBoats;
};


#endif
