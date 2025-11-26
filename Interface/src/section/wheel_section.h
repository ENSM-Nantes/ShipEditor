#ifndef WHEEL_FRAME_H
#define WHEEL_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define WHEEL_INPUT_COUNT 2

using namespace Gtk;

class WheelSection: public SectionSuperClass {
public:
	WheelSection();
	~WheelSection() {}

protected:
	Box m_box;

	InputArea m_vector, m_scale;
	InputArea *input_list_local[WHEEL_INPUT_COUNT] = {
		&m_vector, &m_scale
	};
};


#endif