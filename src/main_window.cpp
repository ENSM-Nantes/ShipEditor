#include <iostream>
#include <filesystem>
#include <fstream>
#include "main_window.h"
#include "BoatManager.hpp"

namespace fs = std::filesystem;

MainWindow::~MainWindow()
{
  RemoveList();  
}

MainWindow::MainWindow():
  // Main window
  mPanes(Gtk::Orientation::HORIZONTAL),
  mScrollEdit(),
  mScrollBoat(),
  mTitleBox(Gtk::Orientation::HORIZONTAL),
  mLeftSideBox(Gtk::Orientation::VERTICAL),
  mRightSideBox(Gtk::Orientation::VERTICAL),
  mButtonsBox(Gtk::Orientation::HORIZONTAL),
  mFooterBox(Gtk::Orientation::HORIZONTAL),
  mHeaderBox(Gtk::Orientation::HORIZONTAL),
  mConfBoatBox(Gtk::Orientation::VERTICAL),
  mMainBox(Gtk::Orientation::VERTICAL),

  // Boat area
  mBoatList(),
  mRefreshButton("Refresh"),
  mSaveButton("Save"),
  mNewButton("New"),
  mDeleteButton("Delete"),

  // Edit area
  mGeneralSection(),
  mMeshSection(),
  mPhysicalSection(),
  mGpsSection(),
  mRotSection(),
  mDepthSection(),
  mRadarSection(),
  mRudderSection(),
  mPropellerSection(),
  mEngineSection(),
  mSailSection()
{
  // Configure this window:
  set_default_size(1920, 1024);
  mPanes.set_position(360);
	
  // Configure the scrooled window
  mScrollBoat.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
  mScrollBoat.set_expand();
  mScrollEdit.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
  mScrollEdit.set_expand();
	
  // Show every section
  mGeneralSection.show();
  mMeshSection.show();
  mPhysicalSection.show();
  mGpsSection.show();
  mRotSection.show();
  mDepthSection.show();
  mRadarSection.show();
  mRudderSection.show();
  mPropellerSection.show();
  mEngineSection.show();
  mSailSection.show();

  //Header
  mHeaderBox.set_margin_top(15);
  mLogo.set_filename("../res/logo.png");
  mSoftName.set_text("\t\t\t\t\tShip Editor");
  mHeaderBox.add_css_class("header-label");
  mHeaderBox.append(mLogo);
  mHeaderBox.append(mSoftName);
    
  //Footer
  mFooterBox.set_margin_top(15);
  mFooterBox.set_margin_start(1150);
  mVersionNumber.set_text("Ship-Editor v2.1 - SOMOS Project 2026 - ENSM Nantes");
  mFooterBox.append(mVersionNumber);
  mFooterBox.add_css_class("text-label");
  
  //Title
  mBoatImg.set_pixel_size(256);
  mTitleBox.append(mBoatName);
  mTitleBox.append(mBoatImg);
  mTitleBox.add_css_class("title-label");

  Gtk::Separator sep1(Gtk::Orientation::HORIZONTAL);
  mConfBoatBox.append(sep1);
  mConfBoatBox.append(mTitleBox);
  mConfBoatBox.append(mGeneralSection);
  mConfBoatBox.append(mMeshSection);
  mConfBoatBox.append(mPhysicalSection);
  mConfBoatBox.append(mRudderSection);
  mConfBoatBox.append(mPropellerSection);
  mConfBoatBox.append(mEngineSection);
  mConfBoatBox.append(mSailSection);
  mConfBoatBox.append(mGpsSection);
  mConfBoatBox.append(mDepthSection);
  mConfBoatBox.append(mRadarSection);
  mConfBoatBox.append(mRotSection);
  mConfBoatBox.add_css_class("text-label");
  
  // Make the box visible and usable with the scroll bar
  mConfBoatBox.show();
  mScrollEdit.set_child(mConfBoatBox);

  //List
  InitList();
  
  // Link the signals to function
  mBoatList.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::BoatLineCbk));
  mSaveButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::Update));
  mRefreshButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::RefreshCbk));
  mNewButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::New));
  mDeleteButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::Delete));

  // Put an icon in the buttons
  // TODO

  // Show the buttons
  mNewButton.show();
  mDeleteButton.show();
  mSaveButton.show();
  mRefreshButton.show();

  // Pack the button in the box
  mButtonsBox.set_margin_top(15);
  mButtonsBox.append(mNewButton);
  mButtonsBox.append(mDeleteButton);
  mButtonsBox.append(mSaveButton);
  mButtonsBox.append(mRefreshButton);
  mButtonsBox.set_homogeneous();
  
  // Make the list usable with the scroll bar
  mScrollBoat.show();
  mScrollBoat.set_child(mBoatList);
  mBoatList.add_css_class("backg");
  mBoatList.add_css_class("text-label");
  
  // Pack the list and the buttons in the box
  mLeftSideBox.append(mScrollBoat);
  mLeftSideBox.append(mButtonsBox);
  
  mRightSideBox.set_margin_start(10);
  mRightSideBox.append(mScrollEdit);
  mRightSideBox.append(mFooterBox);
  
  // Configure the paned
  mPanes.set_margin(10);
  mPanes.set_start_child(mLeftSideBox);
  mPanes.set_end_child(mRightSideBox);
  mPanes.add_css_class("no-handle");
  
  mMainBox.append(mHeaderBox);

  mMainBox.append(mPanes);
  mMainBox.add_css_class("backg");
  
  //Show first boat
  BoatLineCbk((BoatRow*)mBoatList.get_row_at_index(0));
  
  // Add the box in this window:
  set_child(mMainBox);	
}


void MainWindow::BoatLineCbk(Gtk::ListBoxRow *aBoatRow)
{
  static bool bInit = false;
  Boat *pBoat = &(((BoatRow*)aBoatRow)->mBoat);
  mName = pBoat->displayName;

  
  mBoatName.set_markup("<span size='20000'><b>" + Glib::Markup::escape_text(mName) + "\t\t\t\t\n</b></span>");

  mCurrentRowIndex = ((BoatRow*)aBoatRow)->get_index();
  LoadBoat(pBoat);

  try
    {
      auto file = Gio::File::create_for_path(pBoat->imgPath + "/" + pBoat->mesh.fileName.substr(0, pBoat->mesh.fileName.size() - 3) + "jpg");
      auto texture = Gdk::Texture::create_from_file(file);
      mBoatImg.set(texture);
    }
  catch (const Glib::Error& e)
    {
      auto file = Gio::File::create_for_path("../res/default.png");
      auto texture = Gdk::Texture::create_from_file(file);
      mBoatImg.set(texture);
    }

  if(!bInit)
    {
      Init();
      bInit = true;
    }
  else
    Set();
  
  Refresh();
}


void MainWindow::LoadBoat(Boat *aBoat)
{
  if (aBoat == nullptr) return;
  mGeneralSection.load(aBoat);
  mMeshSection.load(aBoat);
  mPhysicalSection.load(aBoat);
  mGpsSection.load(aBoat);
  mDepthSection.load(aBoat);
  mRotSection.load(aBoat);
  mRadarSection.load(aBoat);
  mRudderSection.load(aBoat);
  mPropellerSection.load(aBoat);
  mEngineSection.load(aBoat);
  mSailSection.load(aBoat);
}

void MainWindow::Set(void)
{
  mGeneralSection.set();
  mMeshSection.set();
  mPhysicalSection.set();
  mGpsSection.set();
  mRotSection.set();
  mDepthSection.set();
  mRadarSection.set();
  mRudderSection.set();
  mPropellerSection.set();
  mEngineSection.set();
  mSailSection.set();
}

void MainWindow::Init(void)
{
  mGeneralSection.init();
  mMeshSection.init();
  mPhysicalSection.init();
  mGpsSection.init();
  mRotSection.init();
  mDepthSection.init();
  mRadarSection.init();
  mRudderSection.init();
  mPropellerSection.init();
  mEngineSection.init();
  mSailSection.init();
}

void MainWindow::InfoBubble(const std::string &aMessage, const std::string &aDetail)
{
  if (!mDialog)
    {
      mDialog = Gtk::AlertDialog::create();
    }
	
  // Reset values that may have been set by on_button_question_clicked().
  //m_pDialog->set_buttons({});
  mDialog->set_default_button(-1);
  mDialog->set_cancel_button(-1);

  mDialog->set_modal(); // Block the window until the dialog closes


  mDialog->set_message(aMessage);
  mDialog->set_detail(aDetail);
  mDialog->show(*this);
}


void MainWindow::Update()
{
  Gtk::ListBoxRow *currentBoatRow;

  mGeneralSection.update();
  mMeshSection.update();
  mPhysicalSection.update();
  mRudderSection.update();
  mGpsSection.update();
  mRotSection.update();
  mDepthSection.update();
  mRadarSection.update();
  mPropellerSection.update();
  mEngineSection.update();
  mSailSection.update();
    
  currentBoatRow = mBoatList.get_row_at_index(mCurrentRowIndex);

  if(BoatManager::SaveBoat(((BoatRow*)currentBoatRow)->mBoat))
    InfoBubble("Saved", "The boat has been saved successfully");
  else
    InfoBubble("Error", "Failed to save the boat");
  
  RemoveList();
  InitList();

  //Focus 
  currentBoatRow = mBoatList.get_row_at_index(mCurrentRowIndex);
  BoatLineCbk(currentBoatRow);
}

void MainWindow::Refresh()
{
  mGeneralSection.refresh();
  mMeshSection.refresh();
  mPhysicalSection.refresh();
  mRudderSection.refresh();
  mGpsSection.refresh();
  mRotSection.refresh();
  mDepthSection.refresh();
  mRadarSection.refresh();
  mPropellerSection.refresh();
  mEngineSection.refresh();
  mSailSection.refresh();
}

void MainWindow::RefreshCbk()
{
  Refresh();
  InfoBubble("Refresh", "All datas have been reloaded from JSON file");
}

void MainWindow::Delete(void)
{
  BoatManager::RemoveBoat(mName);
  RemoveList();
  InitList();

  InfoBubble("Delete", "Boat \"" + mName + "\" has been removed successfully.");
}


void MainWindow::New(void)
{
  std::string uniqueName = "NewBoat";
  int counter = 1;
	
  fs::path jsonPath(PATH_JSON_BOATS);
  
  while(fs::exists(jsonPath / uniqueName))
    {
      uniqueName = "NewBoat" + std::to_string(counter);
      counter++;
    }

  std::ifstream file("../res/boat_empty.json");  
  Json::Value root;
  file >> root;
  
  Boat newBoat;

  //General
  newBoat.displayName = uniqueName;
  
  if(BoatManager::SaveBoat(newBoat))
    {
      RemoveList();
      InitList();

      InfoBubble("New Boat Created", "A new boat \"" + uniqueName + "\" has been created and saved successfully.");
    }
  else
    {
      InfoBubble("Error", "Failed to create the new boat.");
    }
}

void MainWindow::InitList(void)
{
  mBoats = BoatManager::LoadBoats(PATH_JSON_BOATS);

  for (Boat b : mBoats)
    {
      BoatRow* row = Gtk::manage(new BoatRow(b));
      mBoatList.append(*row);
      mBoatRows.push_back(row);
    }
}

void MainWindow::RemoveList(void)
{
  for(auto row : mBoatRows)
    {
      mBoatList.remove(*row);
    }
  mBoatRows.clear();

}
