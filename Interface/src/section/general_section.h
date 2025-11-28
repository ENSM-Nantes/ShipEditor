#ifndef GENERAL_FRAME_H
#define GENERAL_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "section.h"

#define GENERAL_INPUT_COUNT 8

using namespace Gtk;

class GeneralSection: public SectionSuperClass {
public:
	GeneralSection();
	~GeneralSection();
	void loadBoat(Boat *b) override;

protected:
	Grid m_grid;

	// InputArea are created when a Boat is loaded (to get valid pointers to Boat members)
	InputArea *m_filename = nullptr;
	InputArea *m_ycorrection = nullptr;
	InputArea *m_gps = nullptr;
	InputArea *m_scale_factor = nullptr;
	InputArea *m_depth = nullptr;
	InputArea *m_depth_sounder = nullptr;
	InputArea *m_max_depth = nullptr;
	InputArea *m_make_transparent = nullptr;

	InputArea *input_list_local[GENERAL_INPUT_COUNT] = {nullptr};
};


#endif