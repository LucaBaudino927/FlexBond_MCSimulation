#ifndef MY_SENSITIVE_DETECTOR_HH
#define MY_SENSITIVE_DETECTOR_HH

#include <algorithm>
#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicsOrderedFreeVector.hh"
#include "G4SDManager.hh"
#include "globals.hh"

//User defined
#include "MySensitiveDetectorHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class MySensitiveDetector : public G4VSensitiveDetector
{

public:

    MySensitiveDetector(G4String name);
    ~MySensitiveDetector();
    
    //G4HCofThisEvent: hits container that contains hits collections
    virtual void Initialize(G4HCofThisEvent* hitsContainer);
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    virtual void clear();
    
private:
    
    //G4PhysicsOrderedFreeVector *quEff;
    MySensitiveDetectorHitsCollection *fHitsCollection = nullptr;
    G4int fHCID = -1;
    
};

#endif
