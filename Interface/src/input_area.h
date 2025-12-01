#ifndef AREA_H
#define AREA_H

#include <string>
#include <gtkmm.h>

using namespace Gtk;

class InputArea: public Box {
public:
	enum variable_type {
		TYPE_NULL = 0,
		TYPE_STRING,
		TYPE_INTEGER,
		TYPE_FLOAT,
		TYPE_DOUBLE,
		TYPE_VECTOR,
		TYPE_BOOL
	};

	InputArea(const Glib::ustring &str, std::string *ref_var);
	InputArea(const Glib::ustring &str, int *ref_var);
	InputArea(const Glib::ustring &str, float *ref_var);
	InputArea(const Glib::ustring &str, double *ref_var);
	InputArea(const Glib::ustring &str, float *ref_var, bool vector);
	InputArea(const Glib::ustring &str, bool *ref_var);
	~InputArea() {}

	void update();
	void reset();
protected:
	int type;
	std::string *var_str;
	int *var_int = nullptr;
	float *var_float = nullptr;
	double *var_double = nullptr;
	float *var_vector = nullptr;
	bool *var_bool = nullptr;

	Label m_label;
	Entry m_entry, m_entry_x, m_entry_y, m_entry_z;
	Entry *vector_entry[3] = {&m_entry_x, &m_entry_y, &m_entry_z};
	CheckButton  m_checkbutton;
}; 




#endif