#ifndef THRUSTER_SECTION_H
#define THRUSTER_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define THRUSTER_INPUT_COUNT 12

using namespace Gtk;

class ThrusterSection: public Section {
public:
  ThrusterSection();
  ~ThrusterSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;

  InputArea mBow, mStern, mBrand, mType, mPower, mRpmMax, mFuelCons, mPropellerDiameter, mForwardRotDir, mBackwardEff, mXBow, mXStern;
  InputArea *mInputList[THRUSTER_INPUT_COUNT] = {&mBow, &mStern, &mBrand, &mType, &mPower, &mRpmMax, &mFuelCons, &mPropellerDiameter, &mForwardRotDir, &mBackwardEff, &mXBow, &mXStern};

};


#endif
