#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <gtkmm.h>
#include "BoatRow.hpp"
#include "section/mesh_section.h"
#include "section/gps_section.h"
#include "section/depth_section.h"
#include "section/rot_section.h"
#include "section/radar_section.h"
#include "section/rudder_section.h"
#include "section/physical_section.h"
#include "section/propeller_section.h"
#include "section/engine_section.h"
#include "section/sail_section.h"

#define WINDOWS_SECTION_COUNT 9

class MainWindow : public Gtk::Window {
public:

  MainWindow();
  ~MainWindow();
	
private:

  void LoadBoat(Boat *aBoat);
  void Update();
  void Refresh();
  void Set();
  void Init();
  void BoatLineCbk(Gtk::ListBoxRow *aBoatRow);

  Gtk::Label mBoatName;
  Gtk::Paned mPanes;
  Gtk::ScrolledWindow mScrollEdit;
  Gtk::ScrolledWindow mScrollBoat;
  Gtk::Box mLeftSideBox;
  Gtk::Box mButtonsBox;
  Gtk::Box mConfBoatBox;
  BoatList mBoatList;
  Gtk::Button mRefreshButton;
  Gtk::Button mSaveButton;
  Gtk::Button mNewButton;
  Gtk::Button mDeleteButton;

  int mCurrentRowIndex;
  
  MeshSection mMeshSection;
  PhysicalSection mPhysicalSection;
  GpsSection mGpsSection;
  RotSection mRotSection;
  DepthSection mDepthSection;
  RadarSection mRadarSection;
  RudderSection mRudderSection;
  PropellerSection mPropellerSection;
  EngineSection mEngineSection;
  SailSection mSailSection;
  
  
};

#endif
