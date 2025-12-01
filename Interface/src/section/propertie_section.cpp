#include "propertie_section.h"

PropertieSection::PropertieSection():
SectionSuperClass("Properties"),
m_grid(),
m_mass("Mass", &(boat_local.mass)),
m_inertia("Inertia", &(boat_local.inertia)),
m_space("Space", &(boat_local.prop.space)),
m_walk_ahead("Walk ahead", &(boat_local.prop.walkAhead)),
m_walk_astern("Walk Astern", &(boat_local.prop.walkAstern)),
m_walk_drift_effect("Walk drift effect", &(boat_local.prop.walkDriftEffect)),
m_roll_period("Roll period", &(boat_local.rollPeriod)),
m_pitch_period("Pitch period", &(boat_local.pitchPeriod)),
m_centrifugal_drift_effect("Centrifugal drift effect", &(boat_local.centrifugalDriftEffect)),
m_turn_indicator_rate("Rate of turn indicator", &(boat_local.hasRateOfTurnIndicator))
{
	// Show every field
	m_mass.show();
	m_inertia.show();
	m_space.show();
	m_walk_ahead.show();
	m_walk_astern.show();
	m_walk_drift_effect.show();
	m_roll_period.show();
	m_pitch_period.show();
	m_centrifugal_drift_effect.show();
	m_turn_indicator_rate.show();

	// Fill the grid
	m_grid.attach(m_mass, 0, 0);
	m_grid.attach(m_inertia, 0, 1);
	m_grid.attach(m_space, 0, 2);
	m_grid.attach(m_walk_ahead, 1, 0);
	m_grid.attach(m_walk_astern, 1, 1);
	m_grid.attach(m_walk_drift_effect, 1, 2);
	m_grid.attach(m_roll_period, 2, 0);
	m_grid.attach(m_pitch_period, 2, 1);
	m_grid.attach(m_centrifugal_drift_effect, 2, 2);
	m_grid.attach(m_turn_indicator_rate, 3, 0);
	
	// Show and set the grid as the child
	m_grid.show();
	this->set_child(m_grid);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = PROPERTIE_INPUT_COUNT;
}