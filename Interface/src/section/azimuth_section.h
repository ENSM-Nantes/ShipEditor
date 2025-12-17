#ifndef AZIMUTH_FRAME_H
#define AZIMUTH_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define AZIMUTH_INPUT_COUNT 10

using namespace Gtk;

class AzimuthSection: public SectionSuperClass {
public:
	AzimuthSection();
	~AzimuthSection() {}

protected:
	Grid m_grid;

	InputArea m_azimuth, m_astern, m_azimuth_lenth2ratio, m_engine_idle, m_max_deg_sec, m_clutch_engaged, m_clutch_disengage, m_thrust_lever, m_same_dir, m_engine_max_change;
	InputArea *input_list_local[AZIMUTH_INPUT_COUNT] = {
		&m_azimuth, &m_astern, &m_azimuth_lenth2ratio, &m_engine_idle,
		&m_max_deg_sec, &m_clutch_engaged, &m_clutch_disengage,
		&m_thrust_lever, &m_same_dir, &m_engine_max_change
	};
};


#endif