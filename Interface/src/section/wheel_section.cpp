#include "wheel_section.h"

WheelSection::WheelSection():
  m_box(Orientation::VERTICAL)
{
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

void WheelSection::set()
{
  m_vector.set((float*)&mBoat->wheel.vector);
  m_scale.set(&mBoat->wheel.scale);
}

void WheelSection::init()
{
  m_vector.init("Vector", (float*)&mBoat->wheel.vector, true);
  m_scale.init("Scale", &mBoat->wheel.scale);
}

void WheelSection::update(void)
{
  for(unsigned char i=0;i<WHEEL_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}


void WheelSection::refresh(void)
{
  for(unsigned char i=0;i<WHEEL_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
