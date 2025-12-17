#include <iostream>
#include "BoatManager.hpp"
#include "main_window.h"

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
	m_wheel_section(),
	m_sails_section(),
	m_pano_section(),
	m_views_section()
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
	// Show newly added sections
	m_sails_section.show();
	m_pano_section.show();
	m_views_section.show();
	
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
	// Append new sections to the edit box
	m_box_edit.append(m_sails_section);
	m_box_edit.append(m_pano_section);
	m_box_edit.append(m_views_section);

	// Make the box visible and usable with the scroll bar
	m_box_edit.show();
	m_scroll_edit.set_child(m_box_edit);


	/* ********************* */
	/* ***** Boat Area ***** */
	/* ********************* */

	// Link the signals to function
	m_boat_list.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::boat_callback));
	m_button_save.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_save_clicked));
	m_button_new.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_new_clicked));
	m_button_reset.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::reset));

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

	m_paned.set_position(180); // Pour la taille du paneau

	
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
    if (!b) return;
	// remember current boat for save
	m_current_boat = b;
	// Call each section's loadBoat directly so derived implementations run
	m_compass_section.loadBoat(b);
	m_general_section.loadBoat(b);
	m_propertie_section.loadBoat(b);
	m_radar_screen_section.loadBoat(b);
	m_rudder_section.loadBoat(b);
	m_weather_section.loadBoat(b);
	m_wheel_section.loadBoat(b);
	m_sails_section.loadBoat(b);
	m_pano_section.loadBoat(b);
	m_views_section.loadBoat(b);
}

void MainWindow::update() {
	for (int i = 0; i < WINDOWS_SECTION_COUNT; i++) {
		section_list[i]->update();
	}

	if (hasFormatError()) {
		infoBubble("Input format error", "Correct the fields in red then press \"Save\"");
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