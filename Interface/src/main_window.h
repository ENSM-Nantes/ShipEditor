#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

// Import for functionnal purpose
#include "input_area.h"
#include "section/section.h"

// Sections import
#include "section/general_section.h"




#define WINDOWS_SECTION_COUNT 1

class MainWindow : public Gtk::Window {
public:
	MainWindow();
	virtual ~MainWindow() = default;
	
private:
	void buttonClick();
	void buttonClickUpdate();
	void buttonClickReset();
	Gtk::Button m_button, m_button_reset, m_button_update;
	Gtk::Box m_box;
	Gtk::Label m_label1, m_label2;

	std::string test_var_string = "file.txt";
	int test_var_int = 10;
	float test_var_float = 56.3;
	bool test_var_bool = 1;

	InputArea m_area0, m_area1, m_area2, m_area3;
	



	void loadBoat(Boat *b);
	void update();
	void reset();


	
	//SectionSuperClass m_general_frame, m_radar_screen_frame, m_proprtie_frame;
	GeneralSection m_general_frame;
	SectionSuperClass *section_list[WINDOWS_SECTION_COUNT] = {&m_general_frame};
};

#endif