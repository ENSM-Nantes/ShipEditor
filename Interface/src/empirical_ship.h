#ifndef EMPIRICAL_SHIP_H
#define EMPIRICAL_SHIP_H

#include <iostream>
#include <string>
#include "BoatManager.hpp"

class EmpiricalShip
{
  public:

  EmpiricalShip(Boat& aBoat);
  ~EmpiricalShip();

  void Process(void);

 private:

  Boat& mBoat;
  float mDb; 
  float mLppB;
  float mDlPP;
  float mXpG;
  float mMp;
  float mMpX;
  float mMpY;
  float mJpZ;
};

#endif
