#ifndef PANO_SECTION_H
#define PANO_SECTION_H

#include "section.h"
#include <vector>
#include <gtkmm/grid.h>

class PanoSection : public SectionSuperClass {
public:
    PanoSection(Boat* boat = nullptr);
    ~PanoSection();

    void update();
    void loadBoat(Boat* b);

private:
    Boat* m_boat = nullptr;
    Gtk::Grid m_grid;
    Gtk::Button m_add_pano_button{"+ Add Pano"};

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
