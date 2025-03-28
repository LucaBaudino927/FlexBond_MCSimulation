#include "MySteppingAction.hh"

// ######## Costructor 
MySteppingAction::MySteppingAction(MyEventAction *eventAction){ fEventAction = eventAction; }

// ######## Destructor 
MySteppingAction::~MySteppingAction(){}

// ######## Step by step get the energy deposition and add it to the total deposit
void MySteppingAction::UserSteppingAction(const G4Step *step){   

	//G4cout << "---MySteppingAction---" << G4endl;
        G4LogicalVolume * volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        const MyDetectorConstruction *detectorConstruction = 
        		static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        		
        //Defined in MyDetectorConstruction.hh. It is the volume where you want to save the energy
        G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
        G4double edep = step->GetTotalEnergyDeposit();
        //AddEdep from MyEventAction.hh. It add every step the energy deposition. The total energy is in MyEventAction.cc.
        fEventAction->AddEdep(edep);
        if(volume != fScoringVolume){
        	return;
        }

}
