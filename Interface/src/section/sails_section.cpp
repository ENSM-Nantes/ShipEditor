#include "sails_section.h"
#include <string>
#include <sstream>

SailsSection::SailsSection(Boat* boat)
: SectionSuperClass(), m_boat(boat)
{
    // Titre du frame
    set_label("Sails");

    // Orientation verticale via Grid
    m_grid.set_row_spacing(5);
    m_grid.set_column_spacing(5);

    if (m_boat) {
        loadBoat(m_boat);
    }

    // Ajouter la grille au Frame (GTK4)
    set_child(m_grid);
}

void SailsSection::loadBoat(Boat* b) {
    m_boat = b;
    m_inputs.clear();

    // Vider l'ancienne grille
    for (auto& child : m_grid.get_children()) {
        child->unparent();
    }

    if (!m_boat) return;

    // Pour chaque voile du bateau
    int row = 0;
    for (size_t i = 0; i < m_boat->sails.sails.size(); ++i) {
        Sail& sail = m_boat->sails.sails[i];

        std::ostringstream label_x, label_y, label_z;
        label_x << "Sail " << i << " X:";
        label_y << "Sail " << i << " Y:";
        label_z << "Sail " << i << " Z:";

        InputArea* in_x = new InputArea(label_x.str(), &sail.vector[0], true);
        InputArea* in_y = new InputArea(label_y.str(), &sail.vector[1], true);
        InputArea* in_z = new InputArea(label_z.str(), &sail.vector[2], true);

        m_grid.attach(*in_x, 0, row, 1, 1);
        m_grid.attach(*in_y, 1, row, 1, 1);
        m_grid.attach(*in_z, 2, row, 1, 1);

        m_inputs.push_back(in_x);
        m_inputs.push_back(in_y);
        m_inputs.push_back(in_z);

        ++row;
    }

    // Lier les entrées à SectionSuperClass
    input_count = m_inputs.size();
    input_list = m_inputs.data();
}

void SailsSection::update() {
    for (auto& input : m_inputs) {
        input->update();
    }
}
