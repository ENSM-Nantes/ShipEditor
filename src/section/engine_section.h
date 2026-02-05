#ifndef ENGINE_SECTION_H
#define ENGINE_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define ENGINE_INPUT_COUNT 6

using namespace Gtk;

class EngineSection: public Section {
public:
  EngineSection();
  ~EngineSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;

  InputArea mNumber, mBrand, mType, mPower, mRpmMax, mFuelCons;
  InputArea *mInputList[ENGINE_INPUT_COUNT] = {&mNumber, &mBrand, &mType, &mPower, &mRpmMax, &mFuelCons};

};


#endif
