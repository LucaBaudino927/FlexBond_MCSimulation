#ifndef MY_EVENT_ACTION_HH
#define MY_EVENT_ACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

//User defined
#include "MyRunAction.hh"

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(MyRunAction*);
    ~MyEventAction();
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    void AddEdep(G4double edep) { fEdep += edep; }//Add edep every step. It is called in MySteppingAction.cc
    
private:
    G4double fEdep;
};

#endif
