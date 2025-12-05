#ifndef COMPASS_FRAME_H
#define COMPASS_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define COMPASS_INPUT_COUNT 2

using namespace Gtk;

class CompassSection: public Section {
public:
  CompassSection();
  ~CompassSection() {}

  virtual void update(void);
  virtual void reset(void);
  
protected:

  Box m_box;

  InputArea m_max_deviation, m_heading_max;

  InputArea *mInputList[COMPASS_INPUT_COUNT] = {
    &m_max_deviation, &m_heading_max
  };

  
};


#endif
