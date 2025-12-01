#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

// Import for functional purpose
#include "input_area.h"
#include "section/section.h"

// Sections import
#include "section/compass_section.h"
#include "section/general_section.h"
#include "section/propertie_section.h"
#include "section/radar_screen_section.h"
#include "section/rudder_section.h"
#include "section/weather_section.h"
#include "section/wheel_section.h"


#define WINDOWS_SECTION_COUNT 7


class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow() = default;
    
    void loadBoat(Boat *b);   /** @brief Charge un Boat dans toutes les sections */
    void update();            /** @brief Applique les modifications de l’UI vers Boat */
    void reset();             /** @brief Réinitialise l’UI depuis Boat */

private:
	Gtk::ScrolledWindow m_scroll_edit;
	Gtk::Box m_box;

	void loadBoat(Boat *b);
	void update();
	void reset();


	CompassSection m_compass_section;
	GeneralSection m_general_section;
	PropertieSection m_propertie_section;
	RadarScreenSection m_radar_screen_section;
	RudderSection m_rudder_section;
	WeatherSection m_weather_section;
	WheelSection m_wheel_section;

	SectionSuperClass *section_list[WINDOWS_SECTION_COUNT] = {
		//&m_compass_section, &m_general_section, &m_propertie_section,
		//&m_radar_screen_section, &m_rudder_section, &m_weather_section, &m_wheel_section
	};
};

#endif