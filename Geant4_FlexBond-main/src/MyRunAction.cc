#include "MyRunAction.hh"

// ######## Costructor
MyRunAction::MyRunAction(MyEventAction* eventAction) : fEventAction(eventAction) {

	//G4cout<<"---MyRunAction---"<<G4endl;
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetDefaultFileType("root");
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetNtupleMerging(true);
	//analysisManager->SetHistoDirectoryName("output");
	analysisManager->SetFileName("output");
	
	
	/***********************************************************************************************************************************
	 *	NofMySensitiveDetector = 6          se ho alpide, colla, kapton e rame							   *
	 *	NofMySensitiveDetector = 6+(#pad*2) se ho alpide, colla, kapton, rame e pad dell'alpide					   *
	 *	NofMySensitiveDetector = 6+(#pad*3) se ho alpide, colla, kapton, rame, pad dell'alpide e solder balls per ogni pad	   *
	 ***********************************************************************************************************************************/
	if (fEventAction) {
		analysisManager->CreateNtuple("MapsFoil", "Hits");
		analysisManager->CreateNtupleDColumn("AlpideEnergy");  					// column Id = 0
		//analysisManager->CreateNtupleDColumn("AlpidePad1Energy_0");  	// column Id: from 1 to 1 + (#pad - 1)*2
		//analysisManager->CreateNtupleDColumn("AlpidePad2Energy_0");  	// column Id: from 2 to 2 + (#pad - 1)*2
		for(G4int i = 0; i < StaticInfo::GetNOfAlpidePads(); i++){
			analysisManager->CreateNtupleDColumn("AlpidePad1Energy_"+std::to_string(i));  	// column Id: from 1 to 1 + (#pad - 1)*2
			analysisManager->CreateNtupleDColumn("AlpidePad2Energy_"+std::to_string(i));  	// column Id: from 2 to 2 + (#pad - 1)*2
		}
		analysisManager->CreateNtupleDColumn("LowerGlueEnergy");  				// column Id: from 3 to 3 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("UpperGlueEnergy");  				// column Id: from 4 to 4 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("LowerKaptonEnergy");  				// column Id: from 5 to 5 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("UpperKaptonEnergy");  				// column Id: from 6 to 6 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("CopperEnergy");  					// column Id: from 7 to 7 + (#pad - 1)*2
		//analysisManager->CreateNtupleDColumn("SolderBallEnergy_0");	// column Id: from 8 to 8 + (#pad - 1)*3  10,11
		for(G4int i = 0; i < StaticInfo::GetNOfAlpidePads(); i++){
			analysisManager->CreateNtupleDColumn("SolderBallEnergy_"+std::to_string(i));	// column Id: from 8 to 8 + (#pad - 1)*3  10,11
		}
		analysisManager->FinishNtuple(0);
		
		/*
		//Energy deposition for each event
		analysisManager->CreateNtuple("MapsFoil", "Scoring");
		analysisManager->CreateNtupleDColumn("fEdep");
		analysisManager->FinishNtuple(1);
		*/
	}

	// Set ntuple output file
	analysisManager->SetNtupleFileName(0, "outputNtuple");
	
	
	/*for(int i = 0; i < NofMySensitiveDetector; i++){
		//histograms
		analysisManager->CreateH1("Layer"+std::to_string(i)+", HitTime", "Hit Time", 10, 0.*ns, 1*ns, "ns");
		AddToHistoNames("Layer"+std::to_string(i)+", HitTime");
		analysisManager->CreateH1("Layer"+std::to_string(i)+", Hit_Z",   "Hit Z",    100, -250.*um, 250*um, "um");
		AddToHistoNames("Layer"+std::to_string(i)+", Hit_Z");
		analysisManager->CreateH1("Layer"+std::to_string(i)+", HitEdep", "Hit Deposited Energy", 50, 0.*keV, 200*keV, "keV");
		AddToHistoNames("Layer"+std::to_string(i)+", HitEdep");
		//analysisManager->CreateH2("Layer"+std::to_string(i)+", Hit_XY",  "Hit XY",   60, -30.*mm, 30.*mm, 30, -15.*mm, 15.*mm);
		//AddToHistoNames("Layer"+std::to_string(i)+", Hit_XY");
		
		//settings
		//analysisManager->SetH1Title(G4int id, const G4String& title);
		//analysisManager->SetH1XAxisTitle(0, "t [ns]");
		//analysisManager->SetH1YAxisTitle(0, "");

	}	
	*/
            
}


// ######## Begin of the run
void MyRunAction::BeginOfRunAction(const G4Run* run){

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
	// Reset histograms from previous run
	analysisManager->Reset();
  
	//G4int runID = run->GetRunID();  
	//std::stringstream strRunID;
	//strRunID << runID;
	//analysisManager->OpenFile("../output/output"+strRunID.str()+".root");
	analysisManager->OpenFile();

}

// ######## End of the run
void MyRunAction::EndOfRunAction(const G4Run*){

        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
        analysisManager->Write();
        analysisManager->CloseFile(false);

}


