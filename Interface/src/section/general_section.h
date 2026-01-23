#ifndef GENERAL_FRAME_H
#define GENERAL_FRAME_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define GENERAL_INPUT_COUNT 8

using namespace Gtk;

class GeneralSection: public Section {
public:
  GeneralSection();
  ~GeneralSection() {}

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid m_grid;

  InputArea m_filename, m_ycorrection, m_gps, m_scale_factor, m_depth, m_depth_sounder, m_max_depth, m_make_transparent;

  InputArea *mInputList[GENERAL_INPUT_COUNT] = {
    &m_filename, &m_ycorrection, &m_gps, &m_scale_factor,
    &m_depth, &m_depth_sounder, &m_max_depth,
    &m_make_transparent
  };

};


#endif
