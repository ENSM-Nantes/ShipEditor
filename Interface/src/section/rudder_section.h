#ifndef RUDDER_FRAME_H
#define RUDDER_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define RUDDER_INPUT_COUNT 3

using namespace Gtk;

class RudderSection: public Section {
public:
  RudderSection();
  ~RudderSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Box m_box;

  InputArea m_a, m_b, m_bastern;

  InputArea *mInputList[RUDDER_INPUT_COUNT] = {
    &m_a, &m_b, &m_bastern
  };

};


#endif
