#include "BoatManager.hpp"
#include <fstream>
#include <filesystem>
#include <json/json.h>

using namespace std;

vector<Boat> BoatManager::loadBoats(const string& folderPath) {
    vector<Boat> boats;

    for (const auto& dirEntry : filesystem::directory_iterator(folderPath)) {
        if (!dirEntry.is_directory()) continue;

        filesystem::path boatFile = dirEntry.path() / "boat.ini";
        if (!filesystem::exists(boatFile)) continue;

        ifstream file(boatFile);
        if (!file.is_open()) continue;

        Json::Value root;
        file >> root;

        Boat b;
        b.fileName = root.get("FileName", "").asString();
        b.scaleFactor = root.get("ScaleFactor", 1.0).asDouble();
        b.yCorrection = root.get("YCorrection", 0.0).asDouble();
        b.angleCorrection = root.get("AngleCorrection", 0).asInt();
        b.depth = root.get("Depth", 0.0).asDouble();
        b.hasGPS = root.get("HasGPS", false).asBool();
        b.hasDepthSounder = root.get("HasDepthSounder", false).asBool();
        b.maxDepth = root.get("MaxDepth", 0.0).asDouble();
        b.makeTransparent = root.get("MakeTransparent", false).asBool();
        b.mass = root.get("Mass", 0.0).asDouble();
        b.maxPropulsionForce = root.get("Max_propulsion_force", 0.0).asDouble();
        b.asternEfficiency = root.get("AsternEfficiency", 0.0).asDouble();
        b.blockCoefficient = root.get("BlockCoefficient", 0.0).asDouble();
        b.buffet = root.get("Buffet", 0.0).asDouble();
        b.swell = root.get("Swell", 0.0).asDouble();
        b.windage = root.get("Windage", 0.0).asDouble();
        b.windageTurnEffect = root.get("WindageTurnEffect", 0.0).asDouble();

        // Nom affiché = nom du dossier
        b.displayName = dirEntry.path().filename().string();

        boats.push_back(b);
    }

    return boats;
}