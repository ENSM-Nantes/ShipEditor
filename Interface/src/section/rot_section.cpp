#include "rot_section.h"

RotSection::RotSection():
  mGrid()
{
  mLabelSection.set_markup("<b>RoT</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  
  // Show every field
  mRot.getBox().show();

  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mRot.getBox(), 0, 1);  
  

  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void RotSection::set()
{
  mRot.set(&mBoat->hasRateOfTurnIndicator);
}

void RotSection::init()
{
  mRot.init("RoT", &mBoat->hasRateOfTurnIndicator);
}


void RotSection::update(void)
{
  for(unsigned char i=0;i<ROT_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void RotSection::refresh(void)
{
  for(unsigned char i=0;i<ROT_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
