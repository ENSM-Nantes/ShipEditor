#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <gtkmm.h>
#include <gdk/gdkkeysyms.h>
#include "BoatRow.hpp"
#include "BoatManager.hpp"
#include "section/general_section.h"
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
#include "section/hull_section.h"
#include "section/light_section.h"

#define WINDOWS_SECTION_COUNT 12

class MainWindow : public Gtk::Window {
public:

  MainWindow();
  ~MainWindow();
	
  void InitList(void);
  void RemoveList(void);
  void LoadBoat(Boat *aBoat);
  void Update();
  void Refresh();
  void Set();
  void Init();
  void BoatLineCbk(Gtk::ListBoxRow *aBoatRow);
  void RefreshCbk(void);
  void New(void);
  void Delete(void);
  void InfoBubble(const std::string &aMessage, const std::string &aDetail);
  bool OnKeyPressed(guint keyval, guint keycode, Gdk::ModifierType state);

private:

  Gtk::Label mSoftName;
  Gtk::Label mBoatName;
  Gtk::Label mVersionNumber;
  Gtk::Image mBoatImg;
  Gtk::Picture mLogo;
  Gtk::Paned mPanes;
  Gtk::ScrolledWindow mScrollEdit;
  Gtk::ScrolledWindow mScrollBoat;
  Gtk::Box mTitleBox;
  Gtk::Box mLeftSideBox;
  Gtk::Box mRightSideBox;
  Gtk::Box mButtonsBox;
  Gtk::Box mFooterBox;
  Gtk::Box mHeaderBox;
  Gtk::Box mConfBoatBox;
  Gtk::Box mMainBox;
  Gtk::ListBox mBoatList;
  Gtk::Button mRefreshButton;
  Gtk::Button mSaveButton;
  Gtk::Button mNewButton;
  Gtk::Button mDeleteButton;

  std::string mName;
  int mCurrentRowIndex;

  GeneralSection mGeneralSection;
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
  HullSection mHullSection;
  LightSection mLightSection;
  
  Glib::RefPtr<Gtk::AlertDialog> mDialog;
  Glib::RefPtr<Gtk::EventControllerKey> mKeyController;

  std::vector<Boat> mBoats;
  std::vector<BoatRow*> mBoatRows;
  
};

#endif
