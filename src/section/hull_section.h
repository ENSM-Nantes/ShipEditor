#ifndef HULL_SECTION_H
#define HULL_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define HULL_INPUT_COUNT 28

using namespace Gtk;

class HullSection: public Section {
public:
  HullSection();
  ~HullSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;

  InputArea mXp0, mXpVV, mXpVR, mXpRR, mXpVVVV, mYpV, mYpR, mYpVVV, mYpVVR, mYpVRR, mYpRRR, mNpV, mNpR, mNpVVV, mNpVVR, mNpVRR, mNpRRR, mKpG, mKpB, mKpR, mKpBBG, mKpBRG, mKpRRG, mKpBBB, mKpBBR, mKpBRR, mKpRRR, mInvertRoll;
;
  InputArea *mInputList[HULL_INPUT_COUNT] = {&mXp0, &mXpVV, &mXpVR, &mXpRR, &mXpVVVV, &mYpV, &mYpR, &mYpVVV, &mYpVVR, &mYpVRR, &mYpRRR, &mNpV, &mNpR, &mNpVVV, &mNpVVR, &mNpVRR, &mNpRRR, &mKpG, &mKpB, &mKpR, &mKpBBG, &mKpBRG, &mKpRRG, &mKpBBB, &mKpBBR, &mKpBRR, &mKpRRR, &mInvertRoll};

};


#endif
