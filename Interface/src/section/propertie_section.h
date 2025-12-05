#ifndef PROPERTIE_FRAME_H
#define PROPERTIE_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define PROPERTIE_INPUT_COUNT 10

using namespace Gtk;

class PropertieSection: public Section {
public:
  PropertieSection();
  ~PropertieSection() {}

  virtual void update(void);
  virtual void reset(void);
  
protected:
  Grid m_grid;

  InputArea m_mass, m_inertia, m_space, m_walk_ahead, m_walk_astern, m_walk_drift_effect, m_roll_period, m_pitch_period, m_centrifugal_drift_effect, m_turn_indicator_rate;

  InputArea *mInputList[PROPERTIE_INPUT_COUNT] = {
    &m_mass, &m_inertia, &m_space, &m_walk_ahead, &m_walk_astern,
    &m_walk_drift_effect, &m_roll_period, &m_pitch_period,
    &m_centrifugal_drift_effect, &m_turn_indicator_rate
  };

};


#endif
