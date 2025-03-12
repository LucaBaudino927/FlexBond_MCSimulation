#ifndef MY_STEPPING_ACTION_HH
#define MY_STEPPING_ACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"

//User defined
#include "MyDetectorConstruction.hh"
#include "MyEventAction.hh"

class MySteppingAction : public G4UserSteppingAction
{
public:

    MySteppingAction(MyEventAction* eventAction);
    ~MySteppingAction();
    virtual void UserSteppingAction(const G4Step*);
    
private:
    MyEventAction *fEventAction;
};

#endif
