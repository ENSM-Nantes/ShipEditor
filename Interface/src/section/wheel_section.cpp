#include "wheel_section.h"

WheelSection::WheelSection():
SectionSuperClass("Wheel"),
m_box(Orientation::VERTICAL),
m_vector("Vector", (float*)&(boat_ref->wheel.vector), true),
m_scale("Scale", &(boat_ref->wheel.scale))
{
	// Show every field
	m_vector.show();
	m_scale.show();

	// Fill the box
	m_box.append(m_vector);
	m_box.append(m_scale);

	// Show and set the grid as the child
	m_box.show();
	this->set_child(m_box);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = WHEEL_INPUT_COUNT;
}