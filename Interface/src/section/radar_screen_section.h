#ifndef RADAR_SCREEN_FRAME_H
#define RADAR_SCREEN_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define RADAR_SCREEN_INPUT_COUNT 5

using namespace Gtk;

class RadarScreenSection: public Section {
public:
  RadarScreenSection();
  ~RadarScreenSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Box m_box;

  InputArea m_size, m_tilt, m_vector, m_port_throttle, m_stbd_throttle;

  InputArea *mInputList[RADAR_SCREEN_INPUT_COUNT] = {
    &m_size, &m_tilt, &m_vector, &m_port_throttle, &m_stbd_throttle
  };

};


#endif
