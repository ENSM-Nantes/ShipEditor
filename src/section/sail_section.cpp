#include "sail_section.h"
 
SailSection::SailSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Sail</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
  
  // Show every field
  mNumber.getBox().show();
  mType.getBox().show();
  mSize.getBox().show();
 
  // Fill the grid
  mGrid.attach(mBox, 0, 0);
  mGrid.attach(mNumber.getBox(), 0, 1);
  mGrid.attach(mType.getBox(), 1, 1);
  mGrid.attach(mSize.getBox(), 2, 1);

  // mGrid.set_column_homogeneous(true);
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

SailSection::~SailSection()
{
  for(unsigned char i=0; i<MAX_SAILS; i++)
    {
      delete mPos[i];
    }
}

void SailSection::set()
{
  mNumber.set(&mBoat->sails.number);
  mType.set(&mBoat->sails.type);
  mSize.set(&mBoat->sails.size);
  
  for(unsigned char i=0; i<MAX_SAILS; i++)
    {
      mPos[i]->set(mBoat->sails.sail[i].pos, true);
    }
}

void SailSection::init()
{
  mNumber.init("Sail number", &mBoat->sails.number);
  mType.init("Type", &mBoat->sails.type);
  mSize.init("Size", &mBoat->sails.size);
  
  for(unsigned char i=0; i<MAX_SAILS; i++)
    {
      mPos.push_back(new InputArea());
 
      mPos[i]->init("Sail n° "+ std::to_string(i+1), mBoat->sails.sail[i].pos, 3);

      mPos[i]->getBox().show();
      mGrid.attach(mPos[i]->getBox(), 0, 3+i);
    }
}


void SailSection::update(void)
{
  for(unsigned char i=0;i<SAIL_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }

  for(unsigned char i=0;i<MAX_SAILS;i++)
    {
      mPos[i]->update();
    }
}

void SailSection::refresh(void)
{
  for(unsigned char i=0;i<SAIL_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }

   for(unsigned char i=0;i<MAX_SAILS;i++)
    {
      mPos[i]->refresh();
    }       
}
