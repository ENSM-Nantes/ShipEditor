#include "light_section.h"
 
LightSection::LightSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Light</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
  
  // Show every field
  mNumber.getBox().show();
 
  // Fill the grid
  mGrid.attach(mBox, 0, 0);
  mGrid.attach(mNumber.getBox(), 0, 1);
 
  // mGrid.set_column_homogeneous(true);
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

LightSection::~LightSection()
{
  for(unsigned char i=0; i<MAX_LIGHT; i++)
    {
      delete mLight[i];
    }
}

void LightSection::set()
{
  mNumber.set(&mBoat->light.number);
  
  for(unsigned char i=0; i<MAX_LIGHT; i++)
    {
      mLight[i]->set(mBoat->light.light[i].data, true);
    }
}

void LightSection::init()
{
  mNumber.init("Light number", &mBoat->light.number);
  
  for(unsigned char i=0; i<MAX_LIGHT; i++)
    {
      mLight.push_back(new InputArea());
 
      mLight[i]->init("Light n° "+ std::to_string(i+1), mBoat->light.light[i].data, 9, false);

      mLight[i]->getBox().show();
      mGrid.attach(mLight[i]->getBox(), 0, 2+i);
    }
}


void LightSection::update(void)
{
  for(unsigned char i=0;i<LIGHT_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }

  for(unsigned char i=0;i<MAX_LIGHT;i++)
    {
      mLight[i]->update();
    }
}

void LightSection::refresh(void)
{
  for(unsigned char i=0;i<LIGHT_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }

   for(unsigned char i=0;i<MAX_LIGHT;i++)
    {
      mLight[i]->refresh();
    }       
}
