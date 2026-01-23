#include "rudder_section.h"

RudderSection::RudderSection():
  m_box(Orientation::VERTICAL)
{
  // Show every field
  m_a.getBox().show();
  m_b.getBox().show();
  m_bastern.getBox().show();

  // Fill the grid
  m_box.append(m_a.getBox());
  m_box.append(m_b.getBox());
  m_box.append(m_bastern.getBox());

  // Show and set the grid as the child
  m_box.show();
  set_child(m_box);
}

void RudderSection::set()
{
  m_a.set(&mBoat->rudder.A);
  m_b.set(&mBoat->rudder.B);
  m_bastern.set(&mBoat->rudder.BAstern);
}

void RudderSection::init()
{
  m_a.init("A", &mBoat->rudder.A);
  m_b.init("B", &mBoat->rudder.B);
  m_bastern.init("BAstern", &mBoat->rudder.BAstern);
}


void RudderSection::update(void)
{
  for(unsigned char i=0;i<RUDDER_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void RudderSection::refresh(void)
{
  for(unsigned char i=0;i<RUDDER_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
