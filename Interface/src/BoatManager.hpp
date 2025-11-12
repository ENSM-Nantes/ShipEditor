#pragma once
#include <string>
#include <vector>

struct Boat {
    std::string fileName;
    double scaleFactor;
    double yCorrection;
    int angleCorrection;
    double depth;
    bool hasGPS;
    bool hasDepthSounder;
    double maxDepth;
    bool makeTransparent;
    double mass;
    double maxPropulsionForce;
    double asternEfficiency;
    double blockCoefficient;
    double buffet;
    double swell;
    double windage;
    double windageTurnEffect;
    std::string displayName; // Nom affiché dans l’interface
};

class BoatManager {
public:
    std::vector<Boat> loadBoats(const std::string& folderPath);
};