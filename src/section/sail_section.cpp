#include "sail_section.h"
#include <filesystem>
#include <iostream>
#include <algorithm>

namespace fs = std::filesystem;

SailSection::SailSection():
  mGrid(),
  mSailLinesAttachedCounter(0),
  mPolarBox(Orientation::HORIZONTAL),
  mBrowsePolarButton("Browse...")
{
  mLabelSection.set_markup("<b>Sail</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);

  // Show every field
  mNumber.getBox().show();
  mType.getBox().show();
  mSize.getBox().show();

  mPolarLabel.set_text("Polar file");
  mPolarLabel.show();

  mBrowsePolarButton.set_margin_start(5);
  mBrowsePolarButton.set_hexpand(false);
  mBrowsePolarButton.set_halign(Align::START);
  mBrowsePolarButton.add_css_class("gray-entry");
  mBrowsePolarButton.show();

  mPolarStatusLabel.set_halign(Align::START);
  mPolarStatusLabel.set_margin_start(10);
  mPolarStatusLabel.show();

  mPolarStatusIcon.set_pixel_size(16);
  mPolarStatusIcon.set_margin_start(4);
  mPolarStatusIcon.show();

  mPolarBox.set_margin_top(2);
  mPolarBox.set_margin_bottom(2);
  mPolarBox.set_margin_start(2);
  mPolarBox.set_margin_end(2);
  mPolarBox.append(mPolarLabel);
  mPolarBox.append(mBrowsePolarButton);
  mPolarBox.append(mPolarStatusLabel);
  mPolarBox.append(mPolarStatusIcon);
  mPolarBox.show();

  mBrowsePolarButton.signal_clicked().connect(sigc::mem_fun(*this, &SailSection::OnBrowsePolarClicked));

  // Fill the grid
  mGrid.attach(mBox, 0, 0);
  mGrid.attach(mNumber.getBox(), 0, 1);
  mGrid.attach(mType.getBox(), 1, 1);
  mGrid.attach(mSize.getBox(), 2, 1);
  mGrid.attach(mPolarBox, 0, 2);

  // mGrid.set_column_homogeneous(true);
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

SailSection::~SailSection()
{
  for(unsigned char i=0; i<mPos.size(); i++)
    {
      delete mPos[i];
    }
}

void SailSection::set()
{
  mNumber.set(&mBoat->sails.number);
  mType.set(&mBoat->sails.type);
  mSize.set(&mBoat->sails.size);

  int nbrSails = std::clamp(mBoat->sails.number, 0, MAX_SAILS);

  // Lazily create InputAreas for any sail line not yet allocated (not attached to the grid yet).
  while((int)mPos.size() < nbrSails)
    {
      int idx = (int)mPos.size();
      mPos.push_back(new InputArea());
      mPos[idx]->init("Sail n° "+ std::to_string(idx+1), mBoat->sails.sail[idx].pos, 3);
      mPos[idx]->getBox().hide();
    }

  for(int i=0; i<nbrSails; i++)
    {
      mPos[i]->set(mBoat->sails.sail[i].pos, true);
    }
}

void SailSection::init()
{
  mNumber.init("Sail number", &mBoat->sails.number);
  mType.init("Type ", &mBoat->sails.type);
  mSize.init("Size ", &mBoat->sails.size);

  int nbrSails = std::clamp(mBoat->sails.number, 0, MAX_SAILS);

  for(int i=0; i<nbrSails; i++)
    {
      mPos.push_back(new InputArea());

      mPos[i]->init("Sail n° "+ std::to_string(i+1), mBoat->sails.sail[i].pos, 3);

      mPos[i]->getBox().show();
      mGrid.attach(mPos[i]->getBox(), 0, 3+i);
      mSailLinesAttachedCounter++;
    }

  mBrowsePolarButton.set_visible(nbrSails > 0);
}


void SailSection::update(void)
{
  for(unsigned char i=0;i<SAIL_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }

  for(unsigned char i=0;i<mPos.size();i++)
    {
      mPos[i]->update();
    }
}

void SailSection::refresh(void)
{
  for(unsigned char i=0;i<SAIL_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }

  int nbrSails = std::clamp(mBoat->sails.number, 0, MAX_SAILS);

  for(int i=0; i<nbrSails; i++)
    {
      mPos[i]->refresh();
    }

  if(mSailLinesAttachedCounter > nbrSails)
    {
      int toRemove = mSailLinesAttachedCounter - nbrSails;
      for(int j=0; j<toRemove; j++)
	{
	  int idx = mSailLinesAttachedCounter - 1 - j;
	  mGrid.remove(mPos[idx]->getBox());
	}
      mSailLinesAttachedCounter -= toRemove;
    }

  if(mSailLinesAttachedCounter < nbrSails)
    {
      int toAttach = nbrSails - mSailLinesAttachedCounter;
      for(int j=0; j<toAttach; j++)
	{
	  int idx = mSailLinesAttachedCounter + j;
	  mPos[idx]->getBox().show();
	  mGrid.attach(mPos[idx]->getBox(), 0, 3+idx);
	}
      mSailLinesAttachedCounter += toAttach;
    }

  mBrowsePolarButton.set_visible(nbrSails > 0);

  UpdatePolarStatusLabel();
}

std::string SailSection::GetPolarFilePath(void)
{
  return mBoat->imgPath + "/nc/polar.nc";
}

void SailSection::UpdatePolarStatusLabel(void)
{
  if (fs::exists(GetPolarFilePath()))
    {
      mPolarStatusLabel.set_text("  Polar file set   ");
      mPolarStatusIcon.set("check.png");
    }
  else
    {
      mPolarStatusLabel.set_text("  No polar file set   ");
      mPolarStatusIcon.set("cross.png");
    }
}

void SailSection::OnBrowsePolarClicked(void)
{
  mFileDialog = FileDialog::create();
  mFileDialog->set_title("Select a polar file (.nc)");

  auto filter = FileFilter::create();
  filter->set_name("NetCDF polar files (*.nc)");
  filter->add_pattern("*.nc");

  auto filters = Gio::ListStore<FileFilter>::create();
  filters->append(filter);
  mFileDialog->set_filters(filters);
  mFileDialog->set_default_filter(filter);

  mFileDialog->open(sigc::mem_fun(*this, &SailSection::OnPolarFileChosen));
}

void SailSection::OnPolarFileChosen(Glib::RefPtr<Gio::AsyncResult>& aResult)
{
  try
    {
      auto file = mFileDialog->open_finish(aResult);
      if (!file) return;

      std::string sourcePath = file->get_path();
      if (sourcePath.empty()) return;

      fs::path destDir = fs::path(mBoat->imgPath) / "nc";
      fs::create_directories(destDir);

      fs::path destFile = destDir / "polar.nc";

      std::error_code ec;
      fs::copy_file(sourcePath, destFile, fs::copy_options::overwrite_existing, ec);

      if (ec)
	{
	  std::cerr << "Failed to copy polar file: " << ec.message() << std::endl;
	}

      UpdatePolarStatusLabel();
    }
  catch (const Glib::Error&)
    {

    }
}
