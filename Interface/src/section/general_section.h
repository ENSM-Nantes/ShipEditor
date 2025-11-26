#ifndef GENERAL_FRAME_H
#define GENERAL_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define GENERAL_INPUT_COUNT 8

using namespace Gtk;

class GeneralSection: public SectionSuperClass {
public:
	GeneralSection();
	~GeneralSection() {}

protected:
	Boat *boat_ref;

	Grid m_grid;

	InputArea m_filename, m_ycorrection, m_gps, m_scale_factor, m_depth, m_depth_sounder, m_max_depth, m_make_transparent;
	InputArea *input_list_local[GENERAL_INPUT_COUNT] = {
		&m_filename, &m_ycorrection, &m_gps, &m_scale_factor,
		&m_depth, &m_depth_sounder, &m_max_depth,
		&m_make_transparent
	};
};


#endif