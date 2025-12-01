#ifndef DYNAMICS_SECTION_H
#define DYNAMICS_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define DYNAMICS_INPUT_COUNT 6

using namespace Gtk;

class DynamicsSection: public SectionSuperClass {
public:
	DynamicsSection();
	~DynamicsSection() {}

protected:
	Grid m_grid;

	InputArea m_speed, m_speed_sq, m_turndrag, m_turndrag_sq, m_lateraldrag, m_lateraldrag_sq;
	InputArea *input_list_local[DYNAMICS_INPUT_COUNT] = {
		&m_speed, &m_speed_sq,
		&m_turndrag, &m_turndrag_sq,
		&m_lateraldrag, &m_lateraldrag_sq
	};
};

#endif