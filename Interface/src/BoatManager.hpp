#pragma once
#include <string>
#include <vector>

constexpr int MAX_VIEWS = 6;
constexpr int MAX_SAILS = 10;
constexpr int MAX_PANOS = 6;

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
    float A;
    float B;
    float BAstern;
};

struct Thruster {
    float Force;
    float Distance;
};

struct Wheel {
    float x, y, z;
    float scale;
};

struct Sails {
    float list[MAX_SAILS][3];
    int sailCount;
    std::string type;
    std::string size;
};

struct Pano {
    std::string file[MAX_PANOS];
    float yaw[MAX_PANOS];
    float pitch[MAX_PANOS];
    float roll[MAX_PANOS];
    int panoCount;
};

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

    float views[MAX_VIEWS][4];
    int viewCount;

    RadarScreen radarScreen;
    bool hasRadarScreen;

    float portThrottle[3];
    float stbdThrottle[3];

    Dynamics dynamics;
    bool hasDynamics;

    float maxPropulsionForce;
    float asternEfficiency;
    float blockCoefficient;
    float mass;
    float inertia;

    Prop prop;
    bool hasProp;

    AzimuthDrive azimuthDrive;
    bool hasAzimuthDrive;

    Rudder rudder;
    bool hasRudder;

    float buffet;
    float swell;
    float windage;
    float windageTurnEffect;
    float deviationMaximum;
    float deviationMaximumHeading;
    float rollPeriod;
    float pitchPeriod;
    int maxRevs;
    float maxSpeedAhead;
    float centrifugalDriftEffect;
    bool hasRateOfTurnIndicator;

    Thruster bowThruster;
    bool hasBowThruster;

    Thruster sternThruster;
    bool hasSternThruster;

    Wheel wheel;
    bool hasWheel;

    Sails sails;
    bool hasSails;

    Pano pano;
    bool hasPano;
};

class BoatManager {
public:
    std::vector<Boat> loadBoats(const std::string& folderPath);
};