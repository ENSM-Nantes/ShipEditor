#ifndef RADAR_SCREEN_FRAME_H
#define RADAR_SCREEN_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define RADAR_SCREEN_INPUT_COUNT 5

using namespace Gtk;

class RadarScreenSection: public SectionSuperClass {
public:
	RadarScreenSection();
	~RadarScreenSection() {}

protected:
	Box m_box;

	InputArea m_size, m_tilt, m_vector, m_port_throttle, m_stbd_throttle;
	InputArea *input_list_local[RADAR_SCREEN_INPUT_COUNT] = {
		&m_size, &m_tilt, &m_vector, &m_port_throttle, &m_stbd_throttle
	};
};


#endif