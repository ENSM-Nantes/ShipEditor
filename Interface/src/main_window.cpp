#include <iostream>
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
  m_propertie_section(),
  m_propulsion_section(),
  m_radar_screen_section(),
  m_rudder_section(),
  m_weather_section(),
  m_wheel_section()
{
  // Configure this window:
  set_default_size(1920, 1024);
  m_paned.set_position(500);
	
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
  m_propertie_section.show();
  m_propulsion_section.show();
  m_radar_screen_section.show();
  m_rudder_section.show();
  m_weather_section.show();
  m_wheel_section.show();
	
  // Pack all elements in the box:
  m_box_edit.append(m_label_edit);
  m_box_edit.append(m_compass_section);
  m_box_edit.append(m_general_section);
  m_box_edit.append(m_propertie_section);
  m_box_edit.append(m_propulsion_section);
  m_box_edit.append(m_dynamics_section);
  m_box_edit.append(m_radar_screen_section);
  m_box_edit.append(m_azimuth_section);
  m_box_edit.append(m_rudder_section);
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

  //Show first boat
  boat_callback((BoatRow*)m_boat_list.get_row_at_index(0));  
  reset();
  
  // Add the box in this window:
  set_child(m_paned);	
}


void MainWindow::boat_callback(Gtk::ListBoxRow *boat_row)
{
  std::string name = ((BoatRow*)boat_row)->boat.displayName;
  m_label_edit.set_text(name);
  m_label_edit.show();

  loadBoat(&(((BoatRow*)boat_row)->boat));
  reset();
}


/**
 * Load a boat to edit its properties
 * @param b The reference of a boat
 */
void MainWindow::loadBoat(Boat *b)
{
  if (b == nullptr) return;

  m_azimuth_section.load(b);
  m_compass_section.load(b);
  m_dynamics_section.load(b);
  m_general_section.load(b);
  m_propertie_section.load(b);
  m_propulsion_section.load(b);
  m_radar_screen_section.load(b);
  m_rudder_section.load(b);
  m_weather_section.load(b);
  m_wheel_section.load(b);
}

/**
 * Update all the field of all the sections (see InputArea::update())
 */
void MainWindow::update()
{
  m_azimuth_section.update();
  m_compass_section.update();
  m_dynamics_section.update();
  m_general_section.update();
  m_propertie_section.update();
  m_propulsion_section.update();
  m_radar_screen_section.update();
  m_rudder_section.update();
  m_weather_section.update();
  m_wheel_section.update();
}

/**
 * Reset all the field of all the sections (see InputArea::reset())
 */
void MainWindow::reset()
{
  m_azimuth_section.reset();
  m_compass_section.reset();
  m_dynamics_section.reset();
  m_general_section.reset();
  m_propertie_section.reset();
  m_propulsion_section.reset();
  m_radar_screen_section.reset();
  m_rudder_section.reset();
  m_weather_section.reset();
  m_wheel_section.reset();
}
