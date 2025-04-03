#include "StaticInfo.hh"

std::vector<G4ThreeVector> StaticInfo::alpidePadCoordinates;
G4int StaticInfo::NOfSensitiveDetector = 0;
G4int StaticInfo::NOfAlpidePads = 0;
std::map<G4String, G4bool> StaticInfo::detectorConstructionFlags;

StaticInfo::StaticInfo() {
	NOfSensitiveDetector = 0;
	NOfAlpidePads = 0;
};

StaticInfo::~StaticInfo() {
	Clear();
};

void StaticInfo::Clear() {
	alpidePadCoordinates.clear();
	NOfSensitiveDetector = 0;
	detectorConstructionFlags.clear();
	NOfAlpidePads = 0;
};
