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

// Manager

/**
 * @brief permet de charger tous les bateaux dans une liste
 *
 * @param folderPath le chemin d'accès dossier contenant les sous dossiers de tous les fichiers json complet
 */
class BoatManager {
public:
  std::vector<Boat> loadBoats(const std::string& folderPath);
  // Save a Boat into a new subfolder. Returns true on success.
  bool saveBoat(Boat& b);
  // Rename a boat folder if the displayName has changed. Returns true on success.
  bool renameBoat(Boat& b);
    
  // Get the transformation path
  static const char* getTransformationPath() { return transformationPath; }
    
  // Set the transformation path
  static void setTransformationPath(const char* path) { transformationPath = path; }

private:
  // Path to the transformation folder containing all boats
  inline static const char* transformationPath = "";
};

#endif
