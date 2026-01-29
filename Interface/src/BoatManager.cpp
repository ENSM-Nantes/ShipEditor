#include "BoatManager.hpp"
#include <fstream>
#include <filesystem>
#include <json/json.h>

using namespace std;
namespace fs = std::filesystem;

// Lecture des bateaux
vector<Boat> BoatManager::loadBoats(const string& folderPath)
{
  vector<Boat> boats;

  for (const auto& dirEntry : fs::directory_iterator(folderPath)) {
    if (!dirEntry.is_directory()) continue;

    fs::path boatFile = dirEntry.path() / "boat.json";
    if (!fs::exists(boatFile)) continue;

    ifstream file(boatFile);
    if (!file.is_open()) continue;

    Json::Value root;
    file >> root;

    //test Erreur
    if (root.isNull()) {
      std::cerr << "Erreur de parsing JSON" << std::endl;
    }

    Boat b;

    b.filePath = boatFile.string();
    b.displayName = dirEntry.path().filename().string();

    //Mesh
    b.mesh.fileName = root["mesh"]["name"].asString();
    b.mesh.makeTransparent = root["mesh"]["makeTransparent"].asInt() == 1 ? true : false;    
    b.mesh.scaleFactor = root["mesh"]["scaleFactor"].asFloat();
    b.mesh.yCorrection = root["mesh"]["yCorrection"].asFloat();
    b.mesh.angleCorrection = root["mesh"]["angleCorrection"].asInt();
    b.mesh.nbrViews = root["mesh"]["numberOfViews"].asInt();

    b.mesh.viewList.views.resize(b.mesh.nbrViews);
    
    for (unsigned char i=0; i<b.mesh.nbrViews; i++)
      {
        b.mesh.viewList.views[i].vector[0] = root["mesh"]["views"][i][0].asFloat();
	b.mesh.viewList.views[i].vector[1] = root["mesh"]["views"][i][1].asFloat();
        b.mesh.viewList.views[i].vector[2] = root["mesh"]["views"][i][2].asFloat();
	b.mesh.viewList.views[i].isTop = root["mesh"]["views"][i][3].asInt() == 1 ? true : false;
      }

    //DepthSounder
    b.hasDepthSounder = root["depthSounder"]["number"].asInt() == 1 ? true : false;
    b.maxDepth = root["depthSounder"]["maxDepth"].asFloat();

    //GPS
    b.hasGPS = root["gps"]["number"].asInt() == 1 ? true : false;

    //RoT
    b.hasRateOfTurnIndicator = root["rotIndicator"]["number"].asInt() == 1 ? true : false;

    // Radar
    b.hasRadar = root["radar"]["number"].asInt() == 1 ? true : false;
    b.radarScreen.vector[0] = root["radar"]["pos"][0].asFloat();
    b.radarScreen.vector[1] = root["radar"]["pos"][1].asFloat();
    b.radarScreen.vector[2] = root["radar"]["pos"][2].asFloat();
    b.radarScreen.size = root["radar"]["size"].asFloat();
    b.radarScreen.tilt = root["radar"]["tilt"].asFloat();

    //Physical
    b.rho = root["geoParams"]["rho"].asFloat();
    b.physicalCharac.lPP = root["geoParams"]["length"].asFloat();
    b.physicalCharac.b = root["geoParams"]["breadth"].asFloat();
    b.physicalCharac.d = root["geoParams"]["draugth"].asFloat();
    b.physicalCharac.volume = root["geoParams"]["subwaterVolume"].asFloat();
    b.physicalCharac.xG = root["geoParams"]["longGravityCenter"].asFloat();
    b.physicalCharac.cB = root["geoParams"]["blockCoef"].asFloat();

    //Rudder
    b.rudder.hR = root["rudder"]["spanLength"].asFloat();
    b.rudder.aR = root["rudder"]["areaMobPart"].asFloat();                  
    b.rudder.lambdaR = root["rudder"]["aspectRatio"].asFloat();            
    b.rudder.rrMax = root["rudder"]["maxSpeed"].asFloat();

    //Propeller
    b.prop.number = root["propeller"]["number"].asInt();
    b.prop.diameter = root["propeller"]["diameter"].asFloat();                  
    b.prop.forwardRotDir = root["propeller"]["forwardRotDir"].asString();            
    b.prop.backwardEff = root["propeller"]["backwardEff"].asFloat();

    //Engine
    b.engine.number = root["engine"]["number"].asInt();
    b.engine.brand = root["engine"]["brand"].asString();
    b.engine.type = root["engine"]["type"].asString();
    b.engine.power = root["engine"]["power"].asFloat();
    b.engine.rpmMax = root["engine"]["rpmMax"].asFloat();
    b.engine.fuelCons = root["engine"]["fuelCons"].asFloat();

    //Sails
    b.sails.number = root["sail"]["number"].asInt();
    b.sails.type  = root["sail"]["type"].asString();
    b.sails.size = root["sail"]["size"].asString();

    b.sails.sail.resize(4);
    
    for (unsigned char i=0; i<4; i++)
      {
        b.sails.sail[i].pos[0] = root["sail"]["pos"][i][0].asFloat();
	b.sails.sail[i].pos[1] = root["sail"]["pos"][i][1].asFloat();
        b.sails.sail[i].pos[2] = root["sail"]["pos"][i][2].asFloat();
      }
    
    
    boats.push_back(b);
  }

  return boats;
}

bool BoatManager::saveBoat(Boat& aBoat)
{
  try {
    namespace fs = std::filesystem;

    fs::path out;

    // Cas 1 : fichier existant → écrasement
    if (!aBoat.filePath.empty()) {
      out = aBoat.filePath;
      std::cout << "out : " << out  << std::endl;
    }
    // Cas 2 : nouveau bateau
    else {
      std::string name = aBoat.displayName.empty() ? "NewBoat" : aBoat.displayName;
      for (auto &c : name)
	if (c == ' ') c = '_';

      fs::path dest = fs::path(transformationPath) / name;
      fs::create_directories(dest);

      // Le fichier JSON doit toujours s'appeler "boat.json"
      out = dest / "boat.json";

      // On met à jour filePath pour les futurs Save
      aBoat.filePath = out.string();
    }

    // ----------------------------
    // Construction du JSON (inchangé)
    // ----------------------------

    Json::Value root;
    root["FileName"] = aBoat.mesh.fileName;
    root["ScaleFactor"] = aBoat.mesh.scaleFactor;
    root["YCorrection"] = aBoat.mesh.yCorrection;
    root["AngleCorrection"] = aBoat.mesh.angleCorrection;
    
    root["HasGPS"] = aBoat.hasGPS;
    root["HasDepthSounder"] = aBoat.hasDepthSounder;
    root["MaxDepth"] = aBoat.maxDepth;
    root["MakeTransparent"] = aBoat.mesh.makeTransparent;

    // View
    Json::Value viewArr(Json::arrayValue);
    for (const auto &v : aBoat.mesh.viewList.views) {
      Json::Value item(Json::arrayValue);
      item.append(v.vector[0]);
      item.append(v.vector[1]);
      item.append(v.vector[2]);
      item.append(v.isTop);
      viewArr.append(item);
    }
    root["View"] = viewArr;

    // RadarScreen
    Json::Value rs;
    Json::Value rsvec(Json::arrayValue);
    rsvec.append(aBoat.radarScreen.vector[0]);
    rsvec.append(aBoat.radarScreen.vector[1]);
    rsvec.append(aBoat.radarScreen.vector[2]);
    rs["vector"] = rsvec;
    rs["size"] = aBoat.radarScreen.size;
    rs["tilt"] = aBoat.radarScreen.tilt;
    root["RadarScreen"] = rs;

    // Prop
    Json::Value prop;
    /*prop["space"] = aBoat.prop.space;
    prop["walkAhead"] = aBoat.prop.walkAhead;
    prop["walkAstern"] = aBoat.prop.walkAstern;
    prop["walkDriftEffect"] = aBoat.prop.walkDriftEffect;
    root["Prop"] = prop;*/

    // Rudder
    /*Json::Value rud;
    rud["A"] = aBoat.rudder.aR;
    rud["B"] = aBoat.rudder.B;
    rud["BAstern"] = aBoat.rudder.BAstern;
    root["Rudder"] = rud;*/

    // Sails
    /*    Json::Value sailsJson;
    Json::Value list(Json::arrayValue);
    for (const auto& s : aBoat.sails.sails) {
      Json::Value item(Json::arrayValue);
      item.append(s.vector[0]);
      item.append(s.vector[1]);
      item.append(s.vector[2]);
      list.append(item);
    }
    sailsJson["list"] = list;
    sailsJson["type"] = aBoat.sails.type;
    sailsJson["size"] = aBoat.sails.size;
    root["Sails"] = sailsJson;*/


    // Écriture finale
    std::ofstream ofs(out);
    if (!ofs.is_open()) {
      std::cerr << "Failed to open output file: " << out << std::endl;
      return false;
    }

    Json::StreamWriterBuilder w;
    std::unique_ptr<Json::StreamWriter> writer(w.newStreamWriter());
    writer->write(root, &ofs);
    ofs << std::endl;

    return true;

  } catch (const std::exception& e) {
    std::cerr << "Exception in saveBoat: " << e.what() << std::endl;
    return false;
  }
}
