#include "azimuth_section.h"

AzimuthSection::AzimuthSection():
SectionSuperClass("Azimuth drive"),
m_grid(),
m_azimuth("Azimuth drive", &(boat_local.azimuthDrive.azimuthDrive)),
m_astern("Astern", &(boat_local.azimuthDrive.astern)),
m_azimuth_lenth2ratio("Azimuth to length ration", &(boat_local.azimuthDrive.aziToLengthRatio)),
m_engine_idle("Engine idle RPM", &(boat_local.azimuthDrive.engineIdleRPM)),
m_max_deg_sec("Max degrees per second", &(boat_local.azimuthDrive.maxDegPerSecond)),
m_clutch_engaged("Clutch engaged RPM", &(boat_local.azimuthDrive.clutchEngageRPM)),
m_clutch_disengage("Clutch disengaged RPM", &(boat_local.azimuthDrive.clutchDisengageRPM)),
m_thrust_lever("Thrust lever max change per second", &(boat_local.azimuthDrive.thrustLeverMaxChangePerSecond)),
m_same_dir("Same direction as schottel", &(boat_local.azimuthDrive.sameDirectionAsSchottel)),
m_engine_max_change("Engine max change per second", &(boat_local.azimuthDrive.engineMaxChangePerSecond))
{
	// Show every field
	m_azimuth.show();
	m_astern.show();
	m_azimuth_lenth2ratio.show();
	m_engine_idle.show();
	m_max_deg_sec.show();
	m_clutch_engaged.show();
	m_clutch_disengage.show();
	m_thrust_lever.show();
	m_same_dir.show();
	m_engine_max_change.show();

	// Fill the grid
	m_grid.attach(m_azimuth, 0, 0);
	m_grid.attach(m_astern, 1, 0);
	m_grid.attach(m_azimuth_lenth2ratio, 2, 0);
	m_grid.attach(m_engine_idle, 0, 1);
	m_grid.attach(m_max_deg_sec, 1, 1);
	m_grid.attach(m_clutch_engaged, 0, 2);
	m_grid.attach(m_clutch_disengage, 1, 2);
	m_grid.attach(m_thrust_lever, 0, 3);
	m_grid.attach(m_same_dir, 0, 4);
	m_grid.attach(m_engine_max_change, 1, 4);

	// Show and set the grid as the child
	m_grid.show();
	this->set_child(m_grid);

	// Save the reference to the input list
	this->input_list = (InputArea**)&input_list_local;
	this->input_count = AZIMUTH_INPUT_COUNT;
}