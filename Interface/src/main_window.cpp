#include <iostream>
#include <filesystem>
#include "main_window.h"
#include "BoatManager.hpp"
#include "BoatRow.hpp"




MainWindow::MainWindow():
// Main window
m_paned(Gtk::Orientation::HORIZONTAL),
m_scroll_edit(),
m_scroll_boat(),
m_box_left_side(Gtk::Orientation::VERTICAL),
m_box_action_button(Gtk::Orientation::HORIZONTAL),
m_box_edit(Gtk::Orientation::VERTICAL),

// Boat area
m_boat_list(),
m_button_reset("Reset"),
m_button_save("Save"),
m_button_new("New"),
m_button_delete("Delete"),

// Current boat
m_current_boat(nullptr),

// Edit area
m_azimuth_section(),
m_compass_section(),
m_dynamics_section(),
m_general_section(),
m_pano_section(),
m_propertie_section(),
m_propulsion_section(),
m_radar_screen_section(),
m_rudder_section(),
m_sails_section(),
m_views_section(),
m_weather_section(),
m_wheel_section()
{
	// Configure this window:
	this->set_default_size(600, 400);

	// Configure the scrooled window
	m_scroll_boat.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
	m_scroll_boat.set_expand();
	m_scroll_edit.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
	m_scroll_edit.set_expand();

	
	/* ********************* */
	/* ***** Edit Area ***** */
	/* ********************* */
	// Show every section
	m_azimuth_section.show();
	m_compass_section.show();
	m_dynamics_section.show();
	m_general_section.show();
	m_pano_section.show();
	m_propertie_section.show();
	m_propulsion_section.show();
	m_radar_screen_section.show();
	m_rudder_section.show();
	m_sails_section.show();
	m_views_section.show();
	m_weather_section.show();
	m_wheel_section.show();
	
	// Pack all elements in the box:
	m_box_edit.append(m_compass_section);
	m_box_edit.append(m_general_section);
	m_box_edit.append(m_propertie_section);
	m_box_edit.append(m_propulsion_section);
	m_box_edit.append(m_dynamics_section);
	m_box_edit.append(m_radar_screen_section);
	m_box_edit.append(m_pano_section);
	m_box_edit.append(m_azimuth_section);
	m_box_edit.append(m_rudder_section);
	m_box_edit.append(m_sails_section);
	m_box_edit.append(m_views_section);
	m_box_edit.append(m_weather_section);
	m_box_edit.append(m_wheel_section);

	// Make the box visible and usable with the scroll bar
	m_box_edit.show();
	m_scroll_edit.set_child(m_box_edit);


	/* ********************* */
	/* ***** Boat Area ***** */
	/* ********************* */

	// Link the signals to function
	m_boat_list.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::boat_callback));
	m_button_save.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::update));
	m_button_reset.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::reset));
	m_button_new.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::newBoat));

	// Put an icon in the buttons
	// TODO

	// Show the buttons
	m_button_new.show();
	m_button_delete.show();
	m_button_save.show();
	m_button_reset.show();

	// Pack the button in the box
	m_box_action_button.append(m_button_new);
	m_box_action_button.append(m_button_delete);
	m_box_action_button.append(m_button_save);
	m_box_action_button.append(m_button_reset);

	// Make the list usable with the scroll bar
	m_scroll_boat.set_child(m_boat_list);

	// Pack the list and the buttons in the box
	m_box_left_side.append(m_scroll_boat);
	m_box_left_side.append(m_box_action_button);

	m_box_action_button.show();
	m_box_left_side.show();

	
	
	// Select the first boat by default
	loadBoat(&(((BoatRow*)m_boat_list.get_row_at_index(0))->boat));
	


	// Configure the paned
	m_paned.set_margin(10);
	m_paned.set_start_child(m_box_left_side);
	m_paned.set_end_child(m_scroll_edit);
	m_paned.set_position(180);

	
	// Add the box in this window:
	set_child(m_paned);
	
}


void MainWindow::boat_callback(Gtk::ListBoxRow *boat_row) {
	if (!hasChanged()) {
		loadBoat(&(((BoatRow*)boat_row)->boat));
	} else {
		infoBubble("Unsaved data", "You have unsaved data in some fields.\nPress \"Save\" to save or \"Reset\" to reset");
	}
}


/**
 * Load a boat to edit its properties
 * @param b The reference of a boat
 */
void MainWindow::loadBoat(Boat *b) {
	if (b == nullptr) return;
	
	// Save reference to current boat
	m_current_boat = b;
	
	for (int i = 0; i < WINDOWS_SECTION_COUNT; i++) {
		section_list[i]->loadBoat(b);
	}
}

/**
 * Update all the field of all the sections (see InputArea::update())
 */
void MainWindow::update() {
	// First, update the boat data from UI fields
	for (int i = 0; i < WINDOWS_SECTION_COUNT; i++) {
		section_list[i]->update();
	}

	if (hasFormatError()) {
		infoBubble("Input format error", "Correct the fields in red then press \"Save\"");
		return;
	}
	
	// Save the boat to JSON file
	if (m_current_boat != nullptr) {
		BoatManager manager;
		
		// First, rename the boat folder if the name has changed
		bool renamed = manager.renameBoat(*m_current_boat);
		if (!renamed) {
			infoBubble("Error", "Failed to rename the boat folder. The name might already exist.");
			return;
		}
		
		// Then save the boat data
		bool success = manager.saveBoat(*m_current_boat);
		
		if (success) {
			infoBubble("Saved", "The boat has been saved successfully.");
		} else {
			infoBubble("Error", "Failed to save the boat.");
		}
	}
}

/**
 * Reset all the field of all the sections (see InputArea::reset())
 */
void MainWindow::reset() {
	for (int i = 0; i < WINDOWS_SECTION_COUNT; i++) {
		section_list[i]->reset();
	}
}

/**
 * Create a new boat with default values and save it
 */
void MainWindow::newBoat() {
	namespace fs = std::filesystem;
	
	// Find a unique name for the new boat
	std::string baseName = "NewBoat";
	std::string uniqueName = baseName;
	int counter = 1;
	
	fs::path transformationPath = BoatManager::getTransformationPath();
	while (fs::exists(transformationPath / uniqueName)) {
		uniqueName = baseName + std::to_string(counter);
		counter++;
	}
	
	// Create a new boat with default values (C++ initializes to 0/false)
	Boat newBoat = {};
	newBoat.displayName = uniqueName;
	newBoat.fileName = "boat.X";
	newBoat.scaleFactor = 1.0f;
	newBoat.asternEfficiency = 1.0f;
	newBoat.wheel.scale = 1.0f;
	// filePath reste vide pour indiquer un nouveau bateau
	
	// Save the boat immediately
	BoatManager manager;
	bool success = manager.saveBoat(newBoat);
	
	if (success) {
		// Add the new boat to the list
		BoatRow* row = Gtk::manage(new BoatRow(newBoat));
		m_boat_list.append(*row);
		
		// Load the new boat in the editor (use the boat from the row)
		loadBoat(&(row->boat));
		
		infoBubble("New Boat Created", "A new boat \"" + uniqueName + "\" has been created and saved successfully.");
	} else {
		infoBubble("Error", "Failed to create the new boat.");
	}
}

/**
 * Retreive error from all the field (see InputArea::hasFormatError())
 */
bool MainWindow::hasFormatError() {
	bool flag = false;
	for (int i = 0; i < WINDOWS_SECTION_COUNT; i++) {
		if (section_list[i]->hasFormatError()) {
			flag = true;
			break;
		}
	}
	return flag;
}

/**
 * Retreive a change from all the field (see InputArea::hasChanged())
 */
bool MainWindow::hasChanged() {
	bool flag = false;
	for (int i = 0; i < WINDOWS_SECTION_COUNT; i++) {
		if (section_list[i]->hasChanged()) {
			flag = true;
			break;
		}
	}
	return flag;
}

void MainWindow::infoBubble(const Glib::ustring &message, const Glib::ustring &detail) {
	if (!m_dialog) {
		m_dialog = Gtk::AlertDialog::create();
	}
	
	// Reset values that may have been set by on_button_question_clicked().
	//m_pDialog->set_buttons({});
	m_dialog->set_default_button(-1);
	m_dialog->set_cancel_button(-1);

	m_dialog->set_modal(); // Block the window until the dialog closes


	m_dialog->set_message(message);
	m_dialog->set_detail(detail);
	m_dialog->show(*this);
}