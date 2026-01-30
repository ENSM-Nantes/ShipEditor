#include <iostream>
#include "main_window.h"

MainWindow::~MainWindow()
{
  
}

MainWindow::MainWindow():
  // Main window
  mPanes(Gtk::Orientation::HORIZONTAL),
  mScrollEdit(),
  mScrollBoat(),
  mLeftSideBox(Gtk::Orientation::VERTICAL),
  mButtonsBox(Gtk::Orientation::HORIZONTAL),
  mConfBoatBox(Gtk::Orientation::VERTICAL),

  // Boat area
  mBoatList(),
  mRefreshButton("Refresh"),
  mSaveButton("Save"),
  mNewButton("New"),
  mDeleteButton("Delete"),

  // Edit area
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
  mPanes.set_position(500);
	
  // Configure the scrooled window
  mScrollBoat.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
  mScrollBoat.set_expand();
  mScrollEdit.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
  mScrollEdit.set_expand();

	
  /* ********************* */
  /* ***** Edit Area ***** */
  /* ********************* */
  // Show every section  
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
	
  // Pack all elements in the box:
  mConfBoatBox.append(mBoatName);
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


  // Make the box visible and usable with the scroll bar
  mConfBoatBox.show();
  mScrollEdit.set_child(mConfBoatBox);


  /* ********************* */
  /* ***** Boat Area ***** */
  /* ********************* */

  // Link the signals to function
  mBoatList.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::BoatLineCbk));
  mSaveButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::Update));
  mRefreshButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::Refresh));

  // Put an icon in the buttons
  // TODO

  // Show the buttons
  mNewButton.show();
  mDeleteButton.show();
  mSaveButton.show();
  mRefreshButton.show();

  // Pack the button in the box
  mButtonsBox.append(mNewButton);
  mButtonsBox.append(mDeleteButton);
  mButtonsBox.append(mSaveButton);
  mButtonsBox.append(mRefreshButton);

  // Make the list usable with the scroll bar
  mScrollBoat.set_child(mBoatList);

  // Pack the list and the buttons in the box
  mLeftSideBox.append(mScrollBoat);
  mLeftSideBox.append(mButtonsBox);

  mButtonsBox.show();
  mLeftSideBox.show();

  // Configure the paned
  mPanes.set_margin(10);
  mPanes.set_start_child(mLeftSideBox);
  mPanes.set_end_child(mScrollEdit);

  //Show first boat
  BoatLineCbk((BoatRow*)mBoatList.get_row_at_index(0));
  
  // Add the box in this window:
  set_child(mPanes);	
}


void MainWindow::BoatLineCbk(Gtk::ListBoxRow *aBoatRow)
{
  static bool bInit = false;
  Boat *pBoat = &(((BoatRow*)aBoatRow)->mBoat);
  std::string name = pBoat->displayName;

  mBoatName.set_markup("<b>" + Glib::Markup::escape_text(name) + "</b>");

  mCurrentRowIndex = ((BoatRow*)aBoatRow)->get_index();
  LoadBoat(pBoat);

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

void MainWindow::Update()
{
  Gtk::ListBoxRow *currentBoatRow;
  
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
  BoatManager::SaveBoat(((BoatRow*)currentBoatRow)->mBoat);
}

void MainWindow::Refresh()
{
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
