#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

// Import for functional purpose
#include "input_area.h"
#include "section/section.h"

// Sections import
#include "section/general_section.h"
#include "section/sails_section.h"
#include "section/pano_section.h"
#include "section/views_section.h"

#define WINDOWS_SECTION_COUNT 4  /** @brief Nombre de sections affichées dans la fenêtre */

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow() = default;
    
    void loadBoat(Boat *b);   /** @brief Charge un Boat dans toutes les sections */
    void update();            /** @brief Applique les modifications de l’UI vers Boat */
    void reset();             /** @brief Réinitialise l’UI depuis Boat */

private:
    void buttonClick();
    void buttonClickUpdate();
    void buttonClickReset();

    Gtk::Button m_button, m_button_update, m_button_reset;
    Gtk::Box m_box;
    Gtk::Label m_label1, m_label2;

    std::string test_var_string = "file.txt";
    int test_var_int = 10;
    float test_var_float = 56.3;
    bool test_var_bool = 1;

    InputArea m_area0, m_area1, m_area2, m_area3;

    // Sections
    GeneralSection m_general_frame;
    SailsSection m_sails_frame;
    PanoSection m_pano_frame;
    ViewsSection m_views_frame;

    SectionSuperClass* section_list[WINDOWS_SECTION_COUNT] = {
        &m_general_frame,
        &m_sails_frame,
        &m_pano_frame,
        &m_views_frame
    };
};

#endif