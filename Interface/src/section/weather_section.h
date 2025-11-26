#ifndef WEATHER_FRAME_H
#define WEATHER_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define WEATHER_INPUT_COUNT 4

using namespace Gtk;

class WeatherSection: public SectionSuperClass {
public:
	WeatherSection();
	~WeatherSection() {}

protected:
	Grid m_grid;

	InputArea m_buffet, m_swell, m_windage, m_windage_turn_effect;
	InputArea *input_list_local[WEATHER_INPUT_COUNT] = {
		&m_buffet, &m_swell, &m_windage, &m_windage_turn_effect
	};
};


#endif