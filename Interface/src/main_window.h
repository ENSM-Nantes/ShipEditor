#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>

#include <gtkmm.h>

// Import for functional purpose
#include "input_area.h"
#include "section/section.h"
// Boat list/row
#include "BoatRow.hpp"

// Sections import
#include "section/section.h" // Super class
#include "section/compass_section.h"
#include "section/general_section.h"
#include "section/propertie_section.h"
#include "section/radar_screen_section.h"
#include "section/rudder_section.h"
#include "section/weather_section.h"
#include "section/wheel_section.h"
#include "section/sails_section.h"
#include "section/pano_section.h"
#include "section/views_section.h"


#define WINDOWS_SECTION_COUNT 10

using namespace std;


class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow() = default;

private:
	Gtk::Paned m_paned;
	Gtk::ScrolledWindow m_scroll_edit, m_scroll_boat;
	Gtk::Box m_box_left_side, m_box_action_button, m_box_edit;
	BoatList m_boat_list;
	Gtk::Button m_button_reset, m_button_save, m_button_new, m_button_delete;

	// Currently loaded boat pointer
	Boat* m_current_boat = nullptr;

	// Save handler
	void on_save_clicked();

	// New boat handler
	void on_new_clicked();


	void loadBoat(Boat *b);
	void update();
	void reset();

	void boat_callback(Gtk::ListBoxRow *boat_row); // TODO


	CompassSection m_compass_section;
	GeneralSection m_general_section;
	PropertieSection m_propertie_section;
	RadarScreenSection m_radar_screen_section;
	RudderSection m_rudder_section;
	WeatherSection m_weather_section;
	WheelSection m_wheel_section;
	// Newly integrated sections
	SailsSection m_sails_section;
	PanoSection m_pano_section;
	ViewsSection m_views_section;

	SectionSuperClass *section_list[WINDOWS_SECTION_COUNT] = {
		&m_compass_section, &m_general_section, &m_propertie_section,
		&m_radar_screen_section, &m_rudder_section, &m_weather_section,
		&m_wheel_section, &m_sails_section, &m_pano_section, &m_views_section
	};
};

#endif