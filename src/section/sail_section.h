#ifndef SAIL_SECTION_H
#define SAIL_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define SAIL_INPUT_COUNT 3
#define MAX_SAILS 4

using namespace Gtk;

class SailSection: public Section {
public:
  SailSection();
  ~SailSection();

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;
  InputArea mNumber, mType, mSize;
  std::vector<InputArea*> mPos;
  InputArea *mInputList[SAIL_INPUT_COUNT] = {&mNumber, &mType, &mSize};

};


#endif
