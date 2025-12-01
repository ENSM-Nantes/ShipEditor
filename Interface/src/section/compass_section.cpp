#include "compass_section.h"

CompassSection::CompassSection():
SectionSuperClass("Compass"),
m_box(Orientation::HORIZONTAL),
m_max_deviation("Maximum deviation", &(boat_ref->deviationMaximum)),
m_heading_max("Heading maximum", &(boat_ref->deviationMaximumHeading))
{
	// Show every field
	m_max_deviation.show();
	m_heading_max.show();

	// Fill the box
	m_box.append(m_max_deviation);
	m_box.append(m_heading_max);

	// Show and set the grid as the child
	m_box.show();
	this->set_child(m_box);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = COMPASS_INPUT_COUNT;
}