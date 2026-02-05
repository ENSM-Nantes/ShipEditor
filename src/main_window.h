#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <gtkmm.h>
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

#define WINDOWS_SECTION_COUNT 11

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

  Glib::RefPtr<Gtk::AlertDialog> mDialog;

  std::vector<Boat> mBoats;
  std::vector<BoatRow*> mBoatRows;
  
};

#endif
