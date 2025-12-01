#include "views_section.h"

ViewsSection::ViewsSection(Boat* boat)
: SectionSuperClass(), m_boat(boat)
{
    set_label("Views");
    m_grid.set_row_spacing(5);
    m_grid.set_column_spacing(5);

    // connect add once
    m_add_view_button.signal_clicked().connect(sigc::mem_fun(*this, &ViewsSection::on_add_view));

    if (m_boat) loadBoat(m_boat);
    set_child(m_grid);
}

ViewsSection::~ViewsSection() {
    for (auto &r : m_rows) {
        if (r.vec3) delete r.vec3;
        if (r.elevated) delete r.elevated;
        if (r.del_btn) delete r.del_btn;
    }
}

void ViewsSection::loadBoat(Boat* b) {
    m_boat = b;
    rebuild_ui();
}

void ViewsSection::rebuild_ui() {
    for (auto &child : m_grid.get_children()) child->unparent();

    for (auto &r : m_rows) {
        if (r.vec3) delete r.vec3;
        if (r.elevated) delete r.elevated;
        if (r.del_btn) delete r.del_btn;
    }
    m_rows.clear();

    if (!m_boat) return;

    int row = 0;
    for (size_t i = 0; i < m_boat->viewList.views.size(); ++i) {
        View &v = m_boat->viewList.views[i];

        Row r{};
        r.vec3 = new InputArea("View", &v.vector[0], true);
        r.vec3->show();
        m_grid.attach(*r.vec3, 0, row, 3, 1);

        r.elevated = new InputArea("Elevated", &v.elevated);
        r.elevated->show();
        m_grid.attach(*r.elevated, 3, row, 1, 1);

        r.del_btn = new Gtk::Button("X");
        r.del_btn->show();
        r.del_btn->signal_clicked().connect([this, i]() { on_delete_view(i); });
        m_grid.attach(*r.del_btn, 4, row, 1, 1);

        m_rows.push_back(r);
        ++row;
    }

    m_add_view_button.show();
    m_grid.attach(m_add_view_button, 0, row, 5, 1);

    // populate UI
    for (auto &r : m_rows) {
        r.vec3->reset();
        r.elevated->reset();
    }
}

void ViewsSection::on_add_view() {
    if (!m_boat) return;
    View v{};
    v.vector[0] = v.vector[1] = v.vector[2] = 0.0f;
    v.elevated = false;
    m_boat->viewList.views.push_back(v);
    rebuild_ui();
}

void ViewsSection::on_delete_view(size_t index) {
    if (!m_boat || index >= m_boat->viewList.views.size()) return;
    m_boat->viewList.views.erase(m_boat->viewList.views.begin() + (int)index);
    rebuild_ui();
}

void ViewsSection::update() {
    for (auto &r : m_rows) {
        if (r.vec3) r.vec3->update();
        if (r.elevated) r.elevated->update();
    }
}
