#include "general_section.h"

GeneralSection::GeneralSection():
  m_grid()
{
  // Show every field
  m_filename.getBox().show();
  m_ycorrection.getBox().show();
  m_gps.getBox().show();
  m_scale_factor.getBox().show();
  m_depth.getBox().show();
  m_depth_sounder.getBox().show();
  m_max_depth.getBox().show();
  m_make_transparent.getBox().show();

  // Fill the grid
  m_grid.attach(m_filename.getBox(), 0, 0);
  m_grid.attach(m_ycorrection.getBox(), 0, 1);
  m_grid.attach(m_gps.getBox(), 0, 2);
  m_grid.attach(m_scale_factor.getBox(), 1, 0);
  m_grid.attach(m_depth.getBox(), 1, 1);
  m_grid.attach(m_depth_sounder.getBox(), 1, 2);
  m_grid.attach(m_max_depth.getBox(), 2, 0);
  m_grid.attach(m_make_transparent.getBox(), 2, 1);

  // Show and set the grid as the child
  m_grid.show();
  set_child(m_grid);
}

void GeneralSection::set()
{
  m_filename.set(&mBoat->fileName);
  m_ycorrection.set(&mBoat->yCorrection);
  m_gps.set(&mBoat->hasGPS);
  m_scale_factor.set(&mBoat->scaleFactor);
  m_depth.set(&mBoat->depth);
  m_depth_sounder.set(&mBoat->hasDepthSounder);
  m_max_depth.set(&mBoat->maxDepth);
  m_make_transparent.set(&mBoat->makeTransparent);
}

void GeneralSection::init()
{
  m_filename.init("File name", &mBoat->fileName);
  m_ycorrection.init("Y correction", &mBoat->yCorrection);
  m_gps.init("GPS", &mBoat->hasGPS);
  m_scale_factor.init("Scale factor", &mBoat->scaleFactor);
  m_depth.init("Depth", &mBoat->depth);
  m_depth_sounder.init("Depth sounder", &mBoat->hasDepthSounder);
  m_max_depth.init("Max depth", &mBoat->maxDepth);
  m_make_transparent.init("Make transparent", &mBoat->makeTransparent);
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
