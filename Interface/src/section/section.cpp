#include "section.h"


/**
 * Constructor of a section
 * @param label the name of the section
 */
Section::Section(const Glib::ustring &label): Frame(label) {
	this->set_margin_top(5);
	this->set_margin_bottom(5);
	this->set_margin_start(10);
	this->set_margin_end(10);
}

/**
 * Constructor of a section
 * 
 */
Section::Section()
{

}

/**
 * Destructor of a section
 * 
 */
Section::~Section()
{
	
}


void Section::load(Boat *aBoat)
{
  mBoat = *aBoat;
}
