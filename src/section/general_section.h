#ifndef GENERAL_SECTION_H
#define GENERAL_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define GENERAL_INPUT_COUNT 2

using namespace Gtk;

class GeneralSection: public Section {
public:
  GeneralSection();
  ~GeneralSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;

  InputArea mBoatName, mImgName;
  InputArea *mInputList[GENERAL_INPUT_COUNT] = {&mBoatName, &mImgName};

};


#endif
