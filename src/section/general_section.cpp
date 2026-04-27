#include "general_section.h"

GeneralSection::GeneralSection():
  mGrid()
{
  mLabelSection.set_markup("<b>General</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
    
  // Show every field
  mBoatName.getBox().show();
  mImgName.getBox().show();
  mType.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mBoatName.getBox(), 0, 1);
  mGrid.attach(mImgName.getBox(), 1, 1);
  mGrid.attach(mType.getBox(), 0, 2);
  
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void GeneralSection::set()
{
  mBoatName.set(&mBoat->displayName);
  mImgName.set(&mBoat->imgName);
  mType.set(&mBoat->type);
}

void GeneralSection::init()
{
  mBoatName.init("Boat name", &mBoat->displayName);
  mImgName.init("Image name", &mBoat->imgName);
  mType.init("Type of Ship (Ferry or Container), Ferry by default", &mBoat->type);
}


void GeneralSection::update(void)
{
  for(unsigned char i=0;i<GENERAL_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void GeneralSection::refresh(void)
{
  for(unsigned char i=0;i<GENERAL_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
