#include "propeller_section.h"

PropellerSection::PropellerSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Propeller</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
  
  // Show every field
  mNumber.getBox().show();
  mDiameter.getBox().show();
  mForwardRotDir.getBox().show();
  mBackwardEff.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mNumber.getBox(), 0, 1);
  mGrid.attach(mDiameter.getBox(), 0, 2);
  mGrid.attach(mForwardRotDir.getBox(), 0, 3);
  mGrid.attach(mBackwardEff.getBox(), 1, 3);

  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void PropellerSection::set()
{
  mNumber.set(&mBoat->prop.number);
  mDiameter.set(&mBoat->prop.diameter);
  mForwardRotDir.set(&mBoat->prop.forwardRotDir);
  mBackwardEff.set(&mBoat->prop.backwardEff);
}

void PropellerSection::init()
{
  mNumber.init("Propeller number", &mBoat->prop.number);
  mDiameter.init("Diameter", &mBoat->prop.diameter);
  mForwardRotDir.init("Forward rotation direction", &mBoat->prop.forwardRotDir);
  mBackwardEff.init("Backward efficiency", &mBoat->prop.backwardEff);
}


void PropellerSection::update(void)
{
  for(unsigned char i=0;i<PROPELLER_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void PropellerSection::refresh(void)
{
  for(unsigned char i=0;i<PROPELLER_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
