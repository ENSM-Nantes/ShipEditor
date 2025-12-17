#ifndef PROPULSION_FRAME_H
#define PROPULSION_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define PROPULSION_INPUT_COUNT 9

using namespace Gtk;

class PropulsionSection: public SectionSuperClass {
public:
	PropulsionSection();
	~PropulsionSection() {}

protected:
	Box m_box, m_box_first_line, m_box_second_line, m_box_frame, m_box_bow, m_box_stern;
	Frame m_frame_bow_thruster, m_frame_stern_thruster;

	InputArea m_max_propulsion_force, m_max_rpm, m_max_speed, m_astern_efficiency, m_block_coeff, m_bow_force, m_bow_distance, m_stern_force, m_stern_distance;
	InputArea *input_list_local[PROPULSION_INPUT_COUNT] = {
		&m_max_propulsion_force, &m_max_rpm, &m_max_speed, &m_astern_efficiency,
		&m_block_coeff, &m_bow_force, &m_bow_distance, &m_stern_force,
		&m_stern_distance
	};
};


#endif