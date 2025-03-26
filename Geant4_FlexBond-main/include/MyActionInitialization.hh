#ifndef MY_ACTION_INITIALIZATION_HH
#define MY_ACTION_INITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "G4AnalysisManager.hh"

//User defined
#include "MyEventAction.hh"
#include "MySteppingAction.hh"
#include "MyPrimaryGenerator.hh"
#include "MyRunAction.hh"

class MyActionInitialization : public G4VUserActionInitialization
{

public:

    MyActionInitialization();
    ~MyActionInitialization();

    virtual void Build() const;
    virtual void BuildForMaster() const;
    
};

#endif
