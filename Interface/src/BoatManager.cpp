#include "BoatManager.hpp"
#include <fstream>
#include <filesystem>
#include <json/json.h>

using namespace std;
namespace fs = std::filesystem;

/**
 * Fonction pour charger les fichiers json dans des objets Boat
 * @param string le chemin d'accès pour accéder au dossier qui contient les sous-dossiers des bateaux qui contiennent les boat.json
 */
vector<Boat> BoatManager::loadBoats(const string& folderPath) {
    vector<Boat> boats;

    for (const auto& dirEntry : fs::directory_iterator(folderPath)) {
        if (!dirEntry.is_directory()) continue;

        fs::path boatFile = dirEntry.path() / "boat.ini";
        if (!fs::exists(boatFile)) continue;

        ifstream file(boatFile);
        if (!file.is_open()) continue;

        Json::Value root;
        file >> root;

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

        // Views
        b.viewCount = 0;
        for (const auto& view : root["View"]) {
            if (b.viewCount >= MAX_VIEWS) break;
            for (int i = 0; i < 4; ++i) {
                b.views[b.viewCount][i] = i < view.size() ? view[i].asFloat() : 0.0f;
            }
            b.viewCount++;
        }

        // RadarScreen
        if (root.isMember("RadarScreen") && root["RadarScreen"]["vector"].size() == 3) {
            b.radarScreen.x = root["RadarScreen"]["vector"][0].asFloat();
            b.radarScreen.y = root["RadarScreen"]["vector"][1].asFloat();
            b.radarScreen.z = root["RadarScreen"]["vector"][2].asFloat();
            b.radarScreen.size = root["RadarScreen"]["size"].asFloat();
            b.radarScreen.tilt = root["RadarScreen"]["tilt"].asFloat();
            b.hasRadarScreen = true;
        } else {
            b.hasRadarScreen = false;
        }

        for (int i = 0; i < 3; ++i) {
            b.portThrottle[i] = root["PortThrottle"][i].asFloat();
            b.stbdThrottle[i] = root["StbdThrottle"][i].asFloat();
        }

        // Dynamics
        if (root.isMember("Dynamics")) {
            for (int i = 0; i < 2; ++i) {
                b.dynamics.speed[i] = root["Dynamics"]["speed"][i].asFloat();
                b.dynamics.turnDrag[i] = root["Dynamics"]["turnDrag"][i].asFloat();
                b.dynamics.lateralDrag[i] = root["Dynamics"]["lateralDrag"][i].asFloat();
            }
            b.hasDynamics = true;
        } else {
            b.hasDynamics = false;
        }

        b.maxPropulsionForce = root.get("Max_propulsion_force", 0.0).asFloat();
        b.asternEfficiency = root.get("AsternEfficiency", 1.0).asFloat();
        b.blockCoefficient = root.get("BlockCoefficient", 0.0).asFloat();
        b.mass = root.get("Mass", 0.0).asFloat();
        b.inertia = root.get("Inertia", 0.0).asFloat();

        // Prop
        if (root.isMember("Prop")) {
            b.prop.space = root["Prop"]["space"].asFloat();
            b.prop.walkAhead = root["Prop"]["walkAhead"].asFloat();
            b.prop.walkAstern = root["Prop"]["walkAstern"].asFloat();
            b.prop.walkDriftEffect = root["Prop"]["walkDriftEffect"].asFloat();
            b.hasProp = true;
        } else {
            b.hasProp = false;
        }

        // AzimuthDrive
        if (root.isMember("AzimuthDrive")) {
            const auto& ad = root["AzimuthDrive"];
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
            b.hasAzimuthDrive = true;
        } else {
            b.hasAzimuthDrive = false;
        }

        // Rudder
        if (root.isMember("Rudder")) {
            b.rudder.A = root["Rudder"]["A"].asFloat();
            b.rudder.B = root["Rudder"]["B"].asFloat();
            b.rudder.BAstern = root["Rudder"]["BAstern"].asFloat();
            b.hasRudder = true;
        } else {
            b.hasRudder = false;
        }

        b.buffet = root.get("Buffet", 0.0).asFloat();
        b.swell = root.get("Swell", 0.0).asFloat();
        b.windage = root.get("Windage", 0.0).asFloat();
        b.windageTurnEffect = root.get("WindageTurnEffect", 0.0).asFloat();
        b.deviationMaximum = root.get("DeviationMaximum", 0.0).asFloat();
        b.deviationMaximumHeading = root.get("DeviationMaximumHeading", 0.0).asFloat();
        b.rollPeriod = root.get("RollPeriod", 0.0).asFloat();
        b.pitchPeriod = root.get("PitchPeriod", 0.0).asFloat();
        b.maxRevs = root.get("MaxRevs", 0).asInt();
        b.maxSpeedAhead = root.get("MaxSpeedAhead", 0.0).asFloat();
        b.centrifugalDriftEffect = root.get("centrifugalDriftEffect", 0.0).asFloat();
        b.hasRateOfTurnIndicator = root.get("HasRateOfTurnIndicator", false).asBool();

        // BowThruster
        if (root.isMember("BowThruster")) {
            b.bowThruster.Force = root["BowThruster"]["Force"].asFloat();
            b.bowThruster.Distance = root["BowThruster"]["Distance"].asFloat();
            b.hasBowThruster = true;
        } else {
            b.hasBowThruster = false;
        }

        // SternThruster
        if (root.isMember("SternThruster")) {
            b.sternThruster.Force = root["SternThruster"]["Force"].asFloat();
            b.sternThruster.Distance = root["SternThruster"]["Distance"].asFloat();
            b.hasSternThruster = true;
        } else {
            b.hasSternThruster = false;
        }

        // Wheel
        if (root.isMember("Wheel") && root["Wheel"]["vector"].size() == 3) {
            b.wheel.x = root["Wheel"]["vector"][0].asFloat();
            b.wheel.y = root["Wheel"]["vector"][1].asFloat();
            b.wheel.z = root["Wheel"]["vector"][2].asFloat();
            b.wheel.scale = root["Wheel"]["scale"].asFloat();
            b.hasWheel = true;
        } else {
            b.hasWheel = false;
        }

        // Sails
        b.hasSails = false;
        b.sails.sailCount = 0;
        if (root.isMember("Sails")) {
            const auto& sailsList = root["Sails"]["list"];
            for (const auto& sail : sailsList) {
                if (b.sails.sailCount >= MAX_SAILS || sail.size() < 3) break;
                b.sails.list[b.sails.sailCount][0] = sail[0].asFloat();
                b.sails.list[b.sails.sailCount][1] = sail[1].asFloat();
                b.sails.list[b.sails.sailCount][2] = sail[2].asFloat();
                b.sails.sailCount++;
            }
            b.sails.type = root["Sails"]["type"].asString();
            b.sails.size = root["Sails"]["size"].asString();
            b.hasSails = true;
        }

        // Pano
        b.hasPano = false;
        b.pano.panoCount = 0;
        if (root.isMember("Pano")) {
            const auto& files = root["Pano"]["file"];
            const auto& yaws = root["Pano"]["yaw"];
            const auto& pitches = root["Pano"]["pitch"];
            const auto& rolls = root["Pano"]["roll"];

            int count = std::min({ files.size(), yaws.size(), pitches.size(), rolls.size(), MAX_PANOS });
            for (int i = 0; i < count; ++i) {
                b.pano.file[i] = files[i].asString();
                b.pano.yaw[i] = yaws[i].asFloat();
                b.pano.pitch[i] = pitches[i].asFloat();
                b.pano.roll[i] = rolls[i].asFloat();
            }
            b.pano.panoCount = count;
            b.hasPano = true;
        }

        // Ajout final du bateau à la liste
        boats.push_back(b);
    }

    return boats;
}