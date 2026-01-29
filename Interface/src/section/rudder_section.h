#ifndef RUDDER_SECTION_H
#define RUDDER_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define RUDDER_INPUT_COUNT 4

using namespace Gtk;

class RudderSection: public Section {
public:
  RudderSection();
  ~RudderSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;

  InputArea mSpanLenght, mAreaMobile, mAspectRatio, mMaxSpeed;

  InputArea *mInputList[RUDDER_INPUT_COUNT] = {&mSpanLenght, &mAreaMobile, &mAspectRatio, &mMaxSpeed};

};


#endif
