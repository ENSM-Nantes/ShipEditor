#include "general_section.h"

GeneralSection::GeneralSection():
  m_grid()
{
  m_filename.set("File name", &mBoat.fileName);
  m_ycorrection.set("Y correction", &mBoat.yCorrection);
  m_gps.set("GPS", &mBoat.hasGPS);
  m_scale_factor.set("Scale factor", &mBoat.scaleFactor);
  m_depth.set("Depth", &mBoat.depth);
  m_depth_sounder.set("Depth sounder", &mBoat.hasDepthSounder);
  m_max_depth.set("Max depth", &mBoat.maxDepth);
  m_make_transparent.set("Make transparent", &mBoat.makeTransparent);
  
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

void GeneralSection::update(void)
{
  for(unsigned char i=0;i<GENERAL_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void GeneralSection::reset(void)
{
  for(unsigned char i=0;i<GENERAL_INPUT_COUNT;i++)
    {
      mInputList[i]->reset();
    }
}
