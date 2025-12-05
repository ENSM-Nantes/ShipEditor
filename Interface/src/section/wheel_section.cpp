#include "wheel_section.h"

WheelSection::WheelSection():
  m_box(Orientation::VERTICAL) 
{
  m_vector.set("Vector", (float*)&mBoat.wheel.vector, true);
  m_scale.set("Scale", &mBoat.wheel.scale);
  // Show every field
  m_vector.getBox().show();
  m_scale.getBox().show();

  // Fill the box
  m_box.append(m_vector.getBox());
  m_box.append(m_scale.getBox());

  // Show and set the grid as the child
  m_box.show();
  set_child(m_box);
}

void WheelSection::update(void)
{
  for(unsigned char i=0;i<WHEEL_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}


void WheelSection::reset(void)
{
  for(unsigned char i=0;i<WHEEL_INPUT_COUNT;i++)
    {
      mInputList[i]->reset();
    }
}
