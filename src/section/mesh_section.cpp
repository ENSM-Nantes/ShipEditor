#include "mesh_section.h"
 
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
 
  mViewsAttachedCounter=0;
  
  // Fill the grid
  mGrid.attach(mBox, 0, 0);
  mGrid.attach(mFilename.getBox(), 0, 1);
  mGrid.attach(mAngleCorrection.getBox(), 1, 1);
  mGrid.attach(mYcorrection.getBox(), 2, 1);
  mGrid.attach(mScaleFactor.getBox(), 3, 1);
  
  mGrid.attach(mMakeTransparent.getBox(), 0, 2);

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

  while(mViews.size() < mBoat->mesh.nbrViews)
    {
      mViews.push_back(new InputArea());
      mIsViewTop.push_back(new InputArea());
      mViews.back()->init("View n°" + std::to_string(mViews.size()), mBoat->mesh.viewList.views.back().vector, 3);
      mIsViewTop.back()->init("Top view : ", &mBoat->mesh.viewList.views.back().isTop);
    }
  
  for(unsigned char i=0; i<mBoat->mesh.nbrViews; i++)
    {
      mViews[i]->set(mBoat->mesh.viewList.views[i].vector, true);
      mIsViewTop[i]->set(&mBoat->mesh.viewList.views[i].isTop);
    }
}

void MeshSection::init()
{
  mFilename.init("File name", &mBoat->mesh.fileName);
  mYcorrection.init("Y correction", &mBoat->mesh.yCorrection);
  mAngleCorrection.init("Angle correction", &mBoat->mesh.angleCorrection);
  mScaleFactor.init("Scale factor", &mBoat->mesh.scaleFactor);
  mMakeTransparent.init("Make transparent", &mBoat->mesh.makeTransparent);

  unsigned char i=0;
    
  for(i=0; i<mBoat->mesh.nbrViews; i++)
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

  for(unsigned char i=0;i<mBoat->mesh.nbrViews;i++)
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

   for(unsigned char i=0;i<mBoat->mesh.nbrViews;i++)
    {
      mViews[i]->refresh();
      mIsViewTop[i]->refresh();
    }
  
  if(mViewsAttachedCounter > mBoat->mesh.nbrViews)
    {
      for(int j=0; j<(mViewsAttachedCounter - mBoat->mesh.nbrViews); j++)
	{
	  mGrid.remove(mViews[mViews.size()-1-j]->getBox());
	  mGrid.remove(mIsViewTop[mViews.size()-1-j]->getBox());
	  mViewsAttachedCounter--;
	}
    }

  if(mViewsAttachedCounter < mBoat->mesh.nbrViews)
    {
       for(int j=0; j<(mBoat->mesh.nbrViews - mViewsAttachedCounter); j++)
	{
	  mGrid.attach(mViews[mViewsAttachedCounter+j]->getBox(), 0, 3+mViewsAttachedCounter+j);
	  mGrid.attach(mIsViewTop[mViewsAttachedCounter+j]->getBox(), 1, 3+mViewsAttachedCounter+j);
	  mViewsAttachedCounter++;
	}
    }
       
}
