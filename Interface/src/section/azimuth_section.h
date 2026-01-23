#ifndef AZIMUTH_FRAME_H
#define AZIMUTH_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define AZIMUTH_INPUT_COUNT 10

using namespace Gtk;

class AzimuthSection: public Section {
public:

  AzimuthSection();
  ~AzimuthSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
private:
  
  Grid m_grid;
  InputArea m_azimuth, m_astern, m_azimuth_lenth2ratio, m_engine_idle, m_max_deg_sec, m_clutch_engaged, m_clutch_disengage, m_thrust_lever, m_same_dir, m_engine_max_change;

  InputArea *mInputList[AZIMUTH_INPUT_COUNT] = {
    &m_azimuth, &m_astern, &m_azimuth_lenth2ratio, &m_engine_idle,
    &m_max_deg_sec, &m_clutch_engaged, &m_clutch_disengage,
    &m_thrust_lever, &m_same_dir, &m_engine_max_change
  };

};


#endif
