#ifndef GPS_SECTION_H
#define GPS_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define GPS_INPUT_COUNT 1

using namespace Gtk;

class GpsSection: public Section {
public:
  GpsSection();
  ~GpsSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;
  InputArea mGps;
  InputArea *mInputList[GPS_INPUT_COUNT] = {&mGps};

};


#endif
