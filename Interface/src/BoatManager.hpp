#ifndef BOAT_MANAGER_H
#define BOAT_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <json/json.h>

// Structures dynamiques

/**
 * @brief permet de définir les vues
 */
struct View {
    float vector[3];
    bool elevated;
};

/**
 * @brief permet de définir les listes des vues
 */
struct ViewList {
    std::vector<View> views;
    void fromJson(const Json::Value& json);
};

/**
 * @brief permet de définir Sail
 */
struct Sail {
    float vector[3];
};

/**
 * @brief permet de définir les listes de Sail
 */
struct SailList {
    std::vector<Sail> sails;
    std::string type;
    std::string size;
    void fromJson(const Json::Value& json);
};

/**
 * @brief permet de définir les listes Pano
 */
struct PanoList {
    std::vector<std::string> file;
    std::vector<float> yaw, pitch, roll;
    void fromJson(const Json::Value& json);
};

// Structures simples

/**
 * @brief permet de définir RadarScreen
 */
struct RadarScreen {
    float vector[3];
    float size;
    float tilt;
};

/**
 * @brief permet de définir Dynamics
 */
struct Dynamics {
    float speed[2];
    float turnDrag[2];
    float lateralDrag[2];
};

/**
 * @brief permet de définir Prop
 */
struct Prop {
    float space;
    float walkAhead;
    float walkAstern;
    float walkDriftEffect;
};

/**
 * @brief permet de définir AzimuthDrive
 */
struct AzimuthDrive {
    bool azimuthDrive;
    bool astern;
    float aziToLengthRatio;
    int engineIdleRPM;
    int clutchEngageRPM;
    int clutchDisengageRPM;
    float engineMaxChangePerSecond;
    float maxDegPerSecond;
    float thrustLeverMaxChangePerSecond;
    float sameDirectionAsSchottel;
};

/**
 * @brief permet de définir Rudder
 */
struct Rudder {
    float A, B, BAstern;
};

/**
 * @brief permet de définir Thruster
 */
struct Thruster {
    float Force, Distance;
};

/**
 * @brief permet de définir Wheel
 */
struct Wheel {
    float vector[3];
    float scale;
};

// Classe principale

/**
 * @brief permet de définir la classe des bateaux
 * 
 * Cette dernière contient toutes les clés présentent dans les fichiers json et un nom pour l'affichage
 */
struct Boat {
    std::string displayName;
    std::string fileName;
    float scaleFactor;
    float yCorrection;
    int angleCorrection;
    float depth;
    bool hasGPS;
    bool hasDepthSounder;
    float maxDepth;
    bool makeTransparent;

    ViewList viewList;
    RadarScreen radarScreen;
    float portThrottle[3];
    float stbdThrottle[3];
    Dynamics dynamics;
    float maxPropulsionForce;
    float asternEfficiency;
    float blockCoefficient;
    float mass;
    float inertia;
    Prop prop;
    AzimuthDrive azimuthDrive;
    Rudder rudder;
    float buffet, swell, windage, windageTurnEffect;
    float deviationMaximum, deviationMaximumHeading;
    float rollPeriod, pitchPeriod;
    int maxRevs;
    float maxSpeedAhead;
    float centrifugalDriftEffect;
    bool hasRateOfTurnIndicator;
    Thruster bowThruster;
    Thruster sternThruster;
    Wheel wheel;
    SailList sails;
    PanoList pano;
    std::string filePath; // chemin complet du boat.json
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
    // Save a Boat into a new subfolder of folderPath. Returns true on success.
    bool saveBoat(const std::string& folderPath, Boat& b);
    // Rename a boat folder if the displayName has changed. Returns true on success.
    bool renameBoat(const std::string& folderPath, Boat& b);
};

#endif