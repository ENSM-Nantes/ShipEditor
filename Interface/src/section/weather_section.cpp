#include "weather_section.h"

WeatherSection::WeatherSection():
  m_grid()
{
  // Show every field
  m_buffet.getBox().show();
  m_swell.getBox().show();
  m_windage.getBox().show();
  m_windage_turn_effect.getBox().show();

  // Fill the box
  m_grid.attach(m_buffet.getBox(), 0, 0);
  m_grid.attach(m_swell.getBox(), 0, 1);
  m_grid.attach(m_windage.getBox(), 1, 0);
  m_grid.attach(m_windage_turn_effect.getBox(), 1, 1);

  // Show and set the grid as the child
  m_grid.show();
  set_child(m_grid);
}

void WeatherSection::set()
{
  m_buffet.set(&mBoat->buffet);
  m_swell.set(&mBoat->swell);
  m_windage.set(&mBoat->windage);
  m_windage_turn_effect.set(&mBoat->windageTurnEffect);
}

void WeatherSection::init()
{
  m_buffet.init("Buffet", &mBoat->buffet);
  m_swell.init("Swell", &mBoat->swell);
  m_windage.init("Windage", &mBoat->windage);
  m_windage_turn_effect.init("Windage turn effect", &mBoat->windageTurnEffect);
}


void WeatherSection::update(void)
{
  for(unsigned char i=0;i<WEATHER_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void WeatherSection::refresh(void)
{
  for(unsigned char i=0;i<WEATHER_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
