#include "input_area.h"

/**
 * Constructor for the input of a string
 * @param str The label od the input
 * @param ref_var The variable to update from
 */
InputArea::InputArea(const Glib::ustring &str, std::string *ref_var) :
Box(Orientation::HORIZONTAL),
m_label(),
m_entry() {
	// Save the pointer to the target variable
	type = TYPE_STRING;
	var_str = ref_var;
	if (ref_var == nullptr) type = TYPE_NULL;

	// Set the label name
	m_label.set_text(str);

	// Show the variable type in the placeholder (when it's empty)
	m_entry.set_placeholder_text("string");

	// Layout
	this->set_margin_top(2);
	this->set_margin_bottom(2);
	this->set_margin_start(2);
	this->set_margin_end(2);
	m_entry.set_margin_start(5);

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
	if (ref_var == nullptr) type = TYPE_NULL;

	// Set the label name
	m_label.set_text(str);

	// Show the variable type in the placeholder (when it's empty)
	m_entry.set_placeholder_text("integer");

	// Layout
	this->set_margin_top(2);
	this->set_margin_bottom(2);
	this->set_margin_start(2);
	this->set_margin_end(2);
	m_entry.set_margin_start(5);

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
	if (ref_var == nullptr) type = TYPE_NULL;

	// Set the label name
	m_label.set_text(str);

	// Show the variable type in the placeholder (when it's empty)
	m_entry.set_placeholder_text("float");

	// Layout
	this->set_margin_top(2);
	this->set_margin_bottom(2);
	this->set_margin_start(2);
	this->set_margin_end(2);
	m_entry.set_margin_start(5);

	// Display the content
	m_label.show();
	m_entry.show();

	// Create the box
	this->append(m_label);
	this->append(m_entry);
}

/**
 * Constructor for the input of a double
 * @param str The label od the input
 * @param ref_var The variable to update from
 */
InputArea::InputArea(const Glib::ustring &str, double *ref_var) :
Box(Gtk::Orientation::HORIZONTAL),
m_label(),
m_entry() {
	// Save the pointer to the target variable
	type = TYPE_DOUBLE;
	var_double = ref_var;
	if (ref_var == nullptr) type = TYPE_NULL;

	// Set the label name
	m_label.set_text(str);

	// Show the variable type in the placeholder (when it's empty)
	m_entry.set_placeholder_text("float");

	// Layout
	this->set_margin_top(2);
	this->set_margin_bottom(2);
	this->set_margin_start(2);
	this->set_margin_end(2);
	m_entry.set_margin_start(5);

	// Display the content
	m_label.show();
	m_entry.show();

	// Create the box
	this->append(m_label);
	this->append(m_entry);
}

/**
 * Constructor for the input of a vector of three float
 * @param str The label od the input
 * @param ref_var The variable to update from
 * @param vector Force the constructor of a vector (useless)
 */
InputArea::InputArea(const Glib::ustring &str, float *ref_var, bool vector) :
Box(Gtk::Orientation::HORIZONTAL),
m_label(),
m_entry_x(),
m_entry_y(),
m_entry_z() {
	// Save the pointer to the target variable
	type = TYPE_VECTOR;
	var_vector = ref_var;
	if (ref_var == nullptr) type = TYPE_NULL;

	// Set the label name
	m_label.set_text(str);

	// Show the variable type in the placeholder (when it's empty)
	m_entry_x.set_placeholder_text("x");
	m_entry_y.set_placeholder_text("y");
	m_entry_z.set_placeholder_text("z");

	// Layout
	this->set_margin_top(2);
	this->set_margin_bottom(2);
	this->set_margin_start(2);
	this->set_margin_end(2);
	m_entry_x.set_margin_start(5);

	// Display the content
	m_label.show();
	m_entry_x.show();
	m_entry_y.show();
	m_entry_z.show();

	// Create the box
	this->append(m_label);
	this->append(m_entry_x);
	this->append(m_entry_y);
	this->append(m_entry_z);
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
	if (ref_var == nullptr) type = TYPE_NULL;

	// Set the label name
	m_label.set_text(str);

	// Layout
	this->set_margin_top(2);
	this->set_margin_bottom(2);
	this->set_margin_start(2);
	this->set_margin_end(2);
	m_checkbutton.set_margin_start(5);
	
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
	} else if (type == TYPE_VECTOR) {
		// Reset the flag if needed
		if (has_error) {
			has_error = false;
			for (int i = 0; i < 3; i++) {
				vector_entry[i]->remove_css_class("error");
			}
		}

		std::string raw_text;
		for (int i = 0; i < 3; i++) {
			raw_text = vector_entry[i]->get_buffer()->get_text();
			try {
				var_vector[i] = std::stof(raw_text);
			} catch  (const std::invalid_argument& ia) {
				errorCallback(vector_entry[i], ia);
				break;
			}
		}
	} else if (type != TYPE_NULL) {
		// Reset the flag if needed
		if (has_error) {
			has_error = false;
			m_entry.remove_css_class("error");
		}

		// Convert the EntryBuffer into a string
		std::string raw_text = m_entry.get_buffer()->get_text();
		try {
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
				case TYPE_DOUBLE:
					// Convert then copy the value
					*var_double = std::stod(raw_text);
				default:
					// TODO: create an error
					break;
			}
		} catch (const std::invalid_argument& ia) {
			errorCallback(&m_entry, ia);
		}
	}
}

/**
 * Reset the value from the right pointer into the entry
 */
void InputArea::reset() {
	if (type == TYPE_BOOL) {
		m_checkbutton.set_active(*var_bool);
	} else if (type == TYPE_VECTOR) {
		std::string raw_text;
		for (int i = 0; i < 3; i++) {
			raw_text = std::to_string(var_vector[i]);
			vector_entry[i]->get_buffer()->set_text(raw_text);
		}
	} else if (type != TYPE_NULL) {
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
			case TYPE_DOUBLE:
				raw_text = std::to_string(*var_double);
			default:
				// TODO: create an error
				break;
		}

		if (raw_text.length()) {
			m_entry.get_buffer()->set_text(raw_text);
		}
	}
}

/**
 * Return wether the input has formatting error like puting a word into an integer field
 * @return True if the field has a format error
 */
bool InputArea::hasFormatError() {
	return has_error;
}

/**
 * Return wether the input has changed
 * @return True if the field had changed since the last update
 */
bool InputArea::hasChanged() {
	// Field must be free of errors
	if (has_error) return true;

	bool flag = false;

	// Compare the saved value to the field
	if (type == TYPE_BOOL) {
		flag = (*var_bool != m_checkbutton.get_active());
	} else if (type == TYPE_VECTOR) {

		std::string raw_text;
		for (int i = 0; i < 3; i++) {
			raw_text = vector_entry[i]->get_buffer()->get_text();
			try {
				var_vector[i] = std::stof(raw_text);
			} catch  (const std::invalid_argument& ia) {
				errorCallback(vector_entry[i], ia);
				flag = true;
				break;
			}
		}
	} else if (type != TYPE_NULL) {
		// Convert the EntryBuffer into a string
		std::string raw_text = m_entry.get_buffer()->get_text();
		try {
			switch(type) {
				case TYPE_STRING:
					flag = (*var_str != raw_text);
					break;
				case TYPE_INTEGER:
					flag = (*var_int != std::stoi(raw_text));
					break;
				case TYPE_FLOAT:
					flag = (*var_float != std::stof(raw_text));
					break;
				case TYPE_DOUBLE:
					flag = (*var_double != std::stod(raw_text));
				default:
					// TODO: create an error
					break;
			}
		} catch (const std::invalid_argument& ia) {
			errorCallback(&m_entry, ia);
			flag = true;
		}
	}

	return flag;
}

void InputArea::errorCallback(Entry *entry, const std::invalid_argument& ia) {
	// Flag the error
	has_error = true;
	// Show the field concerned by the error
	entry->add_css_class("error");
	// Print the error in the console
	std::cerr << "Invalid argument: " << ia.what() << " in field: " << m_label.get_text() << std::endl;
}