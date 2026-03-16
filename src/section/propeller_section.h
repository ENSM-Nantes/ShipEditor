#ifndef PROPELLER_SECTION_H
#define PROPELLER_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define PROPELLER_INPUT_COUNT 5

using namespace Gtk;

class PropellerSection: public Section {
public:
  PropellerSection();
  ~PropellerSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;

  InputArea mNumber, mSpacing, mDiameter, mForwardRotDir, mBackwardEff;
  InputArea *mInputList[PROPELLER_INPUT_COUNT] = {&mNumber, &mSpacing, &mDiameter, &mForwardRotDir, &mBackwardEff};

};


#endif
