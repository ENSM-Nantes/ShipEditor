#ifndef SECTION_H
#define SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"

/*
	This class gether the common functions for the sections:
		void loadBoat(Boat *b)
		void update()
		void reset()

*/
class SectionSuperClass: public Frame {
public:
	SectionSuperClass();
	SectionSuperClass(const Glib::ustring &label);
	~SectionSuperClass() {}

	// Boat change
	virtual void loadBoat(Boat *b);

	// For the entries
	virtual void update();
	virtual void reset();

protected:
	Boat *boat_ref;

	int input_count = 0;
	InputArea **input_list;
	
};


#endif