#include "dynamics_section.h"

DynamicsSection::DynamicsSection():
  m_grid()
{
  m_speed.set("Speed", &mBoat.dynamics.speed[1]);
  m_speed_sq.set("Speed (squared)", &mBoat.dynamics.speed[0]);
  m_turndrag.set("Turn drag", &mBoat.dynamics.turnDrag[1]);
  m_turndrag_sq.set("Turn drag (squared)", &mBoat.dynamics.turnDrag[0]);
  m_lateraldrag.set("Lateral drag", &mBoat.dynamics.lateralDrag[1]);
  m_lateraldrag_sq.set("Lateral drag (squared)", &mBoat.dynamics.lateralDrag[0]);
  
  // Show every field
  m_speed.getBox().show();
  m_speed_sq.getBox().show();
  m_turndrag.getBox().show();
  m_turndrag_sq.getBox().show();
  m_lateraldrag.getBox().show();
  m_lateraldrag_sq.getBox().show();

  // Fill the box
  m_grid.attach(m_speed.getBox(), 0, 0);
  m_grid.attach(m_speed_sq.getBox(), 1, 0);
  m_grid.attach(m_turndrag.getBox(), 0, 1);
  m_grid.attach(m_turndrag_sq.getBox(), 1, 1);
  m_grid.attach(m_lateraldrag.getBox(), 0, 2);
  m_grid.attach(m_lateraldrag_sq.getBox(), 1, 2);

  // Show and set the grid as the child
  m_grid.show();
  set_child(m_grid);

}

void DynamicsSection::update(void)
{
  for(unsigned char i=0;i<DYNAMICS_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void DynamicsSection::reset(void)
{
  for(unsigned char i=0;i<DYNAMICS_INPUT_COUNT;i++)
    {
      mInputList[i]->reset();
    }
}
