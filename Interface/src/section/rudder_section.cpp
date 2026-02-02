#include "rudder_section.h"

RudderSection::RudderSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Rudder</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  
  // Show every field
  mSpanLenght.getBox().show();
  mAreaMobile.getBox().show();
  mAspectRatio.getBox().show();
  mMaxSpeed.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mSpanLenght.getBox(), 0, 1);
  mGrid.attach(mAreaMobile.getBox(), 1, 1);
  mGrid.attach(mAspectRatio.getBox(), 2, 1);
  mGrid.attach(mMaxSpeed.getBox(), 0, 2);
  mGrid.attach(mMaxDelta.getBox(), 1, 2);
  
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void RudderSection::set()
{
  mSpanLenght.set(&mBoat->rudder.hR);
  mAreaMobile.set(&mBoat->rudder.aR);
  mAspectRatio.set(&mBoat->rudder.lambdaR);
  mMaxSpeed.set(&mBoat->rudder.rrMax);
  mMaxDelta.set(&mBoat->rudder.deltaMax);
}

void RudderSection::init()
{
  mSpanLenght.init("Span Lenght", &mBoat->rudder.hR);
  mAreaMobile.init("Area mobile part", &mBoat->rudder.aR);
  mAspectRatio.init("Aspect ratio", &mBoat->rudder.lambdaR);
  mMaxSpeed.init("Maximum speed", &mBoat->rudder.rrMax);
  mMaxDelta.init("Maximum angle", &mBoat->rudder.deltaMax);
}


void RudderSection::update(void)
{
  for(unsigned char i=0;i<RUDDER_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void RudderSection::refresh(void)
{
  for(unsigned char i=0;i<RUDDER_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
