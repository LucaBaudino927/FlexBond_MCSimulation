#ifndef MY_SENSITIVE_DETECTOR_HH
#define MY_SENSITIVE_DETECTOR_HH
#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicsOrderedFreeVector.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
    
private:
    //G4HCofThisEvent: hits container that contains hits collections
    //virtual void Initialize(G4HCofThisEvent* HitsContainer);
    //virtual void EndOfEvent(G4HCofThisEvent* HitsContainer);
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    
    G4PhysicsOrderedFreeVector *quEff;
    
};

#endif
