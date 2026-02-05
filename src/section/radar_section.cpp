#include "radar_section.h"

RadarSection::RadarSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Radar</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
  
  // Show every field
  
  mRadar.getBox().show();
  mTilt.getBox().show();
  mPos.getBox().show();
  mSize.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);
  mGrid.attach(mRadar.getBox(), 0, 1);
  mGrid.attach(mTilt.getBox(), 0, 3);
  mGrid.attach(mSize.getBox(), 0, 4);
  mGrid.attach(mPos.getBox(), 0, 2);
  
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

RadarSection::~RadarSection()
{
  
}

void RadarSection::set()
{
  mRadar.set(&mBoat->hasRadar);
  mTilt.set(&mBoat->radarScreen.tilt);
  mSize.set(&mBoat->radarScreen.size);
  mPos.set(mBoat->radarScreen.vector, true);
}

void RadarSection::init()
{
  mRadar.init("Radar", &mBoat->hasRadar);
  mTilt.init("Tilt", &mBoat->radarScreen.tilt);
  mSize.init("Size", &mBoat->radarScreen.size);
  mPos.init("Position", mBoat->radarScreen.vector, 3); 
}


void RadarSection::update(void)
{
  for(unsigned char i=0;i<RADAR_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void RadarSection::refresh(void)
{
  for(unsigned char i=0;i<RADAR_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }       
}
