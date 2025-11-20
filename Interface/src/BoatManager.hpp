#pragma once
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
class Boat {
public:
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

    std::unique_ptr<ViewList> viewList;
    std::unique_ptr<RadarScreen> radarScreen;
    float portThrottle[3];
    float stbdThrottle[3];
    std::unique_ptr<Dynamics> dynamics;
    float maxPropulsionForce;
    float asternEfficiency;
    float blockCoefficient;
    float mass;
    float inertia;
    std::unique_ptr<Prop> prop;
    std::unique_ptr<AzimuthDrive> azimuthDrive;
    std::unique_ptr<Rudder> rudder;
    float buffet, swell, windage, windageTurnEffect;
    float deviationMaximum, deviationMaximumHeading;
    float rollPeriod, pitchPeriod;
    int maxRevs;
    float maxSpeedAhead;
    float centrifugalDriftEffect;
    bool hasRateOfTurnIndicator;
    std::unique_ptr<Thruster> bowThruster;
    std::unique_ptr<Thruster> sternThruster;
    std::unique_ptr<Wheel> wheel;
    std::unique_ptr<SailList> sails;
    std::unique_ptr<PanoList> pano;
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
};