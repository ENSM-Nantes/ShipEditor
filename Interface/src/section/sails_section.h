#ifndef SAILS_SECTION_H
#define SAILS_SECTION_H

#include "section.h"
#include <vector>
#include <memory>
#include <gtkmm/grid.h>
#include "../input_area.h"

/**
 * Section dédiée aux voiles (Sails)
 */
class SailsSection : public SectionSuperClass {
public:
	SailsSection();

	void update() override;
	void reset() override;
	bool hasFormatError() override;
	bool hasChanged() override;

private:
	Gtk::Grid m_grid;
	Gtk::Box m_box;
	Gtk::Button m_add_sail_button;
	InputArea m_size, m_type;


	std::vector<InputArea*> m_inputs; // un InputArea par voile
	std::vector<Gtk::Button*> m_delete_buttons; // boutons pour supprimer les voiles

	void on_add_sail();
	void on_delete_sail(size_t sail_index);
	void rebuild_ui(); // reconstruit la grille et les boutons
};

#endif
