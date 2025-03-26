#ifndef MY_EVENT_ACTION_HH
#define MY_EVENT_ACTION_HH

#include <vector>
#include <array>
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4THitsCollection.hh"
#include "MySensitiveDetectorHit.hh"
#include "G4RunManager.hh"
#include "G4HCtable.hh"

//User defined
#include "MyRunAction.hh"
#include "MapsFoilDetectorList.hh"


const G4int NofObservables = 3;
const G4int NofMySensitiveDetector = 6;

using namespace std;

class MyEventAction : public G4UserEventAction
{

public:

    MyEventAction(MyRunAction*);
    ~MyEventAction();
    virtual void BeginOfEventAction(const G4Event*) override;
    virtual void EndOfEventAction(const G4Event*) override;
    void AddEdep(G4double edep) { fEdep += edep; }//Add edep every step. It is called in MySteppingAction.cc
    
private:

    G4double fEdep;
    std::vector<G4int> fHitCollID = {-1};
    MyRunAction* fRunAction;
    array<array<G4int, NofMySensitiveDetector>, NofObservables> fMySensitiveDetectorHistoID;
    
};

#endif
