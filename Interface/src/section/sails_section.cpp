#include "sails_section.h"
#include <string>
#include <sstream>

#include <iostream>

SailsSection::SailsSection() :
SectionSuperClass("Sails"),
m_grid(),
m_box(Orientation::VERTICAL),
m_add_sail_button("+ Add Sail"),
m_size("Size", &(boat_local.sails.size)),
m_type("Type", &(boat_local.sails.type))
{
	// Orientation verticale via Grid
	m_grid.set_row_spacing(5);
	m_grid.set_column_spacing(5);

	m_add_sail_button.show();
	m_size.show();
	m_type.show();
	m_grid.show();

	// Connect the "Add Sail" button signal only once, in constructor
	m_add_sail_button.signal_clicked().connect(sigc::mem_fun(*this, &SailsSection::on_add_sail));


	// Ajout des composants dans la box
	m_box.append(m_size);
	m_box.append(m_type);
	m_box.append(m_grid);

	m_box.show();

	// Ajouter la grille au Frame (GTK4)
	set_child(m_box);
}

void SailsSection::rebuild_ui() {
	// Clear the grid and delete old widgets
	for (auto& child : m_grid.get_children()) {
		child->unparent();
	}
	for (auto p : m_inputs) {
		if (p) delete p;
	}
	for (auto p : m_delete_buttons) {
		if (p) delete p;
	}
	m_inputs.clear();
	m_delete_buttons.clear();

	// Pour chaque voile du bateau
	int row = 0;
	for (size_t i = 0; i < boat_local.sails.sails.size(); ++i) {
		Sail& sail = boat_local.sails.sails[i];

		std::ostringstream label;
		label << "Sail " << i;

		// Create InputArea for this sail (vector mode)
		InputArea* in = new InputArea(label.str(), &sail.vector[0], true);
		in->show();
		m_grid.attach(*in, 0, row, 3, 1);
		m_inputs.push_back(in);

		// Create delete button for this sail
		Gtk::Button* delete_btn = new Gtk::Button("X");
		delete_btn->show();
		delete_btn->signal_clicked().connect([this, i]() { on_delete_sail(i); });
		m_grid.attach(*delete_btn, 3, row, 1, 1);
		m_delete_buttons.push_back(delete_btn);

		++row;
	}

	// Add "Add Sail" button at the bottom
	m_add_sail_button.show();
	// Note: we only connect once in constructor; rebuild_ui() will reattach without reconnecting
	m_grid.attach(m_add_sail_button, 0, (int)boat_local.sails.sails.size(), 4, 1);

	// Update the input list for the base class
	input_count = (int)m_inputs.size();
	input_list = m_inputs.data();

	// Populate UI from Boat values
	for (auto& input : m_inputs) {
		input->reset();
	}
	
}

void SailsSection::on_add_sail() {
	// Load the last version before changing it
	boat_local = *boat_ref;

	// Add a new sail with default vector (0, 0, 0)
	Sail new_sail;
	new_sail.vector[0] = 0.0f;
	new_sail.vector[1] = 0.0f;
	new_sail.vector[2] = 0.0f;
	boat_local.sails.sails.push_back(new_sail);
	rebuild_ui();

	// Update the pointer
	*boat_ref = boat_local;
}

void SailsSection::on_delete_sail(size_t sail_index) {
	// Load the last version before changing it
	boat_local = *boat_ref;

	if (sail_index >= boat_local.sails.sails.size()) return;
	boat_local.sails.sails.erase(boat_local.sails.sails.begin() + (int)sail_index);
	rebuild_ui();

	// Update the pointer
	*boat_ref = boat_local;
}

void SailsSection::reset() {
	boat_local = *boat_ref;
	m_size.reset();
	m_type.reset();
	rebuild_ui();
}

void SailsSection::update() {
	// Load the last version before changing it
	boat_local = *boat_ref;

	// Update the list
	for (auto& input : m_inputs) {
		if (input) input->update();
	}

	// Update the static fields
	m_size.update();
	m_type.update();

	// Update the pointer
	*boat_ref = boat_local;
}

bool SailsSection::hasFormatError() {
	bool flag = false;
	for (auto& input : m_inputs) {
		if (input->hasFormatError()) {
			flag = true;
			break;
		}
	}
	if (m_size.hasFormatError()) flag = true;
	if (m_type.hasFormatError()) flag = true;

	return flag;
}

bool SailsSection::hasChanged() {
	bool flag = false;
	for (auto& input : m_inputs) {
		if (input->hasChanged()) {
			flag = true;
			break;
		}
	}
	if (m_size.hasChanged()) flag = true;
	if (m_type.hasChanged()) flag = true;

	return flag;
}