#include "mesh_section.h"
#include <algorithm>

MeshSection::MeshSection():
  mGrid()
{
  mLabelSection.set_markup("<b>3D Mesh</b>");
  mLabelSection.show();
  mBox.append(mLabelSection);
  mBox.add_css_class("section-title-label");
  mBox.set_margin_bottom(10);

  // Show every field
  mFilename.getBox().show();
  mYcorrection.getBox().show();
  mAngleCorrection.getBox().show();
  mScaleFactor.getBox().show();
  mMakeTransparent.getBox().show();
  mNbrViews.getBox().show();

  mViewsAttachedCounter=0;

  // Fill the grid
  mGrid.attach(mBox, 0, 0);
  mGrid.attach(mFilename.getBox(), 0, 1);
  mGrid.attach(mAngleCorrection.getBox(), 1, 1);
  mGrid.attach(mYcorrection.getBox(), 2, 1);
  mGrid.attach(mScaleFactor.getBox(), 3, 1);

  mGrid.attach(mMakeTransparent.getBox(), 0, 2);
  mGrid.attach(mNbrViews.getBox(), 1, 2);

  mGrid.set_column_homogeneous(true);
  // Show and set the grid as the child
  mGrid.show();
  set_child(mGrid);
}

MeshSection::~MeshSection()
{
  for(unsigned char i=0; i<mViews.size(); i++)
    {
      delete mViews[i];
    }
}

void MeshSection::set()
{
  mFilename.set(&mBoat->mesh.fileName);
  mYcorrection.set(&mBoat->mesh.yCorrection);
  mAngleCorrection.set(&mBoat->mesh.angleCorrection);
  mScaleFactor.set(&mBoat->mesh.scaleFactor);
  mMakeTransparent.set(&mBoat->mesh.makeTransparent);
  mNbrViews.set(&mBoat->mesh.nbrViews);

  int nbrViews = std::max(0, mBoat->mesh.nbrViews);

  // Lazily create InputAreas for any view not yet allocated (not attached to the grid yet).
  while((int)mViews.size() < nbrViews)
    {
      int idx = (int)mViews.size();
      mViews.push_back(new InputArea());
      mIsViewTop.push_back(new InputArea());
      mViews[idx]->init("View n°" + std::to_string(idx+1), mBoat->mesh.viewList.views[idx].vector, 3);
      mIsViewTop[idx]->init("Top view : ", &mBoat->mesh.viewList.views[idx].isTop);
      mViews[idx]->getBox().hide();
      mIsViewTop[idx]->getBox().hide();
    }

  for(int i=0; i<nbrViews; i++)
    {
      mViews[i]->set(mBoat->mesh.viewList.views[i].vector, true);
      mIsViewTop[i]->set(&mBoat->mesh.viewList.views[i].isTop);
    }
}

void MeshSection::init()
{
  mFilename.init("File name", &mBoat->mesh.fileName);
  mYcorrection.init("Y correction (m)", &mBoat->mesh.yCorrection);
  mAngleCorrection.init("Angle correction (deg)", &mBoat->mesh.angleCorrection);
  mScaleFactor.init("Scale factor", &mBoat->mesh.scaleFactor);
  mMakeTransparent.init("Make transparent", &mBoat->mesh.makeTransparent);
  mNbrViews.init("Number of views", &mBoat->mesh.nbrViews);

  int nbrViews = std::max(0, mBoat->mesh.nbrViews);

  for(int i=0; i<nbrViews; i++)
    {
      mViews.push_back(new InputArea());
      mIsViewTop.push_back(new InputArea());

      mViews[i]->init("View n° "+ std::to_string(i+1), mBoat->mesh.viewList.views[i].vector, 3);
      mIsViewTop[i]->init("Top view : ", &mBoat->mesh.viewList.views[i].isTop);

      mViews[i]->getBox().show();
      mIsViewTop[i]->getBox().show();
      mGrid.attach(mViews[i]->getBox(), 0, 3+i);
      mGrid.attach(mIsViewTop[i]->getBox(), 1, 3+i);
      mViewsAttachedCounter++;
    }
}


void MeshSection::update(void)
{
  for(unsigned char i=0;i<MESH_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }

  // Views beyond what's currently allocated don't have live UI entries yet
  // (they only get created on the next Set()/Refresh() cycle, after Save reloads the boat).
  int nbrViews = std::min(std::max(0, mBoat->mesh.nbrViews), (int)mViews.size());

  for(int i=0; i<nbrViews; i++)
    {
      mViews[i]->update();
      mIsViewTop[i]->update();
    }
}

void MeshSection::refresh(void)
{
  for(unsigned char i=0;i<MESH_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }

  int nbrViews = std::min(std::max(0, mBoat->mesh.nbrViews), (int)mViews.size());

  for(int i=0; i<nbrViews; i++)
    {
      mViews[i]->refresh();
      mIsViewTop[i]->refresh();
    }

  if(mViewsAttachedCounter > nbrViews)
    {
      int toRemove = mViewsAttachedCounter - nbrViews;
      for(int j=0; j<toRemove; j++)
	{
	  int idx = mViewsAttachedCounter - 1 - j;
	  mGrid.remove(mViews[idx]->getBox());
	  mGrid.remove(mIsViewTop[idx]->getBox());
	}
      mViewsAttachedCounter -= toRemove;
    }

  if(mViewsAttachedCounter < nbrViews)
    {
      int toAttach = nbrViews - mViewsAttachedCounter;
      for(int j=0; j<toAttach; j++)
	{
	  int idx = mViewsAttachedCounter + j;
	  mViews[idx]->getBox().show();
	  mIsViewTop[idx]->getBox().show();
	  mGrid.attach(mViews[idx]->getBox(), 0, 3+idx);
	  mGrid.attach(mIsViewTop[idx]->getBox(), 1, 3+idx);
	}
      mViewsAttachedCounter += toAttach;
    }

}
