#include <cmath>
#include "empirical_ship.h"

EmpiricalShip::EmpiricalShip(Boat& aBoat) : mBoat(aBoat)
{
  
}

EmpiricalShip::~EmpiricalShip()
{

}

void EmpiricalShip::Process(void)
{
  Physical *pPhy = &mBoat.physicalCharac;
  AddedMass *pAddMass = &mBoat.addedMass;
  Hull *pHull = &mBoat.hull;
  Prop *pProp = &mBoat.prop;
  Rudder *pRudder = &mBoat.rudder;

  //Constants
  mDb = pPhy->d / pPhy->b;
  mLppB = pPhy->lPP / pPhy->b;
  mDlPP = pPhy->d / pPhy->lPP;
  mXpG = pPhy->xG / pPhy->lPP;

  //Added Mass
  mMp = pPhy->volume / (0.5 * (pPhy->lPP*pPhy->lPP) * pPhy->d);
  mMpX = 0.05 * mMp;
  mMpY = (0.882 -
	  0.54 * pPhy->cB * (1 - 1.6 * mDb) -
	  0.156 * (1 - 0.673 * pPhy->cB) * mLppB +
	  0.826 * mDb * mLppB * (1 - 0.678 * mDb) -
	  0.638 * pPhy->cB * mDb * mLppB * (1 - 0.669 * mDb)
	  ) * mMp;

  mJpZ = mMp * std::pow((0.01 * (33. - 76.85 * pPhy->cB * (1 - 0.784 * pPhy->cB) + 3.43 * mLppB * (1 - 0.63 * pPhy->cB))), 2);

  pAddMass->mpX = 2 * mMpX;
  pAddMass->mpY = mMpY;
  pAddMass->jpZ = mJpZ;

  //Hull
  pHull->xp0 = 0.022;
  pHull->xpVV = 1.15 * pPhy->cB / mLppB - 0.18;
  pHull->xpVR = mMpY - 1.91 * pPhy->cB / mLppB + 0.08;
  pHull->xpRR = -0.085 * pPhy->cB / mLppB + 0.008 - mXpG * mMpY;
  pHull->xpVVVV = -6.68 * pPhy->cB / mLppB + 1.1;
  pHull->ypV = -(0.5 * M_PI * 2 * mDlPP + 1.4 * pPhy->cB / mLppB);
  pHull->ypR = mMpX + 0.5 * pPhy->cB / mLppB;
  pHull->ypVVV = -0.185 * mLppB + 0.48;
  pHull->ypVVR = -0.75;
  pHull->ypVRR = -(0.26 * (1 - pPhy->cB) * mLppB + 0.11);
  pHull->ypRRR = -0.051; 
  pHull->npV = -2 * mDlPP;
  pHull->npR = -0.54 * 2. * mDlPP + std::pow((2 * mDlPP), 2);
  pHull->npVVV = -(-0.69 * pPhy->cB + 0.66);
  pHull->npVVR = 1.55 * pPhy->cB / mLppB - 0.76;
  pHull->npVRR = -0.075 * (1. - pPhy->cB) * mLppB - 0.098;
  pHull->npRRR = 0.25 * pPhy->cB / mLppB - 0.056;

  //Propeller
  pProp->tFactor = 0.27;
  pProp->xp = -0.48; 
  pProp->w0fraction = 0.5 * pPhy->cB - 0.05;
  pProp->k0 = 0.293; 
  pProp->k1 = -0.275; 
  pProp->k2 = -0.139;

  //Rudder
  pRudder->xPr= -0.5;
  pRudder->aH = 3.6 * pPhy->cB / mLppB; 
  pRudder->tR = 0.39; 
  pRudder->xPh = -0.4;
  pRudder->epsilon = 2.26 - 1.82 * (1 - (0.5 * pPhy->cB - 0.05));
  pRudder->kappa = 0.55 / (2.26 * 1.82 * (1 - (0.5 * pPhy->cB - 0.05)));
  pRudder->lPr = -0.9; 
  pRudder->gammaR[0] = 2.06 * pPhy->cB / mLppB + 0.14;
  pRudder->gammaR[1] = 2.06 * pPhy->cB / mLppB + 0.14;
}
