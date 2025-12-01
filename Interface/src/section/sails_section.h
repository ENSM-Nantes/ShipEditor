#ifndef SAILS_SECTION_H
#define SAILS_SECTION_H

#include "section.h"
#include <vector>
#include <memory>
#include <gtkmm/grid.h>

/**
 * Section dédiée aux voiles (Sails)
 */
class SailsSection : public SectionSuperClass {
public:
    SailsSection(Boat* boat = nullptr);

    void update() override;      // surcharge pour mettre à jour depuis les entrées
    void loadBoat(Boat* b) override; // surcharge pour charger un bateau

private:
    Boat* m_boat = nullptr;
    Gtk::Grid m_grid;
    Gtk::Button m_add_sail_button{"+ Add Sail"};

    std::vector<InputArea*> m_inputs; // un InputArea par voile
    std::vector<Gtk::Button*> m_delete_buttons; // boutons pour supprimer les voiles

    void on_add_sail();
    void on_delete_sail(size_t sail_index);
    void rebuild_ui(); // reconstruit la grille et les boutons
};

#endif
