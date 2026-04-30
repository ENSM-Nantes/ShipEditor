#include "hull_section.h"

HullSection::HullSection():
  mGrid()
{
  mLabelSection.set_markup("<b>Hull</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);
  
  // Show every field
  mXp0.getBox().show();
  mXpVV.getBox().show();
  mXpVR.getBox().show();
  mXpRR.getBox().show();
  mXpVVVV.getBox().show();
  mYpV.getBox().show();
  mYpR.getBox().show();
  mYpVVV.getBox().show();
  mYpVVR.getBox().show();
  mYpVRR.getBox().show();
  mYpRRR.getBox().show();
  mNpV.getBox().show();
  mNpR.getBox().show();
  mNpVVV.getBox().show();
  mNpVVR.getBox().show();
  mNpVRR.getBox().show();
  mNpRRR.getBox().show();
  mKpG.getBox().show();
  mKpB.getBox().show();
  mKpR.getBox().show();
  mKpBBG.getBox().show();
  mKpBRG.getBox().show();
  mKpRRG.getBox().show();
  mKpBBB.getBox().show();
  mKpBBR.getBox().show();
  mKpBRR.getBox().show();
  mKpRRR.getBox().show();
  mInvertRoll.getBox().show();
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);

  mGrid.attach(mXp0.getBox(), 0, 1);
  mGrid.attach(mXpVV.getBox(), 0, 2);
  mGrid.attach(mXpVR.getBox(), 0, 3);
  mGrid.attach(mXpRR.getBox(), 0, 4);
  
  mGrid.attach(mXpVVVV.getBox(), 1, 1);
  mGrid.attach(mYpV.getBox(), 1, 2);
  mGrid.attach(mYpR.getBox(), 1, 3);
  mGrid.attach(mYpVVV.getBox(), 1, 4);
  
  mGrid.attach(mYpVVR.getBox(), 2, 1);
  mGrid.attach(mYpVRR.getBox(), 2, 2);
  mGrid.attach(mYpRRR.getBox(), 2, 3);
  mGrid.attach(mNpV.getBox(), 2, 4);
  
  mGrid.attach(mNpR.getBox(), 3, 1);
  mGrid.attach(mNpVVV.getBox(), 3, 2);
  mGrid.attach(mNpVVR.getBox(), 3, 3);
  mGrid.attach(mNpVRR.getBox(), 3, 4);
  
  mGrid.attach(mNpRRR.getBox(), 4, 1);
  mGrid.attach(mKpG.getBox(), 4, 2);
  mGrid.attach(mKpB.getBox(), 4, 3);
  mGrid.attach(mKpR.getBox(), 4, 4);
  
  mGrid.attach(mKpBBG.getBox(), 5, 1);
  mGrid.attach(mKpBRG.getBox(), 5, 2);
  mGrid.attach(mKpRRG.getBox(), 5, 3);
  mGrid.attach(mKpBBB.getBox(), 5, 4);
  
  mGrid.attach(mKpBBR.getBox(), 6, 1);
  mGrid.attach(mKpBRR.getBox(), 6, 2);
  mGrid.attach(mKpRRR.getBox(), 6, 3);

  mGrid.attach(mInvertRoll.getBox(), 0, 5);

  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

void HullSection::set()
{
  mXp0.set(&mBoat->hull.xp0);
  mXpVV.set(&mBoat->hull.xpVV);
  mXpVR.set(&mBoat->hull.xpVR);
  mXpRR.set(&mBoat->hull.xpRR);
  mXpVVVV.set(&mBoat->hull.xpVVVV);
  mYpV.set(&mBoat->hull.ypV);
  mYpR.set(&mBoat->hull.ypR);
  mYpVVV.set(&mBoat->hull.ypVVV);
  mYpVVR.set(&mBoat->hull.ypVVR);
  mYpVRR.set(&mBoat->hull.ypVRR);
  mYpRRR.set(&mBoat->hull.ypRRR);
  mNpV.set(&mBoat->hull.npV);
  mNpR.set(&mBoat->hull.npR);
  mNpVVV.set(&mBoat->hull.npVVV);
  mNpVVR.set(&mBoat->hull.npVVR);
  mNpVRR.set(&mBoat->hull.npVRR);
  mNpRRR.set(&mBoat->hull.npRRR);
  mKpG.set(&mBoat->hull.kpG);
  mKpB.set(&mBoat->hull.kpB);
  mKpR.set(&mBoat->hull.kpR);
  mKpBBG.set(&mBoat->hull.kpBBG);
  mKpBRG.set(&mBoat->hull.kpBRG);
  mKpRRG.set(&mBoat->hull.kpRRG);
  mKpBBB.set(&mBoat->hull.kpBBB);
  mKpBBR.set(&mBoat->hull.kpBBR);
  mKpBRR.set(&mBoat->hull.kpBRR);
  mKpRRR.set(&mBoat->hull.kpRRR);
  mInvertRoll.set(&mBoat->hull.invertRoll);
}

void HullSection::init()
{
  mXp0.init("X'o", &mBoat->hull.xp0, false);
  mXpVV.init("X'vv", &mBoat->hull.xpVV, false);
  mXpVR.init("X'vr", &mBoat->hull.xpVR, false);
  mXpRR.init("X'rr", &mBoat->hull.xpRR, false);
  mXpVVVV.init("X'vvvv", &mBoat->hull.xpVVVV, false);
  mYpV.init("Y'v", &mBoat->hull.ypV, false);
  mYpR.init("Y'r", &mBoat->hull.ypR, false);
  mYpVVV.init("Y'vvv", &mBoat->hull.ypVVV, false);
  mYpVVR.init("Y'vvr", &mBoat->hull.ypVVR, false);
  mYpVRR.init("Y'vrr", &mBoat->hull.ypVRR, false);
  mYpRRR.init("Y'rrr", &mBoat->hull.ypRRR, false);
  mNpV.init("N'v", &mBoat->hull.npV, false);
  mNpR.init("N'r", &mBoat->hull.npR, false);
  mNpVVV.init("N'vvv", &mBoat->hull.npVVV, false);
  mNpVVR.init("N'vvr", &mBoat->hull.npVVR, false);
  mNpVRR.init("N'vrr", &mBoat->hull.npVRR, false);
  mNpRRR.init("N'rrr", &mBoat->hull.npRRR, false);
  mKpG.init("K'g", &mBoat->hull.kpG, false);
  mKpB.init("K'b", &mBoat->hull.kpB, false);
  mKpR.init("K'r", &mBoat->hull.kpR, false);
  mKpBBG.init("K'bbg", &mBoat->hull.kpBBG, false);
  mKpBRG.init("K'brg", &mBoat->hull.kpBRG, false);
  mKpRRG.init("K'rrg", &mBoat->hull.kpRRG, false);
  mKpBBB.init("K'bbb", &mBoat->hull.kpBBB, false);
  mKpBBR.init("K'bbr", &mBoat->hull.kpBBR, false);
  mKpBRR.init("K'brr", &mBoat->hull.kpBRR, false);
  mKpRRR.init("K'rrr", &mBoat->hull.kpRRR, false);
  mInvertRoll.init("Invert roll", &mBoat->hull.invertRoll);
}


void HullSection::update(void)
{
  for(unsigned char i=0;i<HULL_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void HullSection::refresh(void)
{
  for(unsigned char i=0;i<HULL_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
