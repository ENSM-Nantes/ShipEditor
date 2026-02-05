#ifndef DEPTH_SECTION_H
#define DEPTH_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define DEPTH_INPUT_COUNT 2

using namespace Gtk;

class DepthSection: public Section {
public:
  DepthSection();
  ~DepthSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;

  InputArea mDepthSounder, mMaxDepth;

  InputArea *mInputList[DEPTH_INPUT_COUNT] = {&mDepthSounder, &mMaxDepth};

};


#endif
