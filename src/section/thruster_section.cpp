#include "thruster_section.h"

ThrusterSection::ThrusterSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Thruster</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
    
  // Show every field
  mBow.getBox().show();
  mStern.getBox().show();
  mBrand.getBox().show();
  mType.getBox().show();
  mPower.getBox().show();
  mRpmMax.getBox().show();
  mFuelCons.getBox().show();
  mPropellerDiameter.getBox().show();
  mForwardRotDir.getBox().show();
  mXBow.getBox().show();
  mXStern.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mBow.getBox(), 0, 1);
  mGrid.attach(mStern.getBox(), 1, 1);
  mGrid.attach(mBrand.getBox(), 0, 2);
  mGrid.attach(mType.getBox(), 1, 2);
  mGrid.attach(mPower.getBox(), 0, 3);
  mGrid.attach(mRpmMax.getBox(), 1, 3);
  mGrid.attach(mFuelCons.getBox(), 2, 3);
  mGrid.attach(mPropellerDiameter.getBox(), 3, 3);
  mGrid.attach(mForwardRotDir.getBox(), 0, 4);
  mGrid.attach(mXBow.getBox(), 0, 5);
  mGrid.attach(mXStern.getBox(), 0, 8);
  
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void ThrusterSection::set()
{
  mBow.set(&mBoat->thruster.hasBowThruster);
  mStern.set(&mBoat->thruster.hasSternThruster);
  mBrand.set(&mBoat->thruster.brand);
  mType.set(&mBoat->thruster.type);
  mPower.set(&mBoat->thruster.power);
  mRpmMax.set(&mBoat->thruster.rpmMax);
  mFuelCons.set(&mBoat->thruster.fuelCons);
  mPropellerDiameter.set(&mBoat->thruster.propDiam);
  mForwardRotDir.set(&mBoat->thruster.forwardRotDir);
  mXBow.set(&mBoat->thruster.pos.xBow);
  mXStern.set(&mBoat->thruster.pos.xStern);
}


void ThrusterSection::init()
{
  mBow.init("Bow thruster", &mBoat->thruster.hasBowThruster);
  mStern.init("Stern thruster", &mBoat->thruster.hasSternThruster);
  mBrand.init("Brand", &mBoat->engine.brand);
  mType.init("Type", &mBoat->engine.type);
  mPower.init("Power (kW)", &mBoat->engine.power);
  mRpmMax.init("Maximum propeller rotation (rpm)", &mBoat->engine.rpmMax);
  mFuelCons.init("Fuel consumption (g/kWh)", &mBoat->engine.fuelCons);
  mPropellerDiameter.init("Thruster propeller diameter (m)", &mBoat->thruster.propDiam);
  mForwardRotDir.init("Forward rotation direction (right or left)", &mBoat->thruster.forwardRotDir);
  mXBow.init("Non dimensional longitudinal position from midship (Bow)", &mBoat->thruster.pos.xBow);
  mXStern.init("Non dimensional longitudinal position from midship (Stern)", &mBoat->thruster.pos.xStern);
}


void ThrusterSection::update(void)
{
  for(unsigned char i=0;i<THRUSTER_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void ThrusterSection::refresh(void)
{
  for(unsigned char i=0;i<THRUSTER_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
