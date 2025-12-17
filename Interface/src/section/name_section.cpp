#include "name_section.h"

NameSection::NameSection():
SectionSuperClass("Information"),
m_box(Orientation::VERTICAL),
m_name("Boat name", &(boat_local.displayName)),
m_3d_file("3D filename", &(boat_local.fileName))
{
	// Show every field
	m_name.show();
	m_3d_file.show();

	// Fill the grid
	m_box.append(m_name);
	m_box.append(m_3d_file);

	// Show and set the grid as the child
	m_box.show();
	this->set_child(m_box);
}

void NameSection::reset() {
	boat_local = *boat_ref;
	m_name.reset();
	m_3d_file.reset();
}

void NameSection::update() {
	// Load the last version before changing it
	boat_local = *boat_ref;

	// Update the path for 3D file
	m_3d_file.update();

	// See if there is any change in the field before changing the path
	if (m_name.hasChanged()) {
		BoatManager manager;

		// Save the name in case it doesn't work
		std::string temp = boat_local.displayName;

		// Update the name in the variable
		m_name.update();

		// Try changing the folder name
		if (!manager.renameBoat(boat_local)) {
			// Reload the old name
			boat_local.displayName = temp;
			m_name.reset();
		}

	}



	// Update the pointer
	*boat_ref = boat_local;
}

bool NameSection::hasFormatError() {
	bool flag = false;
	if (m_name.hasFormatError() || m_3d_file.hasFormatError()) {
		flag = true;
	}
	return flag;
}

bool NameSection::hasChanged() {
	bool flag = false;
	if (m_name.hasChanged() || m_3d_file.hasChanged()) {
		flag = true;
	}
	return flag;
}