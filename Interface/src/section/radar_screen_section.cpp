#include "radar_screen_section.h"

RadarScreenSection::RadarScreenSection():
SectionSuperClass("Radar Screen"),
m_box(Orientation::VERTICAL),
m_size("Size", &(boat_local.radarScreen.size)),
m_tilt("Tilt", &(boat_local.radarScreen.tilt)),
m_vector("Vector", (float*)&(boat_local.radarScreen.vector), true),
m_port_throttle("Port throttle", (float*)&(boat_local.portThrottle), true),
m_stbd_throttle("Stbd throttle", (float*)&(boat_local.stbdThrottle), true)
{
	// Show every field
	m_size.show();
	m_tilt.show();
	m_vector.show();
	m_port_throttle.show();
	m_stbd_throttle.show();

	// Fill the box
	m_box.append(m_size);
	m_box.append(m_tilt);
	m_box.append(m_vector);
	m_box.append(m_port_throttle);
	m_box.append(m_stbd_throttle);
	

	// Show and set the box as the child
	m_box.show();
	this->set_child(m_box);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = RADAR_SCREEN_INPUT_COUNT;
}