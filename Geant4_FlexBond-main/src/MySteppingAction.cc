#include "MySteppingAction.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction) { fEventAction = eventAction; }

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step *step){

	// Add Step by step get the energy deposition and add it to the total deposit
	
	G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	
	
	
	
	//PCB energy deposition
	
	if(volume->GetName().substr(0,8).compare("LV_SOLID") != 0) { return; };
	G4double edep = step->GetTotalEnergyDeposit();
	fEventAction->AddEdep(edep);//AddEdep from event.hh. It add every step the energy deposition. The total energy is in event.cc.
        
}
