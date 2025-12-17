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
m_compass_section(),
m_general_section(),
m_propertie_section(),
m_radar_screen_section(),
m_rudder_section(),
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
	m_compass_section.show();
	m_general_section.show();
	m_propertie_section.show();
	m_radar_screen_section.show();
	m_rudder_section.show();
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
	m_box_edit.append(m_radar_screen_section);
	m_box_edit.append(m_rudder_section);
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

	
	
	
	


	// Configure the paned
	m_paned.set_margin(10);
	m_paned.set_start_child(m_box_left_side);
	m_paned.set_end_child(m_scroll_edit);

	m_paned.set_position(180); // Pour la taille du paneau

	
	// Add the box in this window:
	set_child(m_paned);
	
}


void MainWindow::boat_callback(Gtk::ListBoxRow *boat_row) {
	if (!boat_row) {
		std::cout << "Unselected a boat" << std::endl;
		return;
	}

	// Try a safe cast to BoatRow and load the associated Boat
	BoatRow* br = dynamic_cast<BoatRow*>(boat_row);
	if (!br) {
		std::cerr << "Warning: selected row is not a BoatRow" << std::endl;
		return;
	}

	std::cout << "Selected a boat" << std::endl;
	loadBoat(&br->boat);
}


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
	m_compass_section.update();
	m_general_section.update();
	m_propertie_section.update();
	m_radar_screen_section.update();
	m_rudder_section.update();
	m_weather_section.update();
	m_wheel_section.update();
	m_sails_section.update();
	m_pano_section.update();
	m_views_section.update();
}

void MainWindow::reset() {
	m_compass_section.reset();
	m_general_section.reset();
	m_propertie_section.reset();
	m_radar_screen_section.reset();
	m_rudder_section.reset();
	m_weather_section.reset();
	m_wheel_section.reset();
	m_sails_section.reset();
	m_pano_section.reset();
	m_views_section.reset();
}


void MainWindow::on_save_clicked() {
    // First, apply UI -> Boat
    update();

    if (!m_current_boat) {
        std::cerr << "No boat selected to save." << std::endl;
        return;
    }

    BoatManager mgr;
    // Use the same base folder as the loader expects
    std::string base = "../../FileConverter/transformation";
    if (mgr.saveBoat(base, *m_current_boat)) {
        std::cout << "Boat saved successfully." << std::endl;
    } else {
        std::cerr << "Failed to save boat." << std::endl;
    }
}

void MainWindow::on_new_clicked() {
    // Create a new empty Boat with default values
    Boat* new_boat = new Boat();
    new_boat->displayName = "NewBoat";
    new_boat->fileName = "boat.json";
    new_boat->filePath = "";  // Empty path indicates it's a new boat
    
    // Initialize with default values
    new_boat->scaleFactor = 1.0f;
    new_boat->yCorrection = 0.0f;
    new_boat->angleCorrection = 0;
    new_boat->depth = 0.0f;
    new_boat->hasGPS = false;
    new_boat->hasDepthSounder = false;
    new_boat->maxDepth = 0.0f;
    new_boat->makeTransparent = false;
    new_boat->maxPropulsionForce = 0.0f;
    new_boat->asternEfficiency = 0.0f;
    new_boat->blockCoefficient = 0.0f;
    new_boat->mass = 0.0f;
    new_boat->inertia = 0.0f;
    new_boat->buffet = 0.0f;
    new_boat->swell = 0.0f;
    new_boat->windage = 0.0f;
    new_boat->windageTurnEffect = 0.0f;
    new_boat->deviationMaximum = 0.0f;
    new_boat->deviationMaximumHeading = 0.0f;
    new_boat->rollPeriod = 0.0f;
    new_boat->pitchPeriod = 0.0f;
    new_boat->maxRevs = 0;
    new_boat->maxSpeedAhead = 0.0f;
    new_boat->centrifugalDriftEffect = 0.0f;
    new_boat->hasRateOfTurnIndicator = false;

    m_current_boat = new_boat;
    
    // Reset UI and load the new boat
    reset();
    loadBoat(new_boat);
    
    std::cout << "Created new boat 'NewBoat'. Fill in the details and click Save." << std::endl;
}
