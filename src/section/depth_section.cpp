#include "depth_section.h"

DepthSection::DepthSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Depth sounder</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
  
  // Show every field
  mDepthSounder.getBox().show();
  mMaxDepth.getBox().show();

  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mDepthSounder.getBox(), 0, 1);
  mGrid.attach(mMaxDepth.getBox(), 0, 2);

  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void DepthSection::set()
{
  mDepthSounder.set(&mBoat->hasDepthSounder);
  mMaxDepth.set(&mBoat->maxDepth);
}

void DepthSection::init()
{
  mDepthSounder.init("Depth sounder", &mBoat->hasDepthSounder);
  mMaxDepth.init("Max depth", &mBoat->maxDepth);
}


void DepthSection::update(void)
{
  for(unsigned char i=0;i<DEPTH_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void DepthSection::refresh(void)
{
  for(unsigned char i=0;i<DEPTH_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
