#include "general_section.h"

GeneralSection::GeneralSection():
SectionSuperClass("General"),
m_grid(),
m_ycorrection("Y correction", &(boat_local.yCorrection)),
m_gps("GPS", &(boat_local.hasGPS)),
m_scale_factor("Scale factor", &(boat_local.scaleFactor)),
m_depth("Depth", &(boat_local.depth)),
m_depth_sounder("Depth sounder", &(boat_local.hasDepthSounder)),
m_max_depth("Max depth", &(boat_local.maxDepth)),
m_make_transparent("Make transparent", &(boat_local.makeTransparent))
{
	// Show every field
	m_ycorrection.show();
	m_gps.show();
	m_scale_factor.show();
	m_depth.show();
	m_depth_sounder.show();
	m_max_depth.show();
	m_make_transparent.show();

	// Fill the grid
	m_grid.attach(m_ycorrection, 0, 0);
	m_grid.attach(m_gps, 1, 0);
	m_grid.attach(m_scale_factor, 2, 0);
	m_grid.attach(m_depth, 0, 1);
	m_grid.attach(m_depth_sounder, 1, 1);
	m_grid.attach(m_max_depth, 2, 1);
	m_grid.attach(m_make_transparent, 0, 2);

	// Show and set the grid as the child
	m_grid.show();
	this->set_child(m_grid);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = GENERAL_INPUT_COUNT;
}