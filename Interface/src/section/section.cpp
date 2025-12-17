#include "section.h"


/**
 * Constructor of a section
 * @param the name of the section
 */
SectionSuperClass::SectionSuperClass(const Glib::ustring &label): Frame(label) {
	// Nothing to do
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
	for (int i = 0; i < input_count; i++) {
		input_list[i]->update();
	}
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