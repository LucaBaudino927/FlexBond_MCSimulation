#ifndef MY_DETECTOR_CONSTRUCTION_HH
#define MY_DETECTOR_CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include <iostream>
#include <vector>
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
#include "G4SDManager.hh"
#include "G4AssemblyVolume.hh"
#include "G4Threading.hh"

//User definted
#include "MySensitiveDetector.hh"
#include "Glue.hh"
#include "Alpide.hh"
#include "Kapton.hh"
#include "Copper.hh"
#include "SolderBall.hh"
#include "StaticInfo.hh"
#include "Constants.hh"

class G4FieldManager;
class G4VPhysicalVolume;
class G4GenericMessenger;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
    public:

        MyDetectorConstruction();
        ~MyDetectorConstruction() override;
        G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }//energy deposit
        G4VPhysicalVolume* Construct() override;
        void ConstructSDandField() override;
        

    private:
   
        void DefineMaterials();
        void ConstructCherenkov();
        void ConstructScintillator();
        void ConstructTOF();
        void ConstructAtmosphere();
        void ConstructMapsFoil();
        
        G4GenericMessenger *fMessenger = nullptr;
        G4double xWorld, yWorld, zWorld;
        G4Box *solidWorld;
        G4LogicalVolume *logicWorld;
        G4VPhysicalVolume  *physWorld;
        G4LogicalVolume *fScoringVolume;
        
        G4Material *worldMat, *KaptonMaterial, *Si, *Al, *epoxyGlue;
        G4Element *C, *Na, *I, *N, *O, *H;
        
        // G4GenericMessenger settings
        G4bool verboseDetConstr;
        //flags to declare the detector
        G4bool isMapsFoil;
        //flags to declare the setup of the detector
        G4bool constructEpoxyGlueLayer, constructKaptonLayer, constructCopperLayer, constructSolderBalls;
        //flags to tune the setup: if they are specified in the macro -> use those values otherwise use default values
        G4double alpideXFromMessenger 		= 0.;
        G4double alpideYFromMessenger 		= 0.;
        G4double alpideThicknessFromMessenger 	= 0.;
        G4double alpidePadRadiusFromMessenger 	= 0.;
        G4double glueThicknessFromMessenger 	= 0.;
        G4double kaptonThicknessFromMessenger 	= 0.;
        G4double copperThicknessFromMessenger 	= 0.;
        
        //Logical Volumes
        G4LogicalVolume *fLogicAlpide 		= nullptr;
        G4LogicalVolume *fLogicLowerGlue 	= nullptr;
        G4LogicalVolume *fLogicUpperGlue 	= nullptr;
        G4LogicalVolume *fLogicLowerKapton 	= nullptr;
        G4LogicalVolume *fLogicUpperKapton 	= nullptr;
        G4LogicalVolume *fLogicCopper		= nullptr;
        std::vector<G4LogicalVolume*> fLogicalAlpidePad1;
        std::vector<G4LogicalVolume*> fLogicalAlpidePad2;
        std::vector<G4LogicalVolume*> fLogicSolderBalls;
               

};

#endif
