#include "azimuth_section.h"

AzimuthSection::AzimuthSection():
  m_grid()
{
  m_azimuth.set("Azimuth drive", &mBoat.azimuthDrive.azimuthDrive);
  m_astern.set("Astern", &mBoat.azimuthDrive.astern);
  m_azimuth_lenth2ratio.set("Azimuth to length ration", &mBoat.azimuthDrive.aziToLengthRatio);
  m_engine_idle.set("Engine idle RPM", &mBoat.azimuthDrive.engineIdleRPM);
  m_max_deg_sec.set("Max degrees per second", &mBoat.azimuthDrive.maxDegPerSecond);
  m_clutch_engaged.set("Clutch engaged RPM", &mBoat.azimuthDrive.clutchEngageRPM);
  m_clutch_disengage.set("Clutch disengaged RPM", &mBoat.azimuthDrive.clutchDisengageRPM);
  m_thrust_lever.set("Thrust lever max change per second", &mBoat.azimuthDrive.thrustLeverMaxChangePerSecond);
  m_same_dir.set("Same direction as schottel", &mBoat.azimuthDrive.sameDirectionAsSchottel);
  m_engine_max_change.set("Engine max change per second", &mBoat.azimuthDrive.engineMaxChangePerSecond);
  
  // Show every field
  m_azimuth.getBox().show();
  m_astern.getBox().show();
  m_azimuth_lenth2ratio.getBox().show();
  m_engine_idle.getBox().show();
  m_max_deg_sec.getBox().show();
  m_clutch_engaged.getBox().show();
  m_clutch_disengage.getBox().show();
  m_thrust_lever.getBox().show();
  m_same_dir.getBox().show();
  m_engine_max_change.getBox().show();

  // Fill the grid
  m_grid.attach(m_azimuth.getBox(), 0, 0);
  m_grid.attach(m_astern.getBox(), 1, 0);
  m_grid.attach(m_azimuth_lenth2ratio.getBox(), 2, 0);
  m_grid.attach(m_engine_idle.getBox(), 0, 1);
  m_grid.attach(m_max_deg_sec.getBox(), 1, 1);
  m_grid.attach(m_clutch_engaged.getBox(), 0, 2);
  m_grid.attach(m_clutch_disengage.getBox(), 1, 2);
  m_grid.attach(m_thrust_lever.getBox(), 0, 3);
  m_grid.attach(m_same_dir.getBox(), 0, 4);
  m_grid.attach(m_engine_max_change.getBox(), 1, 4);

  // Show and set the grid as the child
  m_grid.show();
  set_child(m_grid);

  
}

void AzimuthSection::update(void)
{
  for(unsigned char i=0;i<AZIMUTH_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}

void AzimuthSection::reset(void)
{
  for(unsigned char i=0;i<AZIMUTH_INPUT_COUNT;i++)
    {
      mInputList[i]->reset();
    }
}
