#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

//#include "edit_area.h"
#include "area.h"

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
	//EditArea *area;
};

#endif