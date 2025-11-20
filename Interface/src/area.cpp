#include "area.h"


/**
 * Constructor for the input of a string
 * @param str The label od the input
 * @param ref_var The variable to update from
 */
InputArea::InputArea(const Glib::ustring &str, std::string *ref_var) :
Box(Gtk::Orientation::HORIZONTAL),
m_label(),
m_entry() {
	// Save the pointer to the target variable
	type = TYPE_STRING;
	var_str = ref_var;

	// Set the label name
	m_label.set_text(str);

	// Display the content
	m_label.show();
	m_entry.show();

	// Create the box
	this->append(m_label);
	this->append(m_entry);
}

/**
 * Constructor for the input of a integer
 * @param str The label od the input
 * @param ref_var The variable to update from
 */
InputArea::InputArea(const Glib::ustring &str, int *ref_var) :
Box(Gtk::Orientation::HORIZONTAL),
m_label(),
m_entry() {
	// Save the pointer to the target variable
	type = TYPE_INTEGER;
	var_int = ref_var;

	// Set the label name
	m_label.set_text(str);

	// Display the content
	m_label.show();
	m_entry.show();

	// Create the box
	this->append(m_label);
	this->append(m_entry);
}

/**
 * Constructor for the input of a float
 * @param str The label od the input
 * @param ref_var The variable to update from
 */
InputArea::InputArea(const Glib::ustring &str, float *ref_var) :
Box(Gtk::Orientation::HORIZONTAL),
m_label(),
m_entry() {
	// Save the pointer to the target variable
	type = TYPE_FLOAT;
	var_float = ref_var;

	// Set the label name
	m_label.set_text(str);

	// Display the content
	m_label.show();
	m_entry.show();

	// Create the box
	this->append(m_label);
	this->append(m_entry);
}

/**
 * Constructor for the input of a boolean
 * @param str The label od the input
 * @param ref_var The variable to update from
 */
InputArea::InputArea(const Glib::ustring &str, bool *ref_var) :
Box(Gtk::Orientation::HORIZONTAL),
m_label(),
m_checkbutton() {
	// Save the pointer to the target variable
	type = TYPE_BOOL;
	var_bool = ref_var;

	// Set the label name
	m_label.set_text(str);

	// Display the content
	m_label.show();
	m_checkbutton.show();

	// Create the box
	this->append(m_label);
	this->append(m_checkbutton);
}


/**
 * Copy the value in the entry into the corresponding pointer
 */
void InputArea::update() {
	if (type == TYPE_BOOL) {
		// Copy the value
		*var_bool = m_checkbutton.get_active();
	} else {
		// Convert the EntryBuffer into a string
		std::string raw_text = m_entry.get_buffer()->get_text();
		switch(type) {
			case TYPE_STRING:
				// Copy the value
				*var_str = raw_text;
				break;
			case TYPE_INTEGER:
				// Convert then copy the value
				*var_int = std::stoi(raw_text);
				break;
			case TYPE_FLOAT:
				// Convert then copy the value
				*var_float = std::stof(raw_text);
				break;
			default:
				// TODO: create an error
				break;
		}
	}
}

/**
 * Reset the value from the right pointer into the entry
 */
void InputArea::reset() {
	if (type == TYPE_BOOL) {
		m_checkbutton.set_active(*var_bool);
	} else {
		std::string raw_text;
		switch(type) {
			case TYPE_STRING:
				raw_text = *var_str;
				break;
			case TYPE_INTEGER:
				raw_text = std::to_string(*var_int);
				break;
			case TYPE_FLOAT:
				raw_text = std::to_string(*var_float);
				break;
			default:
				// TODO: create an error
				break;
		}

		if (raw_text.length()) {
			m_entry.get_buffer()->set_text(raw_text);
		}
	}
}