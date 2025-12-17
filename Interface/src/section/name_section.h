#ifndef NAME_FRAME_H
#define NAME_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"


using namespace Gtk;

class NameSection: public SectionSuperClass {
public:
	NameSection();
	~NameSection() {}

	void update() override;
	void reset() override;
	bool hasFormatError() override;
	bool hasChanged() override;

protected:
	Box m_box;

	InputArea m_name, m_3d_file;
};


#endif