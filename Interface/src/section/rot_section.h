#ifndef ROT_SECTION_H
#define ROT_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define ROT_INPUT_COUNT 1

using namespace Gtk;

class RotSection: public Section {
public:
  RotSection();
  ~RotSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;
  InputArea mRot;
  InputArea *mInputList[ROT_INPUT_COUNT] = {&mRot};

};


#endif
