#include "propulsion_section.h"

PropulsionSection::PropulsionSection():
SectionSuperClass("Propulsion"),
m_box(Orientation::VERTICAL),
m_box_first_line(Orientation::HORIZONTAL),
m_box_second_line(Orientation::HORIZONTAL),
m_box_frame(Orientation::HORIZONTAL),
m_box_bow(Orientation::VERTICAL),
m_box_stern(Orientation::VERTICAL),
m_frame_bow_thruster("Bow"),
m_frame_stern_thruster("Stern"),
m_max_propulsion_force("Max propulsion force", &(boat_local.maxPropulsionForce)),
m_max_rpm("Max RPM", &(boat_local.maxRevs)),
m_max_speed("Max speed", &(boat_local.maxSpeedAhead)),
m_astern_efficiency("Astern efficiency", &(boat_local.asternEfficiency)),
m_block_coeff("Block coefficient", &(boat_local.blockCoefficient)),
m_bow_force("Force", &(boat_local.bowThruster.Force)),
m_bow_distance("Distance", &(boat_local.bowThruster.Distance)),
m_stern_force("Force", &(boat_local.sternThruster.Force)),
m_stern_distance("Distance", &(boat_local.sternThruster.Distance))
{
	// Show every field
	m_max_propulsion_force.show();
	m_max_rpm.show();
	m_max_speed.show();
	m_astern_efficiency.show();
	m_block_coeff.show();
	m_bow_force.show();
	m_bow_distance.show();
	m_stern_force.show();
	m_stern_distance.show();

	
	// Fill the two line
	m_box_first_line.append(m_max_propulsion_force);
	m_box_first_line.append(m_max_speed);
	m_box_first_line.append(m_max_rpm);

	m_box_second_line.append(m_astern_efficiency);
	m_box_second_line.append(m_block_coeff);

	// Fill the sub-sections
	m_box_bow.append(m_bow_force);
	m_box_bow.append(m_bow_distance);
	m_box_stern.append(m_stern_force);
	m_box_stern.append(m_stern_distance);

	m_frame_bow_thruster.set_child(m_box_bow);
	m_frame_stern_thruster.set_child(m_box_stern);
	m_frame_bow_thruster.show();
	m_frame_stern_thruster.show();

	m_box_frame.append(m_frame_bow_thruster);
	m_box_frame.append(m_frame_stern_thruster);

	// Fill the main box
	m_box_first_line.show();
	m_box_second_line.show();
	m_box_frame.show();
	m_box_bow.show();
	m_box_stern.show();


	// Show and set the main box as the child
	m_box.append(m_box_first_line);
	m_box.append(m_box_second_line);
	m_box.append(m_box_frame);	
	m_box.show();
	this->set_child(m_box);


	// Layout
	m_frame_bow_thruster.set_margin_top(5);
	m_frame_bow_thruster.set_margin_bottom(5);
	m_frame_bow_thruster.set_margin_start(10);
	m_frame_bow_thruster.set_margin_end(10);
	m_frame_stern_thruster.set_margin_top(5);
	m_frame_stern_thruster.set_margin_bottom(5);
	m_frame_stern_thruster.set_margin_start(10);
	m_frame_stern_thruster.set_margin_end(10);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = PROPULSION_INPUT_COUNT;
}