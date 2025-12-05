#include "propulsion_section.h"

PropulsionSection::PropulsionSection():
  m_box(Orientation::VERTICAL),
  m_box_first_line(Orientation::HORIZONTAL),
  m_box_second_line(Orientation::HORIZONTAL),
  m_box_frame(Orientation::HORIZONTAL),
  m_box_bow(Orientation::VERTICAL),
  m_box_stern(Orientation::VERTICAL),
  m_frame_bow_thruster("Bow"),
  m_frame_stern_thruster("Stern")
{
  m_max_propulsion_force.set("Max propulsion force", &mBoat.maxPropulsionForce);
  m_max_rpm.set("Max RPM", &mBoat.maxRevs);
  m_max_speed.set("Max speed", &mBoat.maxSpeedAhead);
  m_astern_efficiency.set("Astern efficiency", &mBoat.asternEfficiency);
  m_block_coeff.set("Block coefficient", &mBoat.blockCoefficient);
  m_bow_force.set("Force", &mBoat.bowThruster.Force);
  m_bow_distance.set("Distance", &mBoat.bowThruster.Distance);
  m_stern_force.set("Force", &mBoat.sternThruster.Force);
  m_stern_distance.set("Distance", &mBoat.sternThruster.Distance);
      
  // Show every field
  m_max_propulsion_force.getBox().show();
  m_max_rpm.getBox().show();
  m_max_speed.getBox().show();
  m_astern_efficiency.getBox().show();
  m_block_coeff.getBox().show();
  m_bow_force.getBox().show();
  m_bow_distance.getBox().show();
  m_stern_force.getBox().show();
  m_stern_distance.getBox().show();

	
  // Fill the two line
  m_box_first_line.append(m_max_propulsion_force.getBox());
  m_box_first_line.append(m_max_speed.getBox());
  m_box_first_line.append(m_max_rpm.getBox());

  m_box_second_line.append(m_astern_efficiency.getBox());
  m_box_second_line.append(m_block_coeff.getBox());

  // Fill the sub-sections
  m_box_bow.append(m_bow_force.getBox());
  m_box_bow.append(m_bow_distance.getBox());
  m_box_stern.append(m_stern_force.getBox());
  m_box_stern.append(m_stern_distance.getBox());

  m_frame_bow_thruster.set_child(m_box_bow);
  m_frame_stern_thruster.set_child(m_box_stern);
  m_frame_bow_thruster.show();
  m_frame_stern_thruster.show();

  m_box_frame.append(m_frame_bow_thruster);
  m_box_frame.append(m_frame_stern_thruster);

  // Fill the main box
  m_box_first_line.show();
  m_box_second_line.show();
  m_box_frame.show();
  m_box_bow.show();
  m_box_stern.show();


  // Show and set the main box as the child
  m_box.append(m_box_first_line);
  m_box.append(m_box_second_line);
  m_box.append(m_box_frame);	
  m_box.show();
  set_child(m_box);


  // Layout
  m_frame_bow_thruster.set_margin_top(5);
  m_frame_bow_thruster.set_margin_bottom(5);
  m_frame_bow_thruster.set_margin_start(10);
  m_frame_bow_thruster.set_margin_end(10);
  m_frame_stern_thruster.set_margin_top(5);
  m_frame_stern_thruster.set_margin_bottom(5);
  m_frame_stern_thruster.set_margin_start(10);
  m_frame_stern_thruster.set_margin_end(10);

}



void PropulsionSection::update(void)
{
  for(unsigned char i=0;i<PROPULSION_INPUT_COUNT;i++)
    {
      mInputList[i]->update();
    }
}


void PropulsionSection::reset(void)
{
  for(unsigned char i=0;i<PROPULSION_INPUT_COUNT;i++)
    {
      mInputList[i]->reset();
    }
}
