#include "event.hh"

// ######## Cosntructor

    MyEventAction::MyEventAction(MyRunAction*)
    {
        fEdep = 0.;
    }

// ######## Destructor

    MyEventAction::~MyEventAction()
    {}

// ######## Initialization of fEdep to 0 at the beginning od the event

    void MyEventAction::BeginOfEventAction(const G4Event*)
        {
            fEdep = 0.;
        }

// ####### Storing of fEdep at the end of the event 

    void MyEventAction::EndOfEventAction(const G4Event*)
    {
        G4cout << "Energy deposition: " << fEdep << G4endl;
        G4AnalysisManager *man = G4AnalysisManager::Instance();
        man->FillNtupleDColumn(2, 0, fEdep);
        man->AddNtupleRow(2);
    }