#include "propertie_section.h"

PropertieSection::PropertieSection():
  m_grid()
{
  m_mass.set("Mass", &mBoat.mass);
  m_inertia.set("Inertia", &mBoat.inertia);
  m_space.set("Space", &mBoat.prop.space);
  m_walk_ahead.set("Walk ahead", &mBoat.prop.walkAhead);
  m_walk_astern.set("Walk Astern", &mBoat.prop.walkAstern);
  m_walk_drift_effect.set("Walk drift effect", &mBoat.prop.walkDriftEffect);
  m_roll_period.set("Roll period", &mBoat.rollPeriod);
  m_pitch_period.set("Pitch period", &mBoat.pitchPeriod);
  m_centrifugal_drift_effect.set("Centrifugal drift effect", &mBoat.centrifugalDriftEffect);
  m_turn_indicator_rate.set("Rate of turn indicator", &mBoat.hasRateOfTurnIndicator);
      
  // Show every field
  m_mass.getBox().show();
  m_inertia.getBox().show();
  m_space.getBox().show();
  m_walk_ahead.getBox().show();
  m_walk_astern.getBox().show();
  m_walk_drift_effect.getBox().show();
  m_roll_period.getBox().show();
  m_pitch_period.getBox().show();
  m_centrifugal_drift_effect.getBox().show();
  m_turn_indicator_rate.getBox().show();

  // Fill the grid
  m_grid.attach(m_mass.getBox(), 0, 0);
  m_grid.attach(m_inertia.getBox(), 0, 1);
  m_grid.attach(m_space.getBox(), 0, 2);
  m_grid.attach(m_walk_ahead.getBox(), 1, 0);
  m_grid.attach(m_walk_astern.getBox(), 1, 1);
  m_grid.attach(m_walk_drift_effect.getBox(), 1, 2);
  m_grid.attach(m_roll_period.getBox(), 2, 0);
  m_grid.attach(m_pitch_period.getBox(), 2, 1);
  m_grid.attach(m_centrifugal_drift_effect.getBox(), 2, 2);
  m_grid.attach(m_turn_indicator_rate.getBox(), 3, 0);
	
  // Show and set the grid as the child
  m_grid.show();
  set_child(m_grid);
}


void PropertieSection::update(void)
{
  for(unsigned char i=0;i<PROPERTIE_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void PropertieSection::reset(void)
{
  for(unsigned char i=0;i<PROPERTIE_INPUT_COUNT;i++)
    {
      mInputList[i]->reset();
    }
}
