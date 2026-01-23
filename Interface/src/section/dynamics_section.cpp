#include "dynamics_section.h"

DynamicsSection::DynamicsSection():
  m_grid()

{
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

void DynamicsSection::set()
{
  m_speed.set(&mBoat->dynamics.speed[1]);
  m_speed_sq.set(&mBoat->dynamics.speed[0]);
  m_turndrag.set(&mBoat->dynamics.turnDrag[1]);
  m_turndrag_sq.set(&mBoat->dynamics.turnDrag[0]);
  m_lateraldrag.set(&mBoat->dynamics.lateralDrag[1]);
  m_lateraldrag_sq.set(&mBoat->dynamics.lateralDrag[0]);
}

void DynamicsSection::init()
{
  m_speed.init("Speed", &mBoat->dynamics.speed[1]);
  m_speed_sq.init("Speed (squared)", &mBoat->dynamics.speed[0]);
  m_turndrag.init("Turn drag", &mBoat->dynamics.turnDrag[1]);
  m_turndrag_sq.init("Turn drag (squared)", &mBoat->dynamics.turnDrag[0]);
  m_lateraldrag.init("Lateral drag", &mBoat->dynamics.lateralDrag[1]);
  m_lateraldrag_sq.init("Lateral drag (squared)", &mBoat->dynamics.lateralDrag[0]);
}


void DynamicsSection::update(void)
{
  for(unsigned char i=0;i<DYNAMICS_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void DynamicsSection::refresh(void)
{
  for(unsigned char i=0;i<DYNAMICS_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
