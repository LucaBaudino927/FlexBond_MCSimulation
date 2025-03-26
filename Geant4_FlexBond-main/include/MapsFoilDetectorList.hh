#ifndef MAPS_FOIL_DETECTOR_LIST_HH
#define MAPS_FOIL_DETECTOR_LIST_HH

#include <iostream>
#include <vector>
#include "G4LogicalVolume.hh"

class MapsFoilDetectorList
{
    public:

        MapsFoilDetectorList();
        ~MapsFoilDetectorList();
        static std::vector<G4LogicalVolume*> GetLogicalDetectorList();
        static void AddToLogicalDetectorList(G4LogicalVolume*);
        static void ClearLogicalDetectorList();

    private:
    
        static std::vector<G4LogicalVolume*> mapsFoilLogicalDetectorList;

};

#endif
