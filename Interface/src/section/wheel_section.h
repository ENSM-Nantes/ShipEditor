#ifndef WHEEL_FRAME_H
#define WHEEL_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define WHEEL_INPUT_COUNT 2

using namespace Gtk;

class WheelSection: public Section {
public:
  WheelSection();
  ~WheelSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Box m_box;

  InputArea m_vector, m_scale;

  InputArea *mInputList[WHEEL_INPUT_COUNT] = {
    &m_vector, &m_scale
  };

};


#endif
