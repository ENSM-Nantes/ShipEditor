#include "compass_section.h"

CompassSection::CompassSection():
  m_box(Orientation::HORIZONTAL)
{
  m_max_deviation.set("Maximum deviation", &mBoat.deviationMaximum);
  m_heading_max.set("Heading maximum", &mBoat.deviationMaximumHeading);

  // Show every field
  m_max_deviation.getBox().show();
  m_heading_max.getBox().show();

  // Fill the box
  m_box.append(m_max_deviation.getBox());
  m_box.append(m_heading_max.getBox());

  // Show and set the grid as the child
  m_box.show();
  set_child(m_box);

}


void CompassSection::update(void)
{
  for(unsigned char i=0;i<COMPASS_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void CompassSection::reset(void)
{
  for(unsigned char i=0;i<COMPASS_INPUT_COUNT;i++)
    {
      mInputList[i]->reset();
    }
}
