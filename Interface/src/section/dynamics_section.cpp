#include "dynamics_section.h"

DynamicsSection::DynamicsSection():
SectionSuperClass("Dynamics"),
m_grid(),
m_speed("Speed", &(boat_local.dynamics.speed[1])),
m_speed_sq("Speed (squared)", &(boat_local.dynamics.speed[0])),
m_turndrag("Turn drag", &(boat_local.dynamics.turnDrag[1])),
m_turndrag_sq("Turn drag (squared)", &(boat_local.dynamics.turnDrag[0])),
m_lateraldrag("Lateral drag", &(boat_local.dynamics.lateralDrag[1])),
m_lateraldrag_sq("Lateral drag (squared)", &(boat_local.dynamics.lateralDrag[0]))
{
	// Show every field
	m_speed.show();
	m_speed_sq.show();
	m_turndrag.show();
	m_turndrag_sq.show();
	m_lateraldrag.show();
	m_lateraldrag_sq.show();

	// Fill the box
	m_grid.attach(m_speed, 0, 0);
	m_grid.attach(m_speed_sq, 1, 0);
	m_grid.attach(m_turndrag, 0, 1);
	m_grid.attach(m_turndrag_sq, 1, 1);
	m_grid.attach(m_lateraldrag, 0, 2);
	m_grid.attach(m_lateraldrag_sq, 1, 2);

	// Show and set the grid as the child
	m_grid.show();
	this->set_child(m_grid);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = DYNAMICS_INPUT_COUNT;
}