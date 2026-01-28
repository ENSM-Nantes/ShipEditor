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
    b.fileName = root["mesh"]["name"].asString();
    b.makeTransparent = root["mesh"]["makeTransparent"].asInt() == 1 ? true : false;    
    b.scaleFactor = root["mesh"]["scaleFactor"].asFloat();
    b.yCorrection = root["mesh"]["yCorrection"].asFloat();
    b.angleCorrection = root["mesh"]["angleCorrection"].asInt();
    b.nbrViews = root["mesh"]["numberOfViews"].asInt();

    b.viewList.views.resize(b.nbrViews);
    
    for (unsigned char i=0; i<b.nbrViews; i++)
      {
        b.viewList.views[i].vector[0] = root["mesh"]["views"][i][0].asFloat();
	b.viewList.views[i].vector[1] = root["mesh"]["views"][i][1].asFloat();
        b.viewList.views[i].vector[2] = root["mesh"]["views"][i][2].asFloat();
	b.viewList.views[i].isTop = root["mesh"]["views"][i][3].asInt() == 1 ? true : false;
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
    
    boats.push_back(b);
  }

  return boats;
}

bool BoatManager::saveBoat(Boat& b) {
  try {
    namespace fs = std::filesystem;

    fs::path out;

    // Cas 1 : fichier existant → écrasement
    if (!b.filePath.empty()) {
      out = b.filePath;
      std::cout << "out : " << out  << std::endl;
    }
    // Cas 2 : nouveau bateau
    else {
      std::string name = b.displayName.empty() ? "NewBoat" : b.displayName;
      for (auto &c : name)
	if (c == ' ') c = '_';

      fs::path dest = fs::path(transformationPath) / name;
      fs::create_directories(dest);

      // Le fichier JSON doit toujours s'appeler "boat.json"
      out = dest / "boat.json";

      // On met à jour filePath pour les futurs Save
      b.filePath = out.string();
    }

    // ----------------------------
    // Construction du JSON (inchangé)
    // ----------------------------

    Json::Value root;
    root["FileName"] = b.fileName;
    root["ScaleFactor"] = b.scaleFactor;
    root["YCorrection"] = b.yCorrection;
    root["AngleCorrection"] = b.angleCorrection;
    root["Depth"] = b.depth;
    root["HasGPS"] = b.hasGPS;
    root["HasDepthSounder"] = b.hasDepthSounder;
    root["MaxDepth"] = b.maxDepth;
    root["MakeTransparent"] = b.makeTransparent;

    // View
    Json::Value viewArr(Json::arrayValue);
    for (const auto &v : b.viewList.views) {
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
    rsvec.append(b.radarScreen.vector[0]);
    rsvec.append(b.radarScreen.vector[1]);
    rsvec.append(b.radarScreen.vector[2]);
    rs["vector"] = rsvec;
    rs["size"] = b.radarScreen.size;
    rs["tilt"] = b.radarScreen.tilt;
    root["RadarScreen"] = rs;

    // Port / Stbd Throttles
    Json::Value pt(Json::arrayValue), st(Json::arrayValue);
    for (int i = 0; i < 3; ++i) {
      pt.append(b.portThrottle[i]);
      st.append(b.stbdThrottle[i]);
    }
    root["PortThrottle"] = pt;
    root["StbdThrottle"] = st;

    // Dynamics
    Json::Value dyn;
    Json::Value speed(Json::arrayValue), turn(Json::arrayValue), lat(Json::arrayValue);
    for (int i = 0; i < 2; ++i) {
      speed.append(b.dynamics.speed[i]);
      turn.append(b.dynamics.turnDrag[i]);
      lat.append(b.dynamics.lateralDrag[i]);
    }

    dyn["speed"] = speed;
    dyn["turnDrag"] = turn;
    dyn["lateralDrag"] = lat;
    root["Dynamics"] = dyn;

    root["Max_propulsion_force"] = b.maxPropulsionForce;
    root["AsternEfficiency"] = b.asternEfficiency;
    root["BlockCoefficient"] = b.blockCoefficient;
    root["Mass"] = b.mass;
    root["Inertia"] = b.inertia;

    // Prop
    Json::Value prop;
    prop["space"] = b.prop.space;
    prop["walkAhead"] = b.prop.walkAhead;
    prop["walkAstern"] = b.prop.walkAstern;
    prop["walkDriftEffect"] = b.prop.walkDriftEffect;
    root["Prop"] = prop;

    // AzimuthDrive
    Json::Value ad;
    ad["azimuthDrive"] = b.azimuthDrive.azimuthDrive;
    ad["astern"] = b.azimuthDrive.astern;
    ad["aziToLengthRatio"] = b.azimuthDrive.aziToLengthRatio;
    ad["engineIdleRPM"] = b.azimuthDrive.engineIdleRPM;
    ad["clutchEngageRPM"] = b.azimuthDrive.clutchEngageRPM;
    ad["clutchDisengageRPM"] = b.azimuthDrive.clutchDisengageRPM;
    ad["engineMaxChangePerSecond"] = b.azimuthDrive.engineMaxChangePerSecond;
    ad["maxDegPerSecond"] = b.azimuthDrive.maxDegPerSecond;
    ad["thrustLeverMaxChangePerSecond"] = b.azimuthDrive.thrustLeverMaxChangePerSecond;
    ad["sameDirectionAsSchottel"] = b.azimuthDrive.sameDirectionAsSchottel;
    root["AzimuthDrive"] = ad;

    // Rudder
    Json::Value rud;
    rud["A"] = b.rudder.A;
    rud["B"] = b.rudder.B;
    rud["BAstern"] = b.rudder.BAstern;
    root["Rudder"] = rud;

    // Thrusters
    Json::Value bow, stern;
    bow["Force"] = b.bowThruster.Force;
    bow["Distance"] = b.bowThruster.Distance;
    stern["Force"] = b.sternThruster.Force;
    stern["Distance"] = b.sternThruster.Distance;
    root["BowThruster"] = bow;
    root["SternThruster"] = stern;

    // Wheel
    Json::Value wheel;
    Json::Value wvec(Json::arrayValue);
    wvec.append(b.wheel.vector[0]);
    wvec.append(b.wheel.vector[1]);
    wvec.append(b.wheel.vector[2]);
    wheel["vector"] = wvec;
    wheel["scale"] = b.wheel.scale;
    root["Wheel"] = wheel;

    // Sails
    Json::Value sailsJson;
    Json::Value list(Json::arrayValue);
    for (const auto& s : b.sails.sails) {
      Json::Value item(Json::arrayValue);
      item.append(s.vector[0]);
      item.append(s.vector[1]);
      item.append(s.vector[2]);
      list.append(item);
    }
    sailsJson["list"] = list;
    sailsJson["type"] = b.sails.type;
    sailsJson["size"] = b.sails.size;
    root["Sails"] = sailsJson;

    // Pano
    Json::Value panoJson;
    Json::Value files(Json::arrayValue), yaws(Json::arrayValue),
      pitches(Json::arrayValue), rolls(Json::arrayValue);
    for (const auto& f : b.pano.file) files.append(f);
    for (const auto& v : b.pano.yaw) yaws.append(v);
    for (const auto& v : b.pano.pitch) pitches.append(v);
    for (const auto& v : b.pano.roll) rolls.append(v);

    panoJson["file"] = files;
    panoJson["yaw"] = yaws;
    panoJson["pitch"] = pitches;
    panoJson["roll"] = rolls;
    root["Pano"] = panoJson;

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
