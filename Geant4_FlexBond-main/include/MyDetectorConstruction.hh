#ifndef MY_DETECTOR_CONSTRUCTION_HH
#define MY_DETECTOR_CONSTRUCTION_HH
#include "G4SystemOfUnits.hh"
#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4GenericMessenger.hh"
#include "G4Tubs.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4MTRunManager.hh"

//User definted
#include "MySensitiveDetector.hh"
#include "Glue.hh"
#include "Alpide.hh"
#include "Kapton.hh"
#include "Copper.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
    public:

        MyDetectorConstruction();
        ~MyDetectorConstruction();
        G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }//energy deposit
        virtual G4VPhysicalVolume *Construct();
        void ConstructCherenkov();
        void ConstructScintillator();
        void ConstructTOF();
        void ConstructAtmosphere();
        void ConstructMapsFoil();

    private:
    
        virtual void ConstructSDandField();
        void DefineMaterials();
        G4double AlTck,SiTck,KaTck,PlaneDistance;
        G4int nCols,nRows,nPlanes;
        G4double xWorld, yWorld, zWorld;
        G4bool isCherenkov, isScintillator, isTOF, isAtmosphere, isMapsFoil;
        G4Box *solidWorld, *solidRadiator, *solidRadiator2, *solidDetector, *solidScintillator, *solidAtmosphere;
        G4LogicalVolume  *logicWorld, *logicRadiator, *logicRadiator2, *logicDetector, *logicScintillator, *logicAtmosphere[10];
        G4VPhysicalVolume  *physWorld, *physRadiator, *physRadiator2, *physDetector, *physScintillator, *physAtmosphere[10];
        G4OpticalSurface *mirrorSurface;
        G4GenericMessenger *fMessenger;
        G4LogicalVolume *fScoringVolume;
        G4Material *SiO2, *H2O, *Aerogel, *worldMat, *NaI, *Air[10], *KaptonMaterial, *Si, *Al, *epoxyGlue;
        G4Element *C, *Na, *I, *N, *O, *H;
        G4bool materialsDefined = false;
        G4bool reinitialize = false;
        MySensitiveDetector* sensDet;

};

#endif
