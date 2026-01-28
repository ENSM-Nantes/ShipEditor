#include <iostream>
#include "main_window.h"

MainWindow::~MainWindow()
{
  
}

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
  m_button_refresh("Refresh"),
  m_button_save("Save"),
  m_button_new("New"),
  m_button_delete("Delete"),

  // Edit area
  m_azimuth_section(),
  m_compass_section(),
  m_dynamics_section(),
  mMeshSection(),
  mGpsSection(),
  mDepthSection(),
  m_propertie_section(),
  m_propulsion_section(),
  mRadarSection(),
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
  mMeshSection.show();
  mGpsSection.show();
  mDepthSection.show();
  mRadarSection.show();
  m_propertie_section.show();
  m_propulsion_section.show();
  m_rudder_section.show();
  m_weather_section.show();
  m_wheel_section.show();
	
  // Pack all elements in the box:
  m_box_edit.append(m_label_edit);
  m_box_edit.append(mMeshSection);
  m_box_edit.append(mGpsSection);
  m_box_edit.append(mDepthSection);
  m_box_edit.append(mRadarSection);
  m_box_edit.append(m_compass_section);
  m_box_edit.append(m_propertie_section);
  m_box_edit.append(m_propulsion_section);
  m_box_edit.append(m_dynamics_section);
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
  m_boat_list.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::boat_line));
  m_button_save.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::update));
  m_button_refresh.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::refresh));

  // Put an icon in the buttons
  // TODO

  // Show the buttons
  m_button_new.show();
  m_button_delete.show();
  m_button_save.show();
  m_button_refresh.show();

  // Pack the button in the box
  m_box_action_button.append(m_button_new);
  m_box_action_button.append(m_button_delete);
  m_box_action_button.append(m_button_save);
  m_box_action_button.append(m_button_refresh);

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
  boat_line((BoatRow*)m_boat_list.get_row_at_index(0));
  
  // Add the box in this window:
  set_child(m_paned);	
}


void MainWindow::boat_line(Gtk::ListBoxRow *boat_row)
{
  static bool bInit = false;
  Boat *pBoat = &(((BoatRow*)boat_row)->boat);
  std::string name = pBoat->displayName;

  m_label_edit.set_markup("<b>" + Glib::Markup::escape_text(name) + "</b>");

  mCurrentRowIndex = ((BoatRow*)boat_row)->get_index();
  loadBoat(pBoat);

  if(!bInit)
    {
      init();
      bInit = true;
    }
  else
    set();
  
  refresh();
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
  mMeshSection.load(b);
  mGpsSection.load(b);
  mDepthSection.load(b);
  m_propertie_section.load(b);
  m_propulsion_section.load(b);
  mRadarSection.load(b);
  m_rudder_section.load(b);
  m_weather_section.load(b);
  m_wheel_section.load(b);
}

void MainWindow::set(void)
{
  m_azimuth_section.set();
  m_compass_section.set();
  m_dynamics_section.set();
  mMeshSection.set();
  mGpsSection.set();
  mDepthSection.set();
  m_propertie_section.set();
  m_propulsion_section.set();
  mRadarSection.set();
  m_rudder_section.set();
  m_weather_section.set();
  m_wheel_section.set();
}

void MainWindow::init(void)
{
  m_azimuth_section.init();
  m_compass_section.init();
  m_dynamics_section.init();
  mMeshSection.init();
  mGpsSection.init();
  mDepthSection.init();
  m_propertie_section.init();
  m_propulsion_section.init();
  mRadarSection.init();
  m_rudder_section.init();
  m_weather_section.init();
  m_wheel_section.init();
}

void MainWindow::update()
{
  BoatManager manager;
  Gtk::ListBoxRow *currentBoatRow;
  
  m_azimuth_section.update();
  m_compass_section.update();
  m_dynamics_section.update();
  mMeshSection.update();
  mGpsSection.update();
  mDepthSection.update();
  m_propertie_section.update();
  m_propulsion_section.update();
  mRadarSection.update();
  m_rudder_section.update();
  m_weather_section.update();
  m_wheel_section.update();
  
  currentBoatRow = m_boat_list.get_row_at_index(mCurrentRowIndex);
  manager.saveBoat(((BoatRow*)currentBoatRow)->boat);
}

void MainWindow::refresh()
{
  m_azimuth_section.refresh();
  m_compass_section.refresh();
  m_dynamics_section.refresh();
  mMeshSection.refresh();
  mGpsSection.refresh();
  mDepthSection.refresh();
  m_propertie_section.refresh();
  m_propulsion_section.refresh();
  mRadarSection.refresh();
  m_rudder_section.refresh();
  m_weather_section.refresh();
  m_wheel_section.refresh();
}
