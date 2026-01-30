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
  std::vector<Sail> sail;
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
  float lambdaR;
  float rrMax;
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
  bool hasGPS;
  bool hasDepthSounder;
  bool hasRadar;
  bool hasRateOfTurnIndicator;
  float maxDepth;
  float rho;
  Mesh mesh;
  Physical physicalCharac;
  RadarScreen radarScreen;
  Engine engine;
  Prop prop;
  Rudder rudder;
  SailList sails;  
};

class BoatManager {

public:

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

  static std::vector<Boat> LoadBoats(const std::string& aFolderPath);
  static bool SaveBoat(Boat& aBoat);
  static bool RenameBoat(Boat& aBoat);
  static const char* getTransformationPath() { return transformationPath; }
  static void setTransformationPath(const char* path) { transformationPath = path; }

private:

  inline static const char* transformationPath = "";
};

#endif
