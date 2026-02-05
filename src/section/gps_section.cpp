#include "gps_section.h"

GpsSection::GpsSection():
  mGrid()
{
  mLabelSection.set_markup("<b>GPS</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
  
  // Show every field
  mGps.getBox().show();

  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mGps.getBox(), 0, 1);  
  

  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void GpsSection::set()
{
  mGps.set(&mBoat->hasGPS);
}

void GpsSection::init()
{
  mGps.init("GPS", &mBoat->hasGPS);
}


void GpsSection::update(void)
{
  for(unsigned char i=0;i<GPS_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void GpsSection::refresh(void)
{
  for(unsigned char i=0;i<GPS_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
