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

    // Connect the "Add Sail" button signal only once, in constructor
    m_add_sail_button.signal_clicked().connect(sigc::mem_fun(*this, &SailsSection::on_add_sail));

    if (m_boat) {
        loadBoat(m_boat);
    }

    // Ajouter la grille au Frame (GTK4)
    set_child(m_grid);
}

void SailsSection::loadBoat(Boat* b) {
    m_boat = b;
    if (!m_boat) return;
    rebuild_ui();
}

void SailsSection::rebuild_ui() {
    // Clear the grid and delete old widgets
    for (auto& child : m_grid.get_children()) {
        child->unparent();
    }
    for (auto p : m_inputs) {
        if (p) delete p;
    }
    for (auto p : m_delete_buttons) {
        if (p) delete p;
    }
    m_inputs.clear();
    m_delete_buttons.clear();

    if (!m_boat) return;

    // Pour chaque voile du bateau
    int row = 0;
    for (size_t i = 0; i < m_boat->sails.sails.size(); ++i) {
        Sail& sail = m_boat->sails.sails[i];

        std::ostringstream label;
        label << "Sail " << i;

        // Create InputArea for this sail (vector mode)
        InputArea* in = new InputArea(label.str(), &sail.vector[0], true);
        in->show();
        m_grid.attach(*in, 0, row, 3, 1);
        m_inputs.push_back(in);

        // Create delete button for this sail
        Gtk::Button* delete_btn = new Gtk::Button("X");
        delete_btn->show();
        delete_btn->signal_clicked().connect([this, i]() { on_delete_sail(i); });
        m_grid.attach(*delete_btn, 3, row, 1, 1);
        m_delete_buttons.push_back(delete_btn);

        ++row;
    }

    // Add "Add Sail" button at the bottom
    m_add_sail_button.show();
    // Note: we only connect once in constructor; rebuild_ui() will reattach without reconnecting
    m_grid.attach(m_add_sail_button, 0, (int)m_boat->sails.sails.size(), 4, 1);

    // Update the input list for the base class
    input_count = (int)m_inputs.size();
    input_list = m_inputs.data();

    // Populate UI from Boat values
    reset();
}

void SailsSection::on_add_sail() {
    if (!m_boat) return;
    // Add a new sail with default vector (0, 0, 0)
    Sail new_sail;
    new_sail.vector[0] = 0.0f;
    new_sail.vector[1] = 0.0f;
    new_sail.vector[2] = 0.0f;
    m_boat->sails.sails.push_back(new_sail);
    rebuild_ui();
}

void SailsSection::on_delete_sail(size_t sail_index) {
    if (!m_boat || sail_index >= m_boat->sails.sails.size()) return;
    m_boat->sails.sails.erase(m_boat->sails.sails.begin() + (int)sail_index);
    rebuild_ui();
}

void SailsSection::update() {
    for (auto& input : m_inputs) {
        input->update();
    }
}
