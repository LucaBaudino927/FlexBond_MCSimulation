#include "stepping.hh"

// ######## Costructor 

    MySteppingAction::MySteppingAction(MyEventAction *eventAction)
    {
        fEventAction = eventAction;
    }

// ######## Destructor 
    MySteppingAction::~MySteppingAction()
    {}

// ######## Step by step get the energy deposition and add it to the total deposit

    void MySteppingAction::UserSteppingAction(const G4Step *step){   

        G4LogicalVolume * volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());//construction.hh
        G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();//Defined in construction.hh. Is the volume where you want to save the energy. 
        G4double edep = step->GetTotalEnergyDeposit();
        fEventAction->AddEdep(edep);//AddEdep from event.hh. It add every step the energy deposition. The total energy is in event.cc.
        if(volume != fScoringVolume){return;};

    }