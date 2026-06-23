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
  mTypeStr.getBox().show();
  mType.getBox().show();
  mDescription.getBox().show();
  mMmsi.getBox().show();
  mImo.getBox().show();
  mCallSign.getBox().show();
  mDestination.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mBoatName.getBox(), 0, 1, 2, 1);
  mGrid.attach(mImgName.getBox(), 1, 1, 2, 1);
  mGrid.attach(mTypeStr.getBox(), 0, 2, 2, 1);
  mGrid.attach(mType.getBox(), 0, 3, 2, 1);
  mGrid.attach(mMmsi.getBox(), 0, 4, 2, 1);
  mGrid.attach(mImo.getBox(), 1, 4, 2, 1);
  mGrid.attach(mCallSign.getBox(), 0, 5, 2, 1);
  mGrid.attach(mDestination.getBox(), 1, 5, 2, 1);
  mGrid.attach(mDescription.getBox(), 0, 6, 2, 1);
  
  mGrid.set_row_spacing(10);
  mGrid.set_margin_bottom(10);
  
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void GeneralSection::set()
{
  mBoatName.set(&mBoat->displayName);
  mImgName.set(&mBoat->imgName);
  mTypeStr.set(&mBoat->typeStr);
  mType.set(&mBoat->type);
  mDescription.set(&mBoat->desc);
  mMmsi.set(&mBoat->mmsi);
  mImo.set(&mBoat->imo);
  mCallSign.set(&mBoat->callSign);
  mDestination.set(&mBoat->dest);
}

void GeneralSection::init()
{
  mBoatName.init("Boat name : ", &mBoat->displayName);
  mImgName.init("Image name : ", &mBoat->imgName);
  mType.init("Type of Ship (norme AIS ITU-R M.1371-6) : ", &mBoat->type);
  mTypeStr.init("Type of Ship : Ferry, Container, RoRo, Tanker, BulkCarrier, Cargo, Tug or CruiseLiner), Ferry by default : ", &mBoat->typeStr);
  mDescription.init("Description or additionnal information : ", &mBoat->desc, true);
  mMmsi.init("MMSI : ", &mBoat->mmsi);
  mImo.init("IMO : ", &mBoat->imo);
  mCallSign.init("Call Sign : ", &mBoat->callSign);
  mDestination.init("Destination : ", &mBoat->dest);
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
