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

    std::vector<InputArea*> m_inputs; // un InputArea par voile
};

#endif
