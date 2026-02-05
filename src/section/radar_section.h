#ifndef RADAR_SECTION_H
#define RADAR_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define RADAR_INPUT_COUNT 4

using namespace Gtk;

class RadarSection: public Section {
public:
  RadarSection();
  ~RadarSection();

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;
  InputArea mTilt, mSize, mRadar, mPos;
  InputArea *mInputList[RADAR_INPUT_COUNT] = {&mTilt, &mSize, &mRadar, &mPos};

};


#endif
