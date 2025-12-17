#include "BoatManager.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <ctime>
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

vector<Boat> BoatManager::loadBoats() {
	vector<Boat> boats;

	for (const auto& dirEntry : fs::directory_iterator(transformationPath)) {
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
		}

		// RadarScreen
		if (root.isMember("RadarScreen") && root["RadarScreen"]["vector"].size() == 3) {
			b.radarScreen = RadarScreen();
			b.radarScreen.vector[0] = root["RadarScreen"]["vector"][0].asFloat(); //x
			b.radarScreen.vector[1] = root["RadarScreen"]["vector"][1].asFloat(); //y
			b.radarScreen.vector[2] = root["RadarScreen"]["vector"][2].asFloat(); //z
			b.radarScreen.size = root["RadarScreen"]["size"].asFloat();
			b.radarScreen.tilt = root["RadarScreen"]["tilt"].asFloat();
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
		}

		// Rudder
		if (root.isMember("Rudder")) {
			b.rudder = Rudder();
			b.rudder.A = root["Rudder"]["A"].asFloat();
			b.rudder.B = root["Rudder"]["B"].asFloat();
			b.rudder.BAstern = root["Rudder"]["BAstern"].asFloat();
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
		}

		// Stern Thruster
		if (root.isMember("SternThruster")) {
			b.sternThruster = Thruster();
			b.sternThruster.Force = root["SternThruster"]["Force"].asFloat();
			b.sternThruster.Distance = root["SternThruster"]["Distance"].asFloat();
		}

		// Wheel 
		if (root.isMember("Wheel") && root["Wheel"]["vector"].size() == 3) {
			b.wheel = Wheel();
			b.wheel.vector[0] = root["Wheel"]["vector"][0].asFloat();
			b.wheel.vector[1] = root["Wheel"]["vector"][1].asFloat();
			b.wheel.vector[2] = root["Wheel"]["vector"][2].asFloat();
			b.wheel.scale = root["Wheel"]["scale"].asFloat();
		}

		// Sails
		if (root.isMember("Sails")) {
			b.sails = SailList();
			b.sails.fromJson(root["Sails"]);
		}

		// Pano
		if (root.isMember("Pano")) {
			b.pano = PanoList();
			b.pano.fromJson(root["Pano"]);
		}

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
            item.append(v.elevated);
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

bool BoatManager::renameBoat(Boat& b) {
    try {
        namespace fs = std::filesystem;
        
        // Si pas de filePath, c'est un nouveau bateau, rien à renommer
        if (b.filePath.empty()) {
            return true;
        }
        
        // Extraire le nom actuel du dossier depuis filePath
        fs::path currentPath(b.filePath);
        fs::path currentDir = currentPath.parent_path();
        std::string currentFolderName = currentDir.filename().string();
        
        // Nettoyer le nouveau nom (remplacer espaces par underscores)
        std::string newName = b.displayName;
        for (auto &c : newName) {
            if (c == ' ') c = '_';
        }
        
        // Vérifier si le nom a changé
        if (currentFolderName == newName) {
            return true; // Pas de changement, rien à faire
        }
        
        // Construire le nouveau chemin
        fs::path parentPath = currentDir.parent_path();
        fs::path newDir = parentPath / newName;
        
        // Vérifier que le nouveau dossier n'existe pas déjà
        if (fs::exists(newDir)) {
            std::cerr << "Error: Folder " << newName << " already exists" << std::endl;
            return false;
        }
        
        // Renommer le dossier
        fs::rename(currentDir, newDir);
        
        // Mettre à jour le filePath du bateau
        b.filePath = (newDir / "boat.json").string();
        
        std::cout << "Boat folder renamed from " << currentFolderName << " to " << newName << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Exception in renameBoat: " << e.what() << std::endl;
        return false;
    }
}
