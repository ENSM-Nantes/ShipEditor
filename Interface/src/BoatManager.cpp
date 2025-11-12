#include "BoatManager.hpp"
#include <iostream>
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
            v.x = item[0].asFloat();
            v.y = item[1].asFloat();
            v.z = item[2].asFloat();
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
            s.x = item[0].asFloat();
            s.y = item[1].asFloat();
            s.z = item[2].asFloat();
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
            b.viewList = make_unique<ViewList>();
            b.viewList->fromJson(root["View"]);
        }

        // RadarScreen
        if (root.isMember("RadarScreen") && root["RadarScreen"]["vector"].size() == 3) {
            b.radarScreen = make_unique<RadarScreen>();
            b.radarScreen->x = root["RadarScreen"]["vector"][0].asFloat();
            b.radarScreen->y = root["RadarScreen"]["vector"][1].asFloat();
            b.radarScreen->z = root["RadarScreen"]["vector"][2].asFloat();
            b.radarScreen->size = root["RadarScreen"]["size"].asFloat();
            b.radarScreen->tilt = root["RadarScreen"]["tilt"].asFloat();
        }

        //Throttle
        for (int i = 0; i < 3; ++i) {
            b.portThrottle[i] = root["PortThrottle"][i].asFloat();
            b.stbdThrottle[i] = root["StbdThrottle"][i].asFloat();
        }

        // Dynamics
        if (root.isMember("Dynamics")) {
            b.dynamics = make_unique<Dynamics>();
            for (int i = 0; i < 2; ++i) {
                b.dynamics->speed[i] = root["Dynamics"]["speed"][i].asFloat();
                b.dynamics->turnDrag[i] = root["Dynamics"]["turnDrag"][i].asFloat();
                b.dynamics->lateralDrag[i] = root["Dynamics"]["lateralDrag"][i].asFloat();
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
            b.prop = make_unique<Prop>();
            b.prop->space = root["Prop"]["space"].asFloat();
            b.prop->walkAhead = root["Prop"]["walkAhead"].asFloat();
            b.prop->walkAstern = root["Prop"]["walkAstern"].asFloat();
            b.prop->walkDriftEffect = root["Prop"]["walkDriftEffect"].asFloat();
        }

        // Azimuth Drive ou jsp ce que ça représente
        if (root.isMember("AzimuthDrive")) {
            const auto& ad = root["AzimuthDrive"];
            b.azimuthDrive = make_unique<AzimuthDrive>();
            b.azimuthDrive->azimuthDrive = ad["azimuthDrive"].asBool();
            b.azimuthDrive->astern = ad["astern"].asBool();
            b.azimuthDrive->aziToLengthRatio = ad["aziToLengthRatio"].asFloat();
            b.azimuthDrive->engineIdleRPM = ad["engineIdleRPM"].asInt();
            b.azimuthDrive->clutchEngageRPM = ad["clutchEngageRPM"].asInt();
            b.azimuthDrive->clutchDisengageRPM = ad["clutchDisengageRPM"].asInt();
            b.azimuthDrive->engineMaxChangePerSecond = ad["engineMaxChangePerSecond"].asFloat();
            b.azimuthDrive->maxDegPerSecond = ad["maxDegPerSecond"].asFloat();
            b.azimuthDrive->thrustLeverMaxChangePerSecond = ad["thrustLeverMaxChangePerSecond"].asFloat();
            b.azimuthDrive->sameDirectionAsSchottel = ad["sameDirectionAsSchottel"].asFloat();
        }

        // Rudder
        if (root.isMember("Rudder")) {
            b.rudder = make_unique<Rudder>();
            b.rudder->A = root["Rudder"]["A"].asFloat();
            b.rudder->B = root["Rudder"]["B"].asFloat();
            b.rudder->BAstern = root["Rudder"]["BAstern"].asFloat();
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
            b.bowThruster = make_unique<Thruster>();
            b.bowThruster->Force = root["BowThruster"]["Force"].asFloat();
            b.bowThruster->Distance = root["BowThruster"]["Distance"].asFloat();
        }

        // Stern Thruster
        if (root.isMember("SternThruster")) {
            b.sternThruster = make_unique<Thruster>();
            b.sternThruster->Force = root["SternThruster"]["Force"].asFloat();
            b.sternThruster->Distance = root["SternThruster"]["Distance"].asFloat();
        }

        // Wheel 
        if (root.isMember("Wheel") && root["Wheel"]["vector"].size() == 3) {
            b.wheel = make_unique<Wheel>();
            b.wheel->x = root["Wheel"]["vector"][0].asFloat();
            b.wheel->y = root["Wheel"]["vector"][1].asFloat();
            b.wheel->z = root["Wheel"]["vector"][2].asFloat();
            b.wheel->scale = root["Wheel"]["scale"].asFloat();
        }

        // Sails
        if (root.isMember("Sails")) {
            b.sails = make_unique<SailList>();
            b.sails->fromJson(root["Sails"]);
        }

        // Pano
        if (root.isMember("Pano")) {
            b.pano = make_unique<PanoList>();
            b.pano->fromJson(root["Pano"]);
        }

        boats.push_back(std::move(b));
    }

    return boats;
}