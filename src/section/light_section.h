#ifndef LIGHT_SECTION_H
#define LIGHT_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define LIGHT_INPUT_COUNT 1
#define MAX_LIGHT 5

using namespace Gtk;

class LightSection: public Section {
public:
  LightSection();
  ~LightSection();

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;
  InputArea mNumber;
  std::vector<InputArea*> mLight;
  InputArea *mInputList[LIGHT_INPUT_COUNT] = {&mNumber};

};


#endif
