#ifndef PHYSICAL_SECTION_H
#define PHYSICAL_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define PHYSICAL_INPUT_COUNT 7

using namespace Gtk;

class PhysicalSection: public Section {
public:
  PhysicalSection();
  ~PhysicalSection();

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;
  InputArea mRho, mLength, mBreadth, mDraught, mCoeffBlock, mSubWaterVolume, mGravityCenter;
  InputArea *mInputList[PHYSICAL_INPUT_COUNT] = {&mRho, &mLength, &mBreadth, &mDraught, &mCoeffBlock, &mSubWaterVolume, &mGravityCenter};

};


#endif
