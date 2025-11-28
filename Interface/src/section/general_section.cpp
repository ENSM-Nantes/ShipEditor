#include "general_section.h"

GeneralSection::GeneralSection(): SectionSuperClass("General"), m_grid() {
	// Prepare the grid; InputArea widgets will be created when a Boat is loaded
	m_grid.show();
	this->set_child(m_grid);

	// Initialize the section input list pointer to our local array (currently nulls)
	this->input_list = input_list_local;
	this->input_count = 0;
}

GeneralSection::~GeneralSection() {
	// delete allocated InputArea widgets if any
	InputArea* arr[] = { m_filename, m_ycorrection, m_gps, m_scale_factor,
		m_depth, m_depth_sounder, m_max_depth, m_make_transparent };
	for (auto p : arr) {
		if (p) delete p;
	}
}

void GeneralSection::loadBoat(Boat *b) {
	if (!b) return;

	// Remove previous widgets from grid
	for (auto &child : m_grid.get_children()) {
		child->unparent();
	}

	// Delete previous InputArea objects if they exist
	InputArea* arr_old[] = { m_filename, m_ycorrection, m_gps, m_scale_factor,
		m_depth, m_depth_sounder, m_max_depth, m_make_transparent };
	for (auto &p : arr_old) {
		if (p) { delete p; p = nullptr; }
	}

	// Create new InputAreas bound to the Boat
	m_filename = new InputArea("File name", &(b->fileName));
	m_ycorrection = new InputArea("Y correction", &(b->yCorrection));
	m_gps = new InputArea("GPS", &(b->hasGPS));
	m_scale_factor = new InputArea("Scale factor", &(b->scaleFactor));
	m_depth = new InputArea("Depth", &(b->depth));
	m_depth_sounder = new InputArea("Depth sounder", &(b->hasDepthSounder));
	m_max_depth = new InputArea("Max depth", &(b->maxDepth));
	m_make_transparent = new InputArea("Make transparent", &(b->makeTransparent));

	// show widgets
	m_filename->show();
	m_ycorrection->show();
	m_gps->show();
	m_scale_factor->show();
	m_depth->show();
	m_depth_sounder->show();
	m_max_depth->show();
	m_make_transparent->show();

	// attach to grid
	m_grid.attach(*m_filename, 0, 0);
	m_grid.attach(*m_ycorrection, 0, 1);
	m_grid.attach(*m_gps, 0, 2);
	m_grid.attach(*m_scale_factor, 1, 0);
	m_grid.attach(*m_depth, 1, 1);
	m_grid.attach(*m_depth_sounder, 1, 2);
	m_grid.attach(*m_max_depth, 2, 0);
	m_grid.attach(*m_make_transparent, 2, 1);

	// Fill local input list and inform base class
	input_list_local[0] = m_filename;
	input_list_local[1] = m_ycorrection;
	input_list_local[2] = m_gps;
	input_list_local[3] = m_scale_factor;
	input_list_local[4] = m_depth;
	input_list_local[5] = m_depth_sounder;
	input_list_local[6] = m_max_depth;
	input_list_local[7] = m_make_transparent;

	this->input_count = GENERAL_INPUT_COUNT;
	this->input_list = input_list_local;

	// Call base reset to populate UI from Boat
	reset();
}
