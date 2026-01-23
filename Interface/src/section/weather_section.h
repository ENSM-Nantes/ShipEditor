#ifndef WEATHER_FRAME_H
#define WEATHER_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define WEATHER_INPUT_COUNT 4

using namespace Gtk;

class WeatherSection: public Section {
public:
  WeatherSection();
  ~WeatherSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
    
protected:
  Grid m_grid;

  InputArea m_buffet, m_swell, m_windage, m_windage_turn_effect;

  InputArea *mInputList[WEATHER_INPUT_COUNT] = {
    &m_buffet, &m_swell, &m_windage, &m_windage_turn_effect
  };

};


#endif
