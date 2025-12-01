#include "BoatManager.hpp"
#include <fstream>
#include <filesystem>
#include <json/json.h>

using namespace std;
namespace fs = std::filesystem;

// Implémentation des parseurs

void ViewList::fromJson(const Json::Value& json) {
    for (const auto& item : json) {
        if (item.size() >= 3) {
            View v;
            v.vector[0] = item[0].asFloat(); // x
            v.vector[1] = item[1].asFloat(); // y
            v.vector[2] = item[2].asFloat(); // z
            v.elevated = (item.size() > 3) ? item[3].asBool() : false;
            views.push_back(v);
        }
    }
}

void SailList::fromJson(const Json::Value& json) {
    const auto& list = json["list"];
    for (const auto& item : list) {
        if (item.size() >= 3) {
            Sail s;
            s.vector[0] = item[0].asFloat(); //x
            s.vector[1] = item[1].asFloat(); //y
            s.vector[2] = item[2].asFloat(); //z
            sails.push_back(s);
        }
    }
    type = json.get("type", "").asString();
    size = json.get("size", "").asString();
}

void PanoList::fromJson(const Json::Value& json) {
    const auto& files = json["file"];
    const auto& yaws = json["yaw"];
    const auto& pitches = json["pitch"];
    const auto& rolls = json["roll"];

    int count = std::min(std::min(files.size(), yaws.size()), std::min(pitches.size(), rolls.size()));
    for (int i = 0; i < count; ++i) {
        file.push_back(files[i].asString());
        yaw.push_back(yaws[i].asFloat());
        pitch.push_back(pitches[i].asFloat());
        roll.push_back(rolls[i].asFloat());
    }
}

// Lecture des bateaux

vector<Boat> BoatManager::loadBoats(const string& folderPath) {
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
        b.displayName = dirEntry.path().filename().string();
        b.fileName = root.get("FileName", "").asString();
        b.scaleFactor = root.get("ScaleFactor", 1.0).asFloat();
        b.yCorrection = root.get("YCorrection", 0.0).asFloat();
        b.angleCorrection = root.get("AngleCorrection", 0).asInt();
        b.depth = root.get("Depth", 0.0).asFloat();
        b.hasGPS = root.get("HasGPS", false).asBool();
        b.hasDepthSounder = root.get("HasDepthSounder", false).asBool();
        b.maxDepth = root.get("MaxDepth", 0.0).asFloat();
        b.makeTransparent = root.get("MakeTransparent", false).asBool();

        // View
        if (root.isMember("View")) {
            b.viewList = ViewList();
            b.viewList.fromJson(root["View"]);
        } else {
            b.viewList = ViewList();
        }

        // RadarScreen
        if (root.isMember("RadarScreen") && root["RadarScreen"]["vector"].size() == 3) {
            b.radarScreen = RadarScreen();
            b.radarScreen.vector[0] = root["RadarScreen"]["vector"][0].asFloat(); //x
            b.radarScreen.vector[1] = root["RadarScreen"]["vector"][1].asFloat(); //y
            b.radarScreen.vector[2] = root["RadarScreen"]["vector"][2].asFloat(); //z
            b.radarScreen.size = root["RadarScreen"]["size"].asFloat();
            b.radarScreen.tilt = root["RadarScreen"]["tilt"].asFloat();
        } else {
            b.radarScreen = RadarScreen();
        }

        //Throttle
        for (int i = 0; i < 3; ++i) {
            b.portThrottle[i] = root["PortThrottle"][i].asFloat();
            b.stbdThrottle[i] = root["StbdThrottle"][i].asFloat();
        }

        // Dynamics
        if (root.isMember("Dynamics")) {
            b.dynamics = Dynamics();
            for (int i = 0; i < 2; ++i) {
                b.dynamics.speed[i] = root["Dynamics"]["speed"][i].asFloat();
                b.dynamics.turnDrag[i] = root["Dynamics"]["turnDrag"][i].asFloat();
                b.dynamics.lateralDrag[i] = root["Dynamics"]["lateralDrag"][i].asFloat();
            }
        }

        // Propu FOrce
        b.maxPropulsionForce = root.get("Max_propulsion_force", 0.0).asFloat();

        // AsternEfficiency
        b.asternEfficiency = root.get("AsternEfficiency", 1.0).asFloat();

        // Block Coeff
        b.blockCoefficient = root.get("BlockCoefficient", 0.0).asFloat();

        // Mass et Inertia
        b.mass = root.get("Mass", 0.0).asFloat();
        b.inertia = root.get("Inertia", 0.0).asFloat();

        // Prop
        if (root.isMember("Prop")) {
            b.prop = Prop();
            b.prop.space = root["Prop"]["space"].asFloat();
            b.prop.walkAhead = root["Prop"]["walkAhead"].asFloat();
            b.prop.walkAstern = root["Prop"]["walkAstern"].asFloat();
            b.prop.walkDriftEffect = root["Prop"]["walkDriftEffect"].asFloat();
        } else {
            b.prop = Prop();
        }

        // Azimuth Drive ou jsp ce que ça représente
        if (root.isMember("AzimuthDrive")) {
            const auto& ad = root["AzimuthDrive"];
            b.azimuthDrive = AzimuthDrive();
            b.azimuthDrive.azimuthDrive = ad["azimuthDrive"].asBool();
            b.azimuthDrive.astern = ad["astern"].asBool();
            b.azimuthDrive.aziToLengthRatio = ad["aziToLengthRatio"].asFloat();
            b.azimuthDrive.engineIdleRPM = ad["engineIdleRPM"].asInt();
            b.azimuthDrive.clutchEngageRPM = ad["clutchEngageRPM"].asInt();
            b.azimuthDrive.clutchDisengageRPM = ad["clutchDisengageRPM"].asInt();
            b.azimuthDrive.engineMaxChangePerSecond = ad["engineMaxChangePerSecond"].asFloat();
            b.azimuthDrive.maxDegPerSecond = ad["maxDegPerSecond"].asFloat();
            b.azimuthDrive.thrustLeverMaxChangePerSecond = ad["thrustLeverMaxChangePerSecond"].asFloat();
            b.azimuthDrive.sameDirectionAsSchottel = ad["sameDirectionAsSchottel"].asFloat();
        } else {
            b.azimuthDrive = AzimuthDrive();
        }

        // Rudder
        if (root.isMember("Rudder")) {
            b.rudder = Rudder();
            b.rudder.A = root["Rudder"]["A"].asFloat();
            b.rudder.B = root["Rudder"]["B"].asFloat();
            b.rudder.BAstern = root["Rudder"]["BAstern"].asFloat();
        } else {
            b.rudder = Rudder();
        }

        // Buffet
        b.buffet = root.get("Buffet", 0.0).asFloat();

        // Swell
        b.swell = root.get("Swell", 0.0).asFloat();

        // Windage
        b.windage = root.get("Windage", 0.0).asFloat();
        b.windageTurnEffect = root.get("WindageTurnEffect", 0.0).asFloat();

        // Deviation Max
        b.deviationMaximum = root.get("DeviationMaximum", 0.0).asFloat();
        b.deviationMaximumHeading = root.get("DeviationMaximumHeading", 0.0).asFloat();

        // Period
        b.rollPeriod = root.get("RollPeriod", 0.0).asFloat();
        b.pitchPeriod = root.get("PitchPeriod", 0.0).asFloat();

        // MaxRevs
        b.maxRevs = root.get("MaxRevs", 0).asInt();

        // MaxSpeed Ahead
        b.maxSpeedAhead = root.get("MaxSpeedAhead", 0.0).asFloat();

        // Drift EFfect
        b.centrifugalDriftEffect = root.get("centrifugalDriftEffect", 0.0).asFloat();

        //RateOfTurnIndicator
        b.hasRateOfTurnIndicator = root.get("HasRateOfTurnIndicator", false).asBool();

        // Bow Thruster
        if (root.isMember("BowThruster")) {
            b.bowThruster = Thruster();
            b.bowThruster.Force = root["BowThruster"]["Force"].asFloat();
            b.bowThruster.Distance = root["BowThruster"]["Distance"].asFloat();
        } else {
            b.bowThruster = Thruster();
        }

        // Stern Thruster
        if (root.isMember("SternThruster")) {
            b.sternThruster = Thruster();
            b.sternThruster.Force = root["SternThruster"]["Force"].asFloat();
            b.sternThruster.Distance = root["SternThruster"]["Distance"].asFloat();
        } else {
            b.sternThruster = Thruster();
        }

        // Wheel 
        if (root.isMember("Wheel") && root["Wheel"]["vector"].size() == 3) {
            b.wheel = Wheel();
            b.wheel.vector[0] = root["Wheel"]["vector"][0].asFloat();
            b.wheel.vector[1] = root["Wheel"]["vector"][1].asFloat();
            b.wheel.vector[2] = root["Wheel"]["vector"][2].asFloat();
            b.wheel.scale = root["Wheel"]["scale"].asFloat();
        } else {
            b.wheel = Wheel();
        }

        // Sails
        if (root.isMember("Sails")) {
            b.sails = SailList();
            b.sails.fromJson(root["Sails"]);
        } else {
            b.sails = SailList();
        }

        // Pano
        if (root.isMember("Pano")) {
            b.pano = PanoList();
            b.pano.fromJson(root["Pano"]);
        } else {
            b.pano = PanoList();
        }

        boats.push_back(b);
    }

    return boats;
}