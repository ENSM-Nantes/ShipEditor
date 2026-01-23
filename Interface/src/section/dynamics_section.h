#ifndef DYNAMICS_SECTION_H
#define DYNAMICS_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define DYNAMICS_INPUT_COUNT 6

using namespace Gtk;

class DynamicsSection: public Section {
public:
  DynamicsSection();
  ~DynamicsSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid m_grid;

  InputArea m_speed, m_speed_sq, m_turndrag, m_turndrag_sq, m_lateraldrag, m_lateraldrag_sq;

  InputArea *mInputList[DYNAMICS_INPUT_COUNT] = {
    &m_speed, &m_speed_sq,
    &m_turndrag, &m_turndrag_sq,
    &m_lateraldrag, &m_lateraldrag_sq
  };
  
};

#endif
