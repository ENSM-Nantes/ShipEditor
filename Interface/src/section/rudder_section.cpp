#include "rudder_section.h"

RudderSection::RudderSection():
  m_box(Orientation::VERTICAL)
{
  m_a.set("A", &mBoat.rudder.A);
  m_b.set("B", &mBoat.rudder.B);
  m_bastern.set("BAstern", &mBoat.rudder.BAstern);

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

void RudderSection::update(void)
{
  for(unsigned char i=0;i<RUDDER_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void RudderSection::reset(void)
{
  for(unsigned char i=0;i<RUDDER_INPUT_COUNT;i++)
    {
      mInputList[i]->reset();
    }
}
