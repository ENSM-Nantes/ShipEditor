#include "engine_section.h"

EngineSection::EngineSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Engine</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  
  // Show every field
  mNumber.getBox().show();
  mBrand.getBox().show();
  mType.getBox().show();
  mPower.getBox().show();
  mRpmMax.getBox().show();
  mFuelCons.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mNumber.getBox(), 0, 1);
  mGrid.attach(mBrand.getBox(), 0, 2);
  mGrid.attach(mType.getBox(), 1, 2);
  mGrid.attach(mPower.getBox(), 0, 3);
  mGrid.attach(mRpmMax.getBox(), 1, 3);
  mGrid.attach(mFuelCons.getBox(), 2, 3);
  
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void EngineSection::set()
{
  mNumber.set(&mBoat->engine.number);
  mBrand.set(&mBoat->engine.brand);
  mType.set(&mBoat->engine.type);
  mPower.set(&mBoat->engine.power);
  mRpmMax.set(&mBoat->engine.rpmMax);
  mFuelCons.set(&mBoat->engine.fuelCons);
}

void EngineSection::init()
{
  mNumber.init("Engine number", &mBoat->engine.number);
  mBrand.init("Brand", &mBoat->engine.brand);
  mType.init("Type", &mBoat->engine.type);
  mPower.init("Power", &mBoat->engine.power);
  mRpmMax.init("Maximum rotation per minute", &mBoat->engine.rpmMax);
  mFuelCons.init("Fuel consumption", &mBoat->engine.fuelCons);
}


void EngineSection::update(void)
{
  for(unsigned char i=0;i<ENGINE_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void EngineSection::refresh(void)
{
  for(unsigned char i=0;i<ENGINE_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
