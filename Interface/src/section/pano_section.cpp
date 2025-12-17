#include "pano_section.h"
#include <sstream>
#include <iostream>

PanoSection::PanoSection() :
SectionSuperClass("Pano"),
m_grid(),
m_add_pano_button("+ Add Pano")
{
	m_grid.set_row_spacing(5);
	m_grid.set_column_spacing(5);

	// connect add button once
	m_add_pano_button.signal_clicked().connect(sigc::mem_fun(*this, &PanoSection::on_add_pano));

	set_child(m_grid);
}

PanoSection::~PanoSection() {
	// cleanup
	for (auto &r : m_rows) {
		if (r.file) delete r.file;
		if (r.yaw) delete r.yaw;
		if (r.pitch) delete r.pitch;
		if (r.roll) delete r.roll;
		if (r.del_btn) delete r.del_btn;
	}
}

void PanoSection::reset() {
	boat_local = *boat_ref;
	rebuild_ui();
}

void PanoSection::rebuild_ui() {
	// std::cout << "PanoSection::rebuild_ui called; boat=" << (void*)m_boat;
	// if (m_boat) std::cout << " pano_count=" << m_boat->pano.file.size();
	// std::cout << std::endl;
	// clear grid children
	for (auto &child : m_grid.get_children()) child->unparent();

	// delete previous widgets
	for (auto &r : m_rows) {
		if (r.file) delete r.file;
		if (r.yaw) delete r.yaw;
		if (r.pitch) delete r.pitch;
		if (r.roll) delete r.roll;
		if (r.del_btn) delete r.del_btn;
	}
	m_rows.clear();

	// build rows
	int row = 0;
	for (size_t i = 0; i < boat_local.pano.file.size(); ++i) {
		Row r{};
		// file (string)
		r.file = new InputArea("File", &(boat_local.pano.file[i]));
		r.file->show();
		m_grid.attach(*r.file, 0, row, 1, 1);

		// yaw
		r.yaw = new InputArea("Yaw", &(boat_local.pano.yaw[i]));
		r.yaw->show();
		m_grid.attach(*r.yaw, 1, row, 1, 1);

		// pitch
		r.pitch = new InputArea("Pitch", &(boat_local.pano.pitch[i]));
		r.pitch->show();
		m_grid.attach(*r.pitch, 2, row, 1, 1);

		// roll
		r.roll = new InputArea("Roll", &(boat_local.pano.roll[i]));
		r.roll->show();
		m_grid.attach(*r.roll, 3, row, 1, 1);

		// delete button
		r.del_btn = new Gtk::Button("X");
		r.del_btn->show();
		// capture index by value
		r.del_btn->signal_clicked().connect([this, i]() { on_delete_pano(i); });
		m_grid.attach(*r.del_btn, 4, row, 1, 1);

		m_rows.push_back(r);
		++row;
	}

	// add button at bottom spanning 5 columns
	m_add_pano_button.show();
	m_grid.attach(m_add_pano_button, 0, row, 5, 1);

	// fill input list for base class
	// gather all InputArea pointers in order
	std::vector<InputArea*> all;
	for (auto &r : m_rows) {
		all.push_back(r.file);
		all.push_back(r.yaw);
		all.push_back(r.pitch);
		all.push_back(r.roll);
	}
	// copy to internal storage: we will use a vector and set input_list to its data
	// but SectionSuperClass expects InputArea**; we can keep them in a temporary vector memberless
	// easiest: set input_count and input_list to point to first element of a static vector is unsafe.
	// Instead, build a dynamic array here and keep it until next rebuild; simple approach: reuse m_rows to iterate in reset/update.
	// We'll not rely on base class input_list; override update/reset by using m_rows directly.

	// populate UI from boat values
	for (auto &r : m_rows) {
		r.file->reset();
		r.yaw->reset();
		r.pitch->reset();
		r.roll->reset();
	}
}

void PanoSection::on_add_pano() {
	// Load the last version before changing it
	boat_local = *boat_ref;

	// Add default pano entry
	boat_local.pano.file.push_back(std::string(""));
	boat_local.pano.yaw.push_back(0.0f);
	boat_local.pano.pitch.push_back(0.0f);
	boat_local.pano.roll.push_back(0.0f);
	rebuild_ui();

	// Update the pointer
	*boat_ref = boat_local;
}

void PanoSection::on_delete_pano(size_t index) {
	// Load the last version before changing it
	boat_local = *boat_ref;

	if (index >= boat_local.pano.file.size()) return;
	boat_local.pano.file.erase(boat_local.pano.file.begin() + (int)index);
	boat_local.pano.yaw.erase(boat_local.pano.yaw.begin() + (int)index);
	boat_local.pano.pitch.erase(boat_local.pano.pitch.begin() + (int)index);
	boat_local.pano.roll.erase(boat_local.pano.roll.begin() + (int)index);
	rebuild_ui();

	// Update the pointer
	*boat_ref = boat_local;
}

void PanoSection::update() {
	// Load the last version before changing it
	boat_local = *boat_ref;
	for (auto &r : m_rows) {
		if (r.file) r.file->update();
		if (r.yaw) r.yaw->update();
		if (r.pitch) r.pitch->update();
		if (r.roll) r.roll->update();
	}

	// Update the pointer
	*boat_ref = boat_local;
}

bool PanoSection::hasFormatError() {
	bool flag = false;
	for (auto &r : m_rows) {
		if (r.file->hasFormatError() || r.yaw->hasFormatError() || r.pitch->hasFormatError() || r.roll->hasFormatError()) {
			flag = true;
			break;
		}
	}
	return flag;
}

bool PanoSection::hasChanged() {
	bool flag = false;
	for (auto &r : m_rows) {
		if (r.file->hasChanged() || r.yaw->hasChanged() || r.pitch->hasChanged() || r.roll->hasChanged()) {
			flag = true;
			break;
		}
	}
	return flag;
}