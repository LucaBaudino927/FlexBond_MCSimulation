#include "MyEventAction.hh"

using std::array;

// ######## Constructor
MyEventAction::MyEventAction(){ 
	// set printing per each event
	G4RunManager::GetRunManager()->SetPrintProgress(1);
	fHitCollID.fill(-1);
	fDetEdep.fill(std::vector<G4double>(NofMySensitiveDetector, 0.));
}

// ######## Initialization of fEdep to 0 at the beginning of the event
void MyEventAction::BeginOfEventAction(const G4Event*){ 
	
	/*
	fEdep = 0.;
	auto analysisManager = G4AnalysisManager::Instance();
	if(fHitCollID[0] < 0){
		auto sdManager = G4SDManager::GetSDMpointer();	
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
	}*/
	
	
	if (fHitCollID[0] < 0) {
	
		//G4cout << "---BeginOfEventAction---1---" << G4endl;
		auto sdManager = G4SDManager::GetSDMpointer();
		auto analysisManager = G4AnalysisManager::Instance();

		// hits collections names
		array<G4String, NofMySensitiveDetector> detHCName = {{ "Alpide/MySensitiveDetectorColl", 
								       "logicPad1_0/MySensitiveDetectorColl", 
								       "logicPad2_0/MySensitiveDetectorColl",
								       "LowerGlue/MySensitiveDetectorColl",
								       "UpperGlue/MySensitiveDetectorColl",
								       "LowerKapton/MySensitiveDetectorColl",
								       "UpperKapton/MySensitiveDetectorColl",
								       "CopperLayer/MySensitiveDetectorColl",
								       "logicSolderBall_0/MySensitiveDetectorColl"	}};

		for (G4int iDet = 0; iDet < NofMySensitiveDetector; ++iDet) {
			// hit collections IDs
			fHitCollID[iDet] = sdManager->GetCollectionID(detHCName[iDet]);
		}
    
  	}
	
	
}

// ####### Storing of fEdep at the end of the event 
void MyEventAction::EndOfEventAction(const G4Event* anEvent){
	
	/*G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
	G4HCofThisEvent* hitsCollections = anEvent->GetHCofThisEvent();	
	for (G4int iDet = 0; iDet < NofMySensitiveDetector; ++iDet) {
		MySensitiveDetectorHitsCollection* hitCollection 
			= static_cast<MySensitiveDetectorHitsCollection*>(hitsCollections->GetHC(fHitCollID[iDet]));
		//G4cout << "---fHitCollID["<<iDet<<"]" << " = " << fHitCollID[iDet] <<G4endl;
		//G4cout << "---fHitCollID.size(): " << fHitCollID.size() << G4endl;
		if (!hitCollection) return;
		for(unsigned int i = 0; i < hitCollection->GetSize(); ++i){
			MySensitiveDetectorHit* aHit = static_cast<MySensitiveDetectorHit*> (hitCollection->GetHit(i));
			if (!aHit) continue;
			aHit->Print();
			//TH1
			//G4cout<< "---fMySensitiveDetectorHistoID["<<iDet<<"][0] = "<<fMySensitiveDetectorHistoID[iDet][0]<<G4endl;
			//G4cout<< "---fMySensitiveDetectorHistoID["<<iDet<<"][1] = "<<fMySensitiveDetectorHistoID[iDet][1]<<G4endl;
			//G4cout<< "---fMySensitiveDetectorHistoID["<<iDet<<"][2] = "<<fMySensitiveDetectorHistoID[iDet][2]<<G4endl;
			//analysisManager->FillH1(fMySensitiveDetectorHistoID[iDet][0], aHit->GetTime());
			analysisManager->FillH1(fMySensitiveDetectorHistoID[iDet][1], aHit->GetPos().z());
			analysisManager->FillH1(fMySensitiveDetectorHistoID[iDet][2], aHit->GetEdep());
			//TH2
			//analysisManager->FillH2(fH2ID[0], aHit->GetPos().x(), aHit->GetPos().y());
		}
		
	}*/
	

	// Get analysis manager
	auto analysisManager = G4AnalysisManager::Instance();

	// MySensitiveDetector hits
	array<G4int, NofMySensitiveDetector> totalDetHit;
	totalDetHit.fill(0);
	array<G4double, NofMySensitiveDetector> totalDetEdep;
	totalDetEdep.fill(0.);

	for (G4int iDet = 0; iDet < NofMySensitiveDetector; ++iDet) {
		auto hc = GetHC(anEvent, fHitCollID[iDet]);
		if (!hc) return;

		totalDetHit[iDet] = 0;
		totalDetEdep[iDet] = 0.;
		for (unsigned long i = 0; i < hc->GetSize(); ++i) {
			G4double edep = 0.;
			// The EM and Had calorimeter hits are of different types
			auto hit = static_cast<MySensitiveDetectorHit*>(hc->GetHit(i));
			edep = hit->GetEdep();
			//G4cout << "---EndOfEventAction---0---Edep: " << edep/MeV << " MeV" << G4endl;
			if (edep > 0.) {
				totalDetHit[iDet]++;
				totalDetEdep[iDet] += edep;
			}
			fDetEdep[iDet][i] = edep;
		}
		// columns 2, 3
		analysisManager->FillNtupleDColumn(iDet, totalDetEdep[iDet]);
	}

	analysisManager->AddNtupleRow();
	
	//NB: fEdep che salvo nella Ntupla è l'energia totale depositata dall'EVENTO.
	//Se ho molti piani di detector e voglio sapere l'energia depositata in ogni piano devo cambiare la logica
	//G4cout << "Energy deposition: " << fEdep/MeV << " MeV" << G4endl;
	//G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
	//analysisManager->FillNtupleDColumn(1, 0, fEdep);
	//analysisManager->AddNtupleRow();
	
	auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
	if (printModulo == 0 || anEvent->GetEventID() % printModulo != 0) return;

	auto primary = anEvent->GetPrimaryVertex(0)->GetPrimary(0);
	G4cout << G4endl << ">>> Event " << anEvent->GetEventID() << " >>> Simulation truth : " << primary->GetG4code()->GetParticleName() << " "
															 << primary->GetMomentum() << G4endl;

	// MySensitiveDetector
	array<G4String, NofMySensitiveDetector> detName = {{ "Alpide", 
					   		     "logicPad1_0", 
					   		     "logicPad2_0",
					   		     "lowerGlue",
					   		     "upperGlue",
					   		     "lowerKapton",
					   		     "upperKapton",
					   		     "copperLayer",
					   		     "solderBall_0"	}};
	for (G4int iDet = 0; iDet < NofMySensitiveDetector; ++iDet) {
		G4cout << detName[iDet] << " has " << totalDetHit[iDet] << " hits." << " Total Edep is " << totalDetEdep[iDet] / MeV << " (MeV)" << G4endl;
	}

	
}


// Utility function which finds a hit collection with the given Id
// and print warnings if not found
G4VHitsCollection* MyEventAction::GetHC(const G4Event* event, G4int collId) {
	auto hce = event->GetHCofThisEvent();
	if (!hce) {
		G4ExceptionDescription msg;
		msg << "No hits collection of this event found." << G4endl;
		G4Exception("EventAction::EndOfEventAction()", "Code001", JustWarning, msg);
		return nullptr;
	}

	auto hc = hce->GetHC(collId);
	if (!hc) {
		G4ExceptionDescription msg;
		msg << "Hits collection " << collId << " of this event not found." << G4endl;
		G4Exception("EventAction::EndOfEventAction()", "Code001", JustWarning, msg);
	}
	return hc;
}
