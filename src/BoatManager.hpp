#ifndef BOAT_MANAGER_H
#define BOAT_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <json/json.h>

struct View
{
  float vector[3];
  bool isTop;
};

struct ViewList
{
  std::vector<View> views;
};

struct Sail
{
  float pos[3];
};

struct SailList
{
  int number;
  Sail sail[4];
  std::string type;
  std::string size;
};

struct RadarScreen
{
  float vector[3];
  float size;
  float tilt;
};

struct Prop
{
  int number;
  float diameter;
  float tFactor;
  float xp; 
  float w0fraction;
  float k0; 
  float k1; 
  float k2 ;
  std::string forwardRotDir;
  float backwardEff;
};

struct Engine {
  int number;
  std::string brand;
  std::string type;
  float power;
  float rpmMax;
  float fuelCons;
};

struct Rudder
{
  float hR;
  float aR;
  float xPr;
  float aH; 
  float tR; 
  float xPh;
  float epsilon;
  float kappa;
  float lPr; 
  float lambdaR; 
  double gammaR[2];
  float rrMax;
  float deltaMax;
};

struct Physical
{
  float lPP;
  float b;
  float d;
  float volume;
  float xG;
  float cB;
};

struct AddedMass{
  float mpX;
  float mpY;
  float jpZ;
};

struct Hull
{
  float xp0;
  float xpVV;
  float xpVR;
  float xpRR;
  float xpVVVV;
  float ypV;
  float ypR;
  float ypVVV;
  float ypVVR;
  float ypVRR;
  float ypRRR;
  float npV;
  float npR;
  float npVVV;
  float npVVR;
  float npVRR;
  float npRRR;
};


struct Mesh
{
  std::string fileName;
  float scaleFactor;
  float yCorrection;
  int angleCorrection;
  int nbrViews;
  ViewList viewList;
  bool makeTransparent;
};

struct Boat
{
  std::string filePath;
  std::string displayName;
  std::string imgPath;
  std::string imgName;
  bool hasGPS;
  bool hasDepthSounder;
  bool hasRadar;
  bool hasRateOfTurnIndicator;
  float maxDepth;
  float rho;
  Mesh mesh;
  Physical physicalCharac;
  AddedMass addedMass;
  RadarScreen radarScreen;
  Engine engine;
  Hull hull;
  Prop prop;
  Rudder rudder;
  SailList sails;  
};

class BoatManager {

public:
  
  static void SetInitialSpeed(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetHull(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetAddedMass(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetSail(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetEngine(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetPropeller(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetRudder(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetPhysical(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetRadar(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetDepth(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetMesh(Boat& aBoat, Json::Value& aJsonRoot);
  static void ParseSail(Boat& aBoat, Json::Value& aJsonRoot);
  static void ParseEngine(Boat& aBoat, Json::Value& aJsonRoot);
  static void ParsePropeller(Boat& aBoat, Json::Value& aJsonRoot);
  static void ParseRudder(Boat& aBoat, Json::Value& aJsonRoot);
  static void ParsePhysical(Boat& aBoat, Json::Value& aJsonRoot);
  static void ParseRadar(Boat& aBoat, Json::Value& aJsonRoot);
  static void ParseDepth(Boat& aBoat, Json::Value& aJsonRoot);
  static void ParseMesh(Boat& aBoat, Json::Value& aJsonRoot);
  static void SetGeneral(Boat& aBoat, Json::Value& aJsonRoot);
  static void ParseGeneral(Boat& aBoat, Json::Value& aJsonRoot);

  
  static std::vector<Boat> LoadBoats(const std::string& aFolderPath);
  static bool SaveBoat(Boat& aBoat);
  static bool RemoveBoat(std::string aName);
  
};

#endif
