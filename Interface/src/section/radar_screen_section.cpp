#include "radar_screen_section.h"

RadarScreenSection::RadarScreenSection():
  m_box(Orientation::VERTICAL)
{
     
  // Show every field
  m_size.getBox().show();
  m_tilt.getBox().show();
  m_vector.getBox().show();
  m_port_throttle.getBox().show();
  m_stbd_throttle.getBox().show();

  // Fill the box
  m_box.append(m_size.getBox());
  m_box.append(m_tilt.getBox());
  m_box.append(m_vector.getBox());
  m_box.append(m_port_throttle.getBox());
  m_box.append(m_stbd_throttle.getBox());
	
  // Show and set the box as the child
  m_box.show();
  set_child(m_box);
}

void RadarScreenSection::set()
{
  m_size.set(&mBoat->radarScreen.size);
  m_tilt.set(&mBoat->radarScreen.tilt);
  m_vector.set((float*)&mBoat->radarScreen.vector, true);
  m_port_throttle.set((float*)&mBoat->portThrottle, true);
  m_stbd_throttle.set((float*)&mBoat->stbdThrottle, true);
}

void RadarScreenSection::init()
{
  m_size.init("Size", &mBoat->radarScreen.size);
  m_tilt.init("Tilt", &mBoat->radarScreen.tilt);
  m_vector.init("Vector", (float*)&mBoat->radarScreen.vector, 3);
  m_port_throttle.init("Port throttle", (float*)&mBoat->portThrottle, 3);
  m_stbd_throttle.init("Stbd throttle", (float*)&mBoat->stbdThrottle, 3);
}

void RadarScreenSection::update(void)
{
  for(unsigned char i=0;i<RADAR_SCREEN_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void RadarScreenSection::refresh(void)
{
  for(unsigned char i=0;i<RADAR_SCREEN_INPUT_COUNT;i++)
    {
      mInputList[i]->refresh();
    }
}
