#include "rudder_section.h"

RudderSection::RudderSection():
SectionSuperClass("Rudder"),
m_box(Orientation::VERTICAL),
m_a("A", &(boat_local.rudder.A)),
m_b("B", &(boat_local.rudder.B)),
m_bastern("BAstern", &(boat_local.rudder.BAstern))
{
	// Show every field
	m_a.show();
	m_b.show();
	m_bastern.show();

	// Fill the grid
	m_box.append(m_a);
	m_box.append(m_b);
	m_box.append(m_bastern);

	// Show and set the grid as the child
	m_box.show();
	this->set_child(m_box);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = RUDDER_INPUT_COUNT;
}