#include "MyEventAction.hh"
#include "G4SystemOfUnits.hh"

// ######## Cosntructor
MyEventAction::MyEventAction(MyRunAction*){ fEdep = 0.; }

// ######## Destructor
MyEventAction::~MyEventAction(){}

// ######## Initialization of fEdep to 0 at the beginning of the event
void MyEventAction::BeginOfEventAction(const G4Event*){ fEdep = 0.; }

// ####### Storing of fEdep at the end of the event 
void MyEventAction::EndOfEventAction(const G4Event*){
	//NB: fEdep che salvo nella Ntupla è l'energia totale depositata dall'EVENTO.
	//Se ho molti piani di detector e voglio sapere l'energia depositata in ogni piano devo cambiare la logica
	G4cout << "Energy deposition: " << fEdep/MeV << " MeV" << G4endl;
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleDColumn(2, 0, fEdep);
	man->AddNtupleRow(2);
}
