#include "weather_section.h"

WeatherSection::WeatherSection():
SectionSuperClass("Weather Influence"),
m_grid(),
m_buffet("Buffet", &(boat_ref->buffet)),
m_swell("Swell", &(boat_ref->swell)),
m_windage("Windage", &(boat_ref->windage)),
m_windage_turn_effect("Windage turn effect", &(boat_ref->windageTurnEffect))
{
	// Show every field
	m_buffet.show();
	m_swell.show();
	m_windage.show();
	m_windage_turn_effect.show();

	// Fill the box
	m_grid.attach(m_buffet, 0, 0);
	m_grid.attach(m_swell, 0, 1);
	m_grid.attach(m_windage, 1, 0);
	m_grid.attach(m_windage_turn_effect, 1, 1);

	// Show and set the grid as the child
	m_grid.show();
	this->set_child(m_grid);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = WEATHER_INPUT_COUNT;
}