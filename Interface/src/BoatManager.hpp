#pragma once
#include <string>
#include <vector>
#include <memory>
#include <json/json.h>

// Classes dynamiques

struct View {
    float x, y, z;
    bool elevated;
};

struct ViewList {
    std::vector<View> views;
    void fromJson(const Json::Value& json);
};

struct Sail {
    float x, y, z;
};

struct SailList {
    std::vector<Sail> sails;
    std::string type;
    std::string size;
    void fromJson(const Json::Value& json);
};

struct PanoList {
    std::vector<std::string> file;
    std::vector<float> yaw, pitch, roll;
    void fromJson(const Json::Value& json);
};

// Structures simples

struct RadarScreen {
    float x, y, z;
    float size;
    float tilt;
};

struct Dynamics {
    float speed[2];
    float turnDrag[2];
    float lateralDrag[2];
};

struct Prop {
    float space;
    float walkAhead;
    float walkAstern;
    float walkDriftEffect;
};

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

struct Rudder {
    float A, B, BAstern;
};

struct Thruster {
    float Force, Distance;
};

struct Wheel {
    float x, y, z;
    float scale;
};

// Classe principale

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

class BoatManager {
public:
    std::vector<Boat> loadBoats(const std::string& folderPath);
};