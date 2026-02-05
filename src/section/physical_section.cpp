#include "physical_section.h"
 
PhysicalSection::PhysicalSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Physical Characteristics</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
  
  // Show every field
  mRho.getBox().show();
  mLength.getBox().show();
  mBreadth.getBox().show();
  mDraught.getBox().show();
  mCoeffBlock.getBox().show();
  mSubWaterVolume.getBox().show();
  mGravityCenter.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mRho.getBox(), 0, 1);

  mGrid.attach(mLength.getBox(), 0, 2);
  mGrid.attach(mBreadth.getBox(), 1, 2);
  mGrid.attach(mDraught.getBox(), 2, 2);

  mGrid.attach(mCoeffBlock.getBox(), 0, 3);
  mGrid.attach(mSubWaterVolume.getBox(), 1, 3);
  mGrid.attach(mGravityCenter.getBox(), 2, 3);


  mGrid.set_column_homogeneous(true);
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

PhysicalSection::~PhysicalSection()
{

}

void PhysicalSection::set()
{
  mRho.set(&mBoat->rho);
  mLength.set(&mBoat->physicalCharac.lPP);
  mBreadth.set(&mBoat->physicalCharac.b);
  mDraught.set(&mBoat->physicalCharac.d);
  mCoeffBlock.set(&mBoat->physicalCharac.cB);
  mSubWaterVolume.set(&mBoat->physicalCharac.volume);
  mGravityCenter.set(&mBoat->physicalCharac.xG);
}

void PhysicalSection::init()
{
  mRho.init("Rho", &mBoat->rho);
  mLength.init("Length", &mBoat->physicalCharac.lPP);
  mBreadth.init("Breadth", &mBoat->physicalCharac.b);
  mDraught.init("Draught", &mBoat->physicalCharac.d);
  mCoeffBlock.init("Coefficient block", &mBoat->physicalCharac.cB);
  mSubWaterVolume.init("Sub water volume", &mBoat->physicalCharac.volume);
  mGravityCenter.init("Longitudinal gravity center", &mBoat->physicalCharac.xG);
}


void PhysicalSection::update(void)
{
  for(unsigned char i=0;i<PHYSICAL_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void PhysicalSection::refresh(void)
{
  for(unsigned char i=0;i<PHYSICAL_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }  
}
