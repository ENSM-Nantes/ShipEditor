#ifndef AREA_H
#define AREA_H

#include<iostream>
#include <string>
#include <gtkmm.h>

using namespace Gtk;

class InputArea: public Box {
public:
	enum variable_type {
		TYPE_STRING = 0,
		TYPE_INTEGER,
		TYPE_FLOAT,
		TYPE_BOOL
	};

	InputArea(const Glib::ustring &str, std::string *ref_var);
	InputArea(const Glib::ustring &str, int *ref_var);
	InputArea(const Glib::ustring &str, float *ref_var);
	InputArea(const Glib::ustring &str, bool *ref_var);
	~InputArea() {}

	void update();
	void reset();
protected:
	int type;
	std::string *var_str;
	int *var_int;
	float *var_float;
	bool *var_bool;

	Label m_label;
	Entry m_entry;
	CheckButton  m_checkbutton;
}; 




#endif