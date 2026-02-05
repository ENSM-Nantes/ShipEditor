#include "BoatManager.hpp"
#include "BoatRow.hpp"
#include "empirical_ship.h"
#include <gtkmm.h>
#include <fstream>
#include <filesystem>
#include <json/json.h>

namespace fs = std::filesystem;

void BoatManager::ParseMesh(Boat& aBoat, Json::Value& aJsonRoot)
{
  aBoat.mesh.fileName = aJsonRoot["mesh"]["name"].asString();
  aBoat.mesh.makeTransparent = aJsonRoot["mesh"]["makeTransparent"].asBool();    
  aBoat.mesh.scaleFactor = aJsonRoot["mesh"]["scaleFactor"].asFloat();
  aBoat.mesh.yCorrection = aJsonRoot["mesh"]["yCorrection"].asFloat();
  aBoat.mesh.angleCorrection = aJsonRoot["mesh"]["angleCorrection"].asInt();
  aBoat.mesh.nbrViews = aJsonRoot["mesh"]["numberOfViews"].asInt();

  aBoat.mesh.viewList.views.resize(aBoat.mesh.nbrViews);
    
  for (unsigned char i=0; i<aBoat.mesh.nbrViews; i++)
    {
      aBoat.mesh.viewList.views[i].vector[0] = aJsonRoot["mesh"]["views"][i][0].asFloat();
      aBoat.mesh.viewList.views[i].vector[1] = aJsonRoot["mesh"]["views"][i][1].asFloat();
      aBoat.mesh.viewList.views[i].vector[2] = aJsonRoot["mesh"]["views"][i][2].asFloat();
      aBoat.mesh.viewList.views[i].isTop = aJsonRoot["mesh"]["views"][i][3].asBool();
    }
}

void BoatManager::SetMesh(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["mesh"]["name"] = aBoat.mesh.fileName;
  aJsonRoot["mesh"]["makeTransparent"] = aBoat.mesh.makeTransparent;    
  aJsonRoot["mesh"]["scaleFactor"] = aBoat.mesh.scaleFactor;
  aJsonRoot["mesh"]["yCorrection"] = aBoat.mesh.yCorrection;
  aJsonRoot["mesh"]["angleCorrection"] = aBoat.mesh.angleCorrection;
  aJsonRoot["mesh"]["numberOfViews"] = aBoat.mesh.nbrViews;
  
  for(unsigned char i=0; i<aBoat.mesh.nbrViews; i++)
    {
      aJsonRoot["mesh"]["views"][i][0] = aBoat.mesh.viewList.views[i].vector[0];
      aJsonRoot["mesh"]["views"][i][1] = aBoat.mesh.viewList.views[i].vector[1];
      aJsonRoot["mesh"]["views"][i][2] = aBoat.mesh.viewList.views[i].vector[2];
      aJsonRoot["mesh"]["views"][i][3] = aBoat.mesh.viewList.views[i].isTop;
    }
}

void BoatManager::ParseGeneral(Boat& aBoat, Json::Value& aJsonRoot)
{
  aBoat.displayName = aJsonRoot["general"]["boatName"].asString();
  aBoat.imgName = aJsonRoot["general"]["imgName"].asString();
}

void BoatManager::SetGeneral(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["general"]["boatName"] = aBoat.displayName;
  aJsonRoot["general"]["imgName"] = aBoat.imgName;
}

void BoatManager::ParseDepth(Boat& aBoat, Json::Value& aJsonRoot)
{
  aBoat.hasDepthSounder = aJsonRoot["depthSounder"]["number"].asBool();
  aBoat.maxDepth = aJsonRoot["depthSounder"]["maxDepth"].asFloat();
}

void BoatManager::SetDepth(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["depthSounder"]["number"] = aBoat.hasDepthSounder;
  aJsonRoot["depthSounder"]["maxDepth"] = aBoat.maxDepth;
}

void BoatManager::SetAddedMass(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["addedMass"]["pX"] = aBoat.addedMass.mpX;
  aJsonRoot["addedMass"]["pY"] = aBoat.addedMass.mpY;
  aJsonRoot["addedMass"]["pZ"] = aBoat.addedMass.jpZ;
}

void BoatManager::ParseRadar(Boat& aBoat, Json::Value& aJsonRoot)
{
  aBoat.hasRadar = aJsonRoot["radar"]["number"].asBool();
  aBoat.radarScreen.vector[0] = aJsonRoot["radar"]["pos"][0].asFloat();
  aBoat.radarScreen.vector[1] = aJsonRoot["radar"]["pos"][1].asFloat();
  aBoat.radarScreen.vector[2] = aJsonRoot["radar"]["pos"][2].asFloat();
  aBoat.radarScreen.size = aJsonRoot["radar"]["size"].asFloat();
  aBoat.radarScreen.tilt = aJsonRoot["radar"]["tilt"].asFloat();
}

void BoatManager::SetRadar(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["radar"]["number"] = aBoat.hasRadar == true ? 1 : 0;
  aJsonRoot["radar"]["pos"][0] = aBoat.radarScreen.vector[0];
  aJsonRoot["radar"]["pos"][1] = aBoat.radarScreen.vector[1];
  aJsonRoot["radar"]["pos"][2] = aBoat.radarScreen.vector[2];
  aJsonRoot["radar"]["size"] = aBoat.radarScreen.size;
  aJsonRoot["radar"]["tilt"] = aBoat.radarScreen.tilt;
}

void BoatManager::ParsePhysical(Boat& aBoat, Json::Value& aJsonRoot)
{
  aBoat.rho = aJsonRoot["geoParams"]["rho"].asFloat();
  aBoat.physicalCharac.lPP = aJsonRoot["geoParams"]["length"].asFloat();
  aBoat.physicalCharac.b = aJsonRoot["geoParams"]["breadth"].asFloat();
  aBoat.physicalCharac.d = aJsonRoot["geoParams"]["draugth"].asFloat();
  aBoat.physicalCharac.volume = aJsonRoot["geoParams"]["subwaterVolume"].asFloat();
  aBoat.physicalCharac.xG = aJsonRoot["geoParams"]["longGravityCenter"].asFloat();
  aBoat.physicalCharac.cB = aJsonRoot["geoParams"]["blockCoef"].asFloat();
}

void BoatManager::SetPhysical(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["geoParams"]["rho"] = aBoat.rho;
  aJsonRoot["geoParams"]["length"] = aBoat.physicalCharac.lPP;
  aJsonRoot["geoParams"]["breadth"] = aBoat.physicalCharac.b;
  aJsonRoot["geoParams"]["draugth"] = aBoat.physicalCharac.d;
  aJsonRoot["geoParams"]["subwaterVolume"] = aBoat.physicalCharac.volume;
  aJsonRoot["geoParams"]["longGravityCenter"] = aBoat.physicalCharac.xG;
  aJsonRoot["geoParams"]["blockCoef"] = aBoat.physicalCharac.cB;
}

void BoatManager::ParseRudder(Boat& aBoat, Json::Value& aJsonRoot)
{
  aBoat.rudder.hR = aJsonRoot["rudder"]["spanLength"].asFloat();
  aBoat.rudder.aR = aJsonRoot["rudder"]["areaMobPart"].asFloat();                  
  aBoat.rudder.lambdaR = aJsonRoot["rudder"]["aspectRatio"].asFloat();            
  aBoat.rudder.rrMax = aJsonRoot["rudder"]["maxSpeed"].asFloat();
  aBoat.rudder.deltaMax = aJsonRoot["rudder"]["maxAngle"].asFloat();
}

void BoatManager::SetHull(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["hull"]["xp0"] = aBoat.hull.xp0;
  aJsonRoot["hull"]["xpVV"] = aBoat.hull.xpVV;
  aJsonRoot["hull"]["xpVR"] = aBoat.hull.xpVR;
  aJsonRoot["hull"]["xpRR"] = aBoat.hull.xpRR;
  aJsonRoot["hull"]["xpVVVV"] = aBoat.hull.xpVVVV;
  aJsonRoot["hull"]["ypV"] = aBoat.hull.ypV;
  aJsonRoot["hull"]["ypR"] = aBoat.hull.ypR;
  aJsonRoot["hull"]["ypVVV"] = aBoat.hull.ypVVV;
  aJsonRoot["hull"]["ypVVR"] = aBoat.hull.ypVVR;
  aJsonRoot["hull"]["ypVRR"] = aBoat.hull.ypVRR;
  aJsonRoot["hull"]["ypRRR"] = aBoat.hull.ypRRR;
  aJsonRoot["hull"]["npV"] = aBoat.hull.npV;
  aJsonRoot["hull"]["npR"] = aBoat.hull.npR;
  aJsonRoot["hull"]["npVVV"] = aBoat.hull.npVVV;
  aJsonRoot["hull"]["npVVR"] = aBoat.hull.npVVR;
  aJsonRoot["hull"]["npVRR"] = aBoat.hull.npVRR;
  aJsonRoot["hull"]["npRRR"] = aBoat.hull.npRRR;
}

void BoatManager::SetRudder(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["rudder"]["spanLength"] = aBoat.rudder.hR;
  aJsonRoot["rudder"]["areaMobPart"] = aBoat.rudder.aR;
  aJsonRoot["rudder"]["longCoordinateRatio"] = aBoat.rudder.xPr;
  aJsonRoot["rudder"]["forceIncreaseFactor"] = aBoat.rudder.aH;
  aJsonRoot["rudder"]["steeringResistanceFactor"] = aBoat.rudder.tR;
  aJsonRoot["rudder"]["longLateralForce"] = aBoat.rudder.xPh;
  aJsonRoot["rudder"]["wakeFractionRatio"] = aBoat.rudder.epsilon;
  aJsonRoot["rudder"]["expConstUr"] = aBoat.rudder.kappa;
  aJsonRoot["rudder"]["longCoordinatePos"] = aBoat.rudder.lPr;
  aJsonRoot["rudder"]["aspectRatio"] = aBoat.rudder.lambdaR;
  aJsonRoot["rudder"]["flowCoef"][0] = aBoat.rudder.gammaR[0];
  aJsonRoot["rudder"]["flowCoef"][1] = aBoat.rudder.gammaR[1];
  aJsonRoot["rudder"]["maxSpeed"] = aBoat.rudder.rrMax;
  aJsonRoot["rudder"]["maxAngle"] = aBoat.rudder.deltaMax;
}

void BoatManager::ParsePropeller(Boat& aBoat, Json::Value& aJsonRoot)
{
  aBoat.prop.number = aJsonRoot["propeller"]["number"].asInt();
  aBoat.prop.diameter = aJsonRoot["propeller"]["diameter"].asFloat();                  
  aBoat.prop.forwardRotDir = aJsonRoot["propeller"]["forwardRotDir"].asString();            
  aBoat.prop.backwardEff = aJsonRoot["propeller"]["backwardEff"].asFloat();
}

void BoatManager::SetPropeller(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["propeller"]["number"] = aBoat.prop.number;
  aJsonRoot["propeller"]["diameter"] = aBoat.prop.diameter;
  aJsonRoot["propeller"]["thrustFactor"] = aBoat.prop.tFactor;
  aJsonRoot["propeller"]["longPosition"] = aBoat.prop.xp;
  aJsonRoot["propeller"]["nominalWake"] = aBoat.prop.w0fraction;
  aJsonRoot["propeller"]["k0"] = aBoat.prop.k0;
  aJsonRoot["propeller"]["k1"] = aBoat.prop.k1;
  aJsonRoot["propeller"]["k2"] = aBoat.prop.k2;  
  aJsonRoot["propeller"]["forwardRotDir"] = aBoat.prop.forwardRotDir;            
  aJsonRoot["propeller"]["backwardEff"] = aBoat.prop.backwardEff;

}

void BoatManager::ParseEngine(Boat& aBoat, Json::Value& aJsonRoot)
{
  aBoat.engine.number = aJsonRoot["engine"]["number"].asInt();
  aBoat.engine.brand = aJsonRoot["engine"]["brand"].asString();
  aBoat.engine.type = aJsonRoot["engine"]["type"].asString();
  aBoat.engine.power = aJsonRoot["engine"]["power"].asFloat();
  aBoat.engine.rpmMax = aJsonRoot["engine"]["rpmMax"].asFloat();
  aBoat.engine.fuelCons = aJsonRoot["engine"]["fuelCons"].asFloat();
}

void BoatManager::SetEngine(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["engine"]["number"] = aBoat.engine.number;
  aJsonRoot["engine"]["brand"] = aBoat.engine.brand;
  aJsonRoot["engine"]["type"] = aBoat.engine.type;
  aJsonRoot["engine"]["power"] = aBoat.engine.power;
  aJsonRoot["engine"]["rpmMax"] = aBoat.engine.rpmMax;
  aJsonRoot["engine"]["fuelCons"] = aBoat.engine.fuelCons;
}

void BoatManager::SetInitialSpeed(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["initialSpeed"][0] = 0;
  aJsonRoot["initialSpeed"][1] = 0;
  aJsonRoot["initialSpeed"][2] = 0;
}

void BoatManager::ParseSail(Boat& aBoat, Json::Value& aJsonRoot)
{
  aBoat.sails.number = aJsonRoot["sail"]["number"].asInt();
  aBoat.sails.type  = aJsonRoot["sail"]["type"].asString();
  aBoat.sails.size = aJsonRoot["sail"]["size"].asString();
    
  for (unsigned char i=0; i<4; i++)
    {
      aBoat.sails.sail[i].pos[0] = aJsonRoot["sail"]["pos"][i][0].asFloat();
      aBoat.sails.sail[i].pos[1] = aJsonRoot["sail"]["pos"][i][1].asFloat();
      aBoat.sails.sail[i].pos[2] = aJsonRoot["sail"]["pos"][i][2].asFloat();
    }
}

void BoatManager::SetSail(Boat& aBoat, Json::Value& aJsonRoot)
{
  aJsonRoot["sail"]["number"] = aBoat.sails.number;
  aJsonRoot["sail"]["type"] = aBoat.sails.type;
  aJsonRoot["sail"]["size"] = aBoat.sails.size;

  for (unsigned char i=0; i<4; i++)
    {
      aJsonRoot["sail"]["pos"][i][0] = aBoat.sails.sail[i].pos[0];
      aJsonRoot["sail"]["pos"][i][1] = aBoat.sails.sail[i].pos[1];
      aJsonRoot["sail"]["pos"][i][2] = aBoat.sails.sail[i].pos[2];
    }
}

std::vector<Boat> BoatManager::LoadBoats(const std::string& aFolderPath)
{
  std::vector<Boat> boats;

  for(const auto& dirEntry : fs::directory_iterator(aFolderPath))
    {
      if (!dirEntry.is_directory()) continue;
      
      fs::path boatFile = dirEntry.path() / "boat.json";
      if (!fs::exists(boatFile)) continue;

      std::ifstream file(boatFile);
      if (!file.is_open()) continue;

      Json::Value root;
      file >> root;

      if (root.isNull()) {
	std::cerr << "Erreur de parsing JSON" << std::endl;
      }

      Boat b;

      b.imgPath = dirEntry.path().string();
      b.filePath = boatFile.string();

      //General
      ParseGeneral(b, root);
      //Mesh
      ParseMesh(b, root);
      //DepthSounder
      ParseDepth(b, root);
      //GPS
      b.hasGPS = root["gps"]["number"].asBool();
      //RoT
      b.hasRateOfTurnIndicator = root["rotIndicator"]["number"].asBool();
      // Radar
      ParseRadar(b, root);
      //Physical
      ParsePhysical(b, root);
      //Rudder
      ParseRudder(b, root);
      //Propeller
      ParsePropeller(b, root);
      //Engine
      ParseEngine(b, root);
      //Sails
      ParseSail(b, root);
    
      boats.push_back(b);
    }

  return boats;
}

bool BoatManager::SaveBoat(Boat& aBoat)
{
  Json::Value root;
  fs::path out;
  
  if (!aBoat.filePath.empty())
    {
      out = aBoat.filePath;

      EmpiricalShip empShip(aBoat);
      empShip.Process();
      //General
      SetGeneral(aBoat, root);
      //Initial Speed
      SetInitialSpeed(aBoat, root);
      //Physical
      SetPhysical(aBoat, root);
      //AddedMAss
      SetAddedMass(aBoat, root);
      //Hull
      SetHull(aBoat, root);
      //Rudder
      SetRudder(aBoat, root);
      //Propeller
      SetPropeller(aBoat, root);
      //Engine
      SetEngine(aBoat, root);
      //Sails
      SetSail(aBoat, root);
      //Mesh
      SetMesh(aBoat, root);
      //Depth
      SetDepth(aBoat, root);
      //GPS
      root["gps"]["number"] = aBoat.hasGPS;
      //RoT
      root["rotIndicator"]["number"] = aBoat.hasRateOfTurnIndicator;
      //Radar
      SetRadar(aBoat, root);

    }
  else
    {
      fs::path dest = fs::path(PATH_JSON_BOATS + aBoat.displayName);
      fs::create_directories(dest);
      out = dest / "boat.json";
      fs::copy_file("../res/boat_empty.json", out.string(), fs::copy_options::overwrite_existing);
      aBoat.filePath = out.string();
      aBoat.imgPath = dest.string();
      aBoat.imgName= aBoat.displayName + ".png";

      std::ifstream jsonFile(out);
      jsonFile >> root;
      SetGeneral(aBoat, root);
      jsonFile.close();
    }

  std::ofstream ofs(out);

  if (!ofs.is_open())
    {
      std::cerr << "Failed to open output file: " << out << std::endl;
      return false;
    }

  Json::StreamWriterBuilder w;
  std::unique_ptr<Json::StreamWriter> writer(w.newStreamWriter());
  writer->write(root, &ofs);
  ofs << std::endl;
 
  return true;
}


bool BoatManager::RemoveBoat(std::string aName)
{
  std::string dirBoatToRemove = "../res/boats/" + aName;
  
  for(const auto& dirEntry : fs::directory_iterator("../res/boats/"))
    {
      if(dirEntry.path().string() == dirBoatToRemove)
	{
	  if(!dirEntry.is_directory())
	    {
	      return false;
	    }
	  else
	    {
	      fs::remove_all(dirEntry);
	      break;
	    }
	}
    }
  return true;
}
