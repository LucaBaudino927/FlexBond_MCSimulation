#include "MyEventAction.hh"

using std::array;

// ######## Constructor
MyEventAction::MyEventAction(MyRunAction* myRunAction){ 
	// set printing per each event
	G4RunManager::GetRunManager()->SetPrintProgress(1);
	fEdep = 0.;
	fRunAction = myRunAction;
}

// ######## Destructor
MyEventAction::~MyEventAction(){}

// ######## Initialization of fEdep to 0 at the beginning of the event
void MyEventAction::BeginOfEventAction(const G4Event*){ 
	
	fEdep = 0.;
	if(fHitCollID[0] < 0){
		auto sdManager = G4SDManager::GetSDMpointer();
		auto analysisManager = G4AnalysisManager::Instance();		
		// hits collections ID
		G4cout << "------MapsFoilDetectorList::GetLogicalDetectorList().size(): " << MapsFoilDetectorList::GetLogicalDetectorList().size() << G4endl;
		for(int i = 0; i < MapsFoilDetectorList::GetLogicalDetectorList().size(); ++i){			  	 //nomeSD/nomeColl
			fHitCollID[i] = sdManager->GetCollectionID(MapsFoilDetectorList::GetLogicalDetectorList()[i]->GetName()+"/MySensitiveDetectorColl");
			G4cout << "Indexing collection ID: " << fHitCollID[i] << G4endl;
		}
	
		G4int count = 0;
		for(int i = 0; i < NofMySensitiveDetector; ++i){
			for(G4int j = 0; j < NofObservables; ++j){
				fMySensitiveDetectorHistoID[i][j] = analysisManager->GetH1Id(fRunAction->GetHistoNameByIndex(count));
				G4cout<< "---fRunAction->GetHistoNameByIndex("<<count<<") = "<<fRunAction->GetHistoNameByIndex(count)<<G4endl;
				count++;
			}
		}
	}
}

// ####### Storing of fEdep at the end of the event 
void MyEventAction::EndOfEventAction(const G4Event* anEvent){
	//NB: fEdep che salvo nella Ntupla è l'energia totale depositata dall'EVENTO.
	//Se ho molti piani di detector e voglio sapere l'energia depositata in ogni piano devo cambiare la logica
	G4cout << "Energy deposition: " << fEdep/MeV << " MeV" << G4endl;
	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
	analysisManager->FillNtupleDColumn(0, 0, fEdep);
	analysisManager->AddNtupleRow(0);
	
	G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
	G4HCofThisEvent* hitsCollections = anEvent->GetHCofThisEvent();	
	for (G4int iDet = 0; iDet < NofMySensitiveDetector; ++iDet) {
		MySensitiveDetectorHitsCollection* hitCollection 
			= static_cast<MySensitiveDetectorHitsCollection*>(hitsCollections->GetHC(fHitCollID[iDet]));
		G4cout << "---fHitCollID["<<iDet<<"]" << " = " << fHitCollID[iDet] <<G4endl;
		//G4cout << "---fHitCollID.size(): " << fHitCollID.size() << G4endl;
		if (!hitCollection) return;
		for(unsigned int i = 0; i < hitCollection->GetSize(); ++i){
			MySensitiveDetectorHit* aHit = static_cast<MySensitiveDetectorHit*> (hitCollection->GetHit(i));
			if (!aHit) continue;
			aHit->Print();
			//TH1
			G4cout<< "---fMySensitiveDetectorHistoID["<<iDet<<"][0] = "<<fMySensitiveDetectorHistoID[iDet][0]<<G4endl;
			G4cout<< "---fMySensitiveDetectorHistoID["<<iDet<<"][1] = "<<fMySensitiveDetectorHistoID[iDet][1]<<G4endl;
			G4cout<< "---fMySensitiveDetectorHistoID["<<iDet<<"][2] = "<<fMySensitiveDetectorHistoID[iDet][2]<<G4endl;
			//analysisManager->FillH1(fMySensitiveDetectorHistoID[iDet][0], aHit->GetTime());
			analysisManager->FillH1(fMySensitiveDetectorHistoID[iDet][1], aHit->GetPos().z());
			analysisManager->FillH1(fMySensitiveDetectorHistoID[iDet][2], aHit->GetEdep());
			//TH2
			//analysisManager->FillH2(fH2ID[0], aHit->GetPos().x(), aHit->GetPos().y());
		}
		
	}
	
}
