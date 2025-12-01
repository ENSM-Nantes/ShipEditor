#include "pano_section.h"
#include <sstream>

PanoSection::PanoSection(Boat* boat)
: SectionSuperClass(), m_boat(boat)
{
    set_label("Pano");
    m_grid.set_row_spacing(5);
    m_grid.set_column_spacing(5);

    // connect add button once
    m_add_pano_button.signal_clicked().connect(sigc::mem_fun(*this, &PanoSection::on_add_pano));

    if (m_boat) loadBoat(m_boat);
    set_child(m_grid);
}

PanoSection::~PanoSection() {
    // cleanup
    for (auto &r : m_rows) {
        if (r.file) delete r.file;
        if (r.yaw) delete r.yaw;
        if (r.pitch) delete r.pitch;
        if (r.roll) delete r.roll;
        if (r.del_btn) delete r.del_btn;
    }
}

void PanoSection::loadBoat(Boat* b) {
    m_boat = b;
    rebuild_ui();
}

void PanoSection::rebuild_ui() {
    // clear grid children
    for (auto &child : m_grid.get_children()) child->unparent();

    // delete previous widgets
    for (auto &r : m_rows) {
        if (r.file) delete r.file;
        if (r.yaw) delete r.yaw;
        if (r.pitch) delete r.pitch;
        if (r.roll) delete r.roll;
        if (r.del_btn) delete r.del_btn;
    }
    m_rows.clear();

    if (!m_boat) return;

    // build rows
    int row = 0;
    for (size_t i = 0; i < m_boat->pano.file.size(); ++i) {
        Row r{};
        // file (string)
        r.file = new InputArea("File", &m_boat->pano.file[i]);
        r.file->show();
        m_grid.attach(*r.file, 0, row, 1, 1);

        // yaw
        r.yaw = new InputArea("Yaw", &m_boat->pano.yaw[i]);
        r.yaw->show();
        m_grid.attach(*r.yaw, 1, row, 1, 1);

        // pitch
        r.pitch = new InputArea("Pitch", &m_boat->pano.pitch[i]);
        r.pitch->show();
        m_grid.attach(*r.pitch, 2, row, 1, 1);

        // roll
        r.roll = new InputArea("Roll", &m_boat->pano.roll[i]);
        r.roll->show();
        m_grid.attach(*r.roll, 3, row, 1, 1);

        // delete button
        r.del_btn = new Gtk::Button("X");
        r.del_btn->show();
        // capture index by value
        r.del_btn->signal_clicked().connect([this, i]() { on_delete_pano(i); });
        m_grid.attach(*r.del_btn, 4, row, 1, 1);

        m_rows.push_back(r);
        ++row;
    }

    // add button at bottom spanning 5 columns
    m_add_pano_button.show();
    m_grid.attach(m_add_pano_button, 0, row, 5, 1);

    // fill input list for base class
    // gather all InputArea pointers in order
    std::vector<InputArea*> all;
    for (auto &r : m_rows) {
        all.push_back(r.file);
        all.push_back(r.yaw);
        all.push_back(r.pitch);
        all.push_back(r.roll);
    }
    // copy to internal storage: we will use a vector and set input_list to its data
    // but SectionSuperClass expects InputArea**; we can keep them in a temporary vector memberless
    // easiest: set input_count and input_list to point to first element of a static vector is unsafe.
    // Instead, build a dynamic array here and keep it until next rebuild; simple approach: reuse m_rows to iterate in reset/update.
    // We'll not rely on base class input_list; override update/reset by using m_rows directly.

    input_count = 0;
    input_list = nullptr;
    // populate UI from boat values
    // use reset to set entries using each InputArea's reset()
    for (auto &r : m_rows) r.file->reset();
    for (auto &r : m_rows) r.yaw->reset();
    for (auto &r : m_rows) r.pitch->reset();
    for (auto &r : m_rows) r.roll->reset();
}

void PanoSection::on_add_pano() {
    if (!m_boat) return;
    // Add default pano entry
    m_boat->pano.file.push_back(std::string(""));
    m_boat->pano.yaw.push_back(0.0f);
    m_boat->pano.pitch.push_back(0.0f);
    m_boat->pano.roll.push_back(0.0f);
    rebuild_ui();
}

void PanoSection::on_delete_pano(size_t index) {
    if (!m_boat) return;
    if (index >= m_boat->pano.file.size()) return;
    m_boat->pano.file.erase(m_boat->pano.file.begin() + (int)index);
    m_boat->pano.yaw.erase(m_boat->pano.yaw.begin() + (int)index);
    m_boat->pano.pitch.erase(m_boat->pano.pitch.begin() + (int)index);
    m_boat->pano.roll.erase(m_boat->pano.roll.begin() + (int)index);
    rebuild_ui();
}

void PanoSection::update() {
    for (auto &r : m_rows) {
        if (r.file) r.file->update();
        if (r.yaw) r.yaw->update();
        if (r.pitch) r.pitch->update();
        if (r.roll) r.roll->update();
    }
}
