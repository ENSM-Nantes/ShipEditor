#ifndef COMPASS_FRAME_H
#define COMPASS_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define COMPASS_INPUT_COUNT 2

using namespace Gtk;

class CompassSection: public SectionSuperClass {
public:
	CompassSection();
	~CompassSection() {}

protected:
	Box m_box;

	InputArea m_max_deviation, m_heading_max;
	InputArea *input_list_local[COMPASS_INPUT_COUNT] = {
		&m_max_deviation, &m_heading_max
	};
};


#endif