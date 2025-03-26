#include "MapsFoilDetectorList.hh"

std::vector<G4LogicalVolume*> MapsFoilDetectorList::mapsFoilLogicalDetectorList;

MapsFoilDetectorList::MapsFoilDetectorList() {
	if(mapsFoilLogicalDetectorList.empty()){
		mapsFoilLogicalDetectorList.reserve(30);
	}
};

MapsFoilDetectorList::~MapsFoilDetectorList() {};

std::vector<G4LogicalVolume*> MapsFoilDetectorList::GetLogicalDetectorList() { return mapsFoilLogicalDetectorList; };

void MapsFoilDetectorList::AddToLogicalDetectorList(G4LogicalVolume* logVolume) { mapsFoilLogicalDetectorList.push_back(logVolume); };

void MapsFoilDetectorList::ClearLogicalDetectorList() { mapsFoilLogicalDetectorList.clear(); };
