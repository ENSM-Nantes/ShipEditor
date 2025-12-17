#ifndef PANO_SECTION_H
#define PANO_SECTION_H

#include "section.h"
#include <vector>
#include <gtkmm/grid.h>

class PanoSection : public SectionSuperClass {
public:
	PanoSection();
	~PanoSection();

	void update() override;
	void reset() override;
	bool hasFormatError() override;
	bool hasChanged() override;

private:
	Gtk::Grid m_grid;
	Gtk::Button m_add_pano_button;

	struct Row {
		InputArea* file;
		InputArea* yaw;
		InputArea* pitch;
		InputArea* roll;
		Gtk::Button* del_btn;
	};

	std::vector<Row> m_rows;

	void rebuild_ui();
	void on_add_pano();
	void on_delete_pano(size_t index);
};

#endif
