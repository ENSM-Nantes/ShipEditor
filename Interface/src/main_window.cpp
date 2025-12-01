#include <iostream>
#include "main_window.h"

MainWindow::MainWindow():
m_scroll_edit(),
m_box(Gtk::Orientation::VERTICAL),
m_compass_section(),
m_general_section(),
m_propertie_section(),
m_radar_screen_section(),
m_rudder_section(),
m_weather_section(),
m_wheel_section()
{
	// Configure this window:
	this->set_default_size(600, 400);

	// Configure the scrooled window
	m_scroll_edit.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
	m_scroll_edit.set_expand();
	
	// Show every section
	m_compass_section.show();
	m_general_section.show();
	m_propertie_section.show();
	m_radar_screen_section.show();
	m_rudder_section.show();
	//m_weather_section.show();
	//m_wheel_section.show();
	
	
	// Pack all elements in the box:
	m_box.append(m_compass_section);
	m_box.append(m_general_section);
	m_box.append(m_propertie_section);
	m_box.append(m_radar_screen_section);
	m_box.append(m_rudder_section);
	m_box.append(m_weather_section);
	m_box.append(m_wheel_section);

	// Make the box visible:
	m_box.show();

	// Add the box to the scrolled window
	m_scroll_edit.set_child(m_box);

	// Add the box in this window:
	set_child(m_scroll_edit);
	
}


void MainWindow::loadBoat(Boat *b) {
    if (!b) return;
    for (int i = 0; i < WINDOWS_SECTION_COUNT; i++) {
        section_list[i]->loadBoat(b);
    }
}

void MainWindow::update() {
    for (int i = 0; i < WINDOWS_SECTION_COUNT; i++) {
        section_list[i]->update();
    }
}

void MainWindow::reset() {
    for (int i = 0; i < WINDOWS_SECTION_COUNT; i++) {
        section_list[i]->reset();
    }
}