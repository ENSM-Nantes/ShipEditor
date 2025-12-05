#ifndef SECTION_H
#define SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"


class Section: public Frame {
public:
  Section();
  Section(const Glib::ustring &label);
  ~Section();

  void load(Boat *b);
  virtual void update(void) = 0;
  virtual void reset(void) = 0;

protected:

  Boat mBoat;  
	
};


#endif
