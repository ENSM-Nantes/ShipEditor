#include "rudder_section.h"

RudderSection::RudderSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Rudder</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
  
  // Show every field
  mNumber.getBox().show();
  mSpacing.getBox().show();
  mSpanLenght.getBox().show();
  mAreaMobile.getBox().show();
  mAspectRatio.getBox().show();
  mMaxSpeed.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mNumber.getBox(), 0, 1);
  mGrid.attach(mSpacing.getBox(), 1, 1);
  mGrid.attach(mSpanLenght.getBox(), 0, 2);
  mGrid.attach(mAreaMobile.getBox(), 1, 2);
  mGrid.attach(mAspectRatio.getBox(), 2, 2);
  mGrid.attach(mMaxSpeed.getBox(), 0, 3);
  mGrid.attach(mMaxDelta.getBox(), 1, 3);
  
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void RudderSection::set()
{
  mNumber.set(&mBoat->rudder.number);
  mSpacing.set(&mBoat->rudder.spacing);
  mSpanLenght.set(&mBoat->rudder.hR);
  mAreaMobile.set(&mBoat->rudder.aR);
  mAspectRatio.set(&mBoat->rudder.lambdaR);
  mMaxSpeed.set(&mBoat->rudder.rrMax);
  mMaxDelta.set(&mBoat->rudder.deltaMax);
}

void RudderSection::init()
{
  mNumber.init("Rudder number", &mBoat->rudder.number);
  mSpacing.init("Rudder spacing (if 2 rudders, not used if not)", &mBoat->rudder.spacing);    
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
