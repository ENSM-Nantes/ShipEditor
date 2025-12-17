#include "section.h"


/**
 * Constructor of a section
 * @param the name of the section
 */
SectionSuperClass::SectionSuperClass(const Glib::ustring &label): Frame(label) {
	this->set_margin_top(5);
	this->set_margin_bottom(5);
	this->set_margin_start(10);
	this->set_margin_end(10);
}

/**
 * Constructor of a section
 * @param the name of the section
 */
SectionSuperClass::SectionSuperClass(): SectionSuperClass("") {
	// Nothing to do
}

/**
 * Load a boat to edit its properties
 * @param b The reference of a boat
 */
void SectionSuperClass::loadBoat(Boat *b) {
	if (b == nullptr) return;
	boat_ref = b;
	// Refresh the interface
	reset();
}
 
/**
 * Update all the field (see InputArea::update())
 */
void SectionSuperClass::update() {
	// Load the last version of the boat
	boat_local = *boat_ref;
	for (int i = 0; i < input_count; i++) {
		input_list[i]->update();
	}
	// Save the modifications
	*boat_ref = boat_local;
}

/**
 * Reset all the field (see InputArea::reset())
 */
void SectionSuperClass::reset() {
	boat_local = *boat_ref;
	for (int i = 0; i < input_count; i++) {
		input_list[i]->reset();
	}
}

/**
 * Retreive error from all the field (see InputArea::hasFormatError())
 */
bool SectionSuperClass::hasFormatError() {
	bool flag = false;
	for (int i = 0; i < input_count; i++) {
		if (input_list[i]->hasFormatError()) {
			flag = true;
			break;
		}
	}
	return flag;
}

/**
 * Retreive a change from all the field (see InputArea::hasChanged())
 */
bool SectionSuperClass::hasChanged() {
	bool flag = false;
	for (int i = 0; i < input_count; i++) {
		if (input_list[i]->hasChanged()) {
			flag = true;
			break;
		}
	}
	return flag;
}