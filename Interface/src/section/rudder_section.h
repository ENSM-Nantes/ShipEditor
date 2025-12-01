#ifndef RUDDER_FRAME_H
#define RUDDER_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define RUDDER_INPUT_COUNT 3

using namespace Gtk;

class RudderSection: public SectionSuperClass {
public:
	RudderSection();
	~RudderSection() {}

protected:
	Box m_box;

	InputArea m_a, m_b, m_bastern;
	InputArea *input_list_local[RUDDER_INPUT_COUNT] = {
		&m_a, &m_b, &m_bastern
	};
};


#endif