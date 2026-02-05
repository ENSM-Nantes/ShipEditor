#ifndef MESH_SECTION_H
#define MESH_SECTION_H

#include <gtkmm.h>
#include "../input_area.h"
#include "../BoatManager.hpp"
#include "section.h"

#define MESH_INPUT_COUNT 5

using namespace Gtk;

class MeshSection: public Section {
public:
  MeshSection();
  ~MeshSection();

  virtual void init(void);
  virtual void set(void);
  virtual void update(void);
  virtual void refresh(void);
  
protected:
  Grid mGrid;
  int mViewsAttachedCounter;
  InputArea mFilename, mYcorrection, mAngleCorrection, mScaleFactor, mMakeTransparent;
  std::vector<InputArea*> mViews;
  std::vector<InputArea*> mIsViewTop;
  InputArea *mInputList[MESH_INPUT_COUNT] = {&mFilename, &mYcorrection, &mAngleCorrection, &mScaleFactor, &mMakeTransparent};

};


#endif
