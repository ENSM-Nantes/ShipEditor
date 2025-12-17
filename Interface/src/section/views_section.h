#ifndef VIEWS_SECTION_H
#define VIEWS_SECTION_H

#include "section.h"
#include <vector>
#include <gtkmm/grid.h>

class ViewsSection : public SectionSuperClass {
public:
	ViewsSection();
	~ViewsSection();

	void update() override;
	void reset() override;
	bool hasFormatError() override;
	bool hasChanged() override;

private:
	Gtk::Grid m_grid;
	Gtk::Button m_add_view_button;

	struct Row {
		InputArea* vec3; // X,Y,Z
		InputArea* elevated; // bool
		Gtk::Button* del_btn;
	};

	std::vector<Row> m_rows;

	void rebuild_ui();
	void on_add_view();
	void on_delete_view(size_t index);
};

#endif
