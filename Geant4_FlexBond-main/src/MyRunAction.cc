#include "MyRunAction.hh"

// ######## Costructor
MyRunAction::MyRunAction() {

	//G4cout<<"---MyRunAction---"<<G4endl;
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	//analysisManager->SetDefaultFileType("root");
	//analysisManager->SetVerboseLevel(1);
	analysisManager->SetNtupleMerging(true);
	//analysisManager->SetNtupleDirectoryName("output");
	//analysisManager->SetHistoDirectoryName("output");
	//analysisManager->SetFileName("output");
	
	
	/***********************************************************************************************************************************
	 *	NofMySensitiveDetector = 6          se ho alpide, colla, kapton e rame							   *
	 *	NofMySensitiveDetector = 6+(#pad*2) se ho alpide, colla, kapton, rame e pad dell'alpide					   *
	 *	NofMySensitiveDetector = 6+(#pad*3) se ho alpide, colla, kapton, rame, pad dell'alpide e solder balls per ogni pad	   *
	 *	NofMySensitiveDetector = 9+(#pad*3) se ho alpide, colla, kapton, rame, pad dell'alpide, solder balls per ogni pad e PCB	   *
	 ***********************************************************************************************************************************/
	/*
	if(!StaticInfo::GetIsFirstRunMangerInitialization()){
		analysisManager->CreateNtuple("MapsFoil", "Hits");
		analysisManager->CreateNtupleDColumn("AlpideEnergy");  					// column Id = 0
		for(G4int i = 0; i < NofPads; i++){
			analysisManager->CreateNtupleDColumn("AlpidePad1Energy_"+std::to_string(i));  	// column Id: from 1 to 1 + (#pad - 1)*2
			analysisManager->CreateNtupleDColumn("AlpidePad2Energy_"+std::to_string(i));  	// column Id: from 2 to 2 + (#pad - 1)*2
		}
		analysisManager->CreateNtupleDColumn("LowerGlueEnergy");  				// column Id: from 3 to 3 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("UpperGlueEnergy");  				// column Id: from 4 to 4 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("LowerKaptonEnergy");  				// column Id: from 5 to 5 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("UpperKaptonEnergy");  				// column Id: from 6 to 6 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("CopperEnergy");  					// column Id: from 7 to 7 + (#pad - 1)*2
		for(G4int i = 0; i < NofPads; i++){
			analysisManager->CreateNtupleDColumn("SolderBallEnergy_"+std::to_string(i));	// column Id: from 8 to 8 + (#pad - 1)*3
		}
		analysisManager->FinishNtuple(0);		
		
		//Energy deposition for each event
		analysisManager->CreateNtuple("PCB", "PCB_Hits");
		analysisManager->CreateNtupleDColumn("fPCBedep");
		analysisManager->FinishNtuple(1);
		
		//Scattering angle in each volume of the maps foil
		analysisManager->CreateNtuple("MapsFoil", "ScatteringAngles");
		analysisManager->CreateNtupleDColumn("Alpide");
		analysisManager->CreateNtupleDColumn("LowerGlue");
		analysisManager->CreateNtupleDColumn("UpperGlue");
		analysisManager->CreateNtupleDColumn("LowerKapton");
		analysisManager->CreateNtupleDColumn("UpperKapton");
		analysisManager->CreateNtupleDColumn("Copper");
		analysisManager->FinishNtuple(2);
	}
	*/
	
	/*
	G4cout << "---MyRunAction---StaticInfo::GetIsFirstRunMangerInitialization(): " << StaticInfo::GetIsFirstRunMangerInitialization() << G4endl;
	
	if(!StaticInfo::GetIsFirstRunMangerInitialization()){
		G4cout << "---MyRunAction---0---" << G4endl;
		analysisManager->CreateNtuple("MapsFoil", "Hits");
		analysisManager->CreateNtupleDColumn("AlpideEnergy");  					// column Id = 0
		for(G4int i = 0; i < NofPads; i++){
			analysisManager->CreateNtupleDColumn("AlpidePad1Energy_"+std::to_string(i));  	// column Id: from 1 to 1 + (#pad - 1)*2
			analysisManager->CreateNtupleDColumn("AlpidePad2Energy_"+std::to_string(i));  	// column Id: from 2 to 2 + (#pad - 1)*2
		}
		if(StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) {
			analysisManager->CreateNtupleDColumn("LowerGlueEnergy");  				// column Id: from 3 to 3 + (#pad - 1)*2
			analysisManager->CreateNtupleDColumn("UpperGlueEnergy");  				// column Id: from 4 to 4 + (#pad - 1)*2
		}
		if(StaticInfo::GetDetectorFlag("constructKaptonLayer")) {
			analysisManager->CreateNtupleDColumn("LowerKaptonEnergy");  				// column Id: from 5 to 5 + (#pad - 1)*2
			analysisManager->CreateNtupleDColumn("UpperKaptonEnergy");  				// column Id: from 6 to 6 + (#pad - 1)*2
		}
		if(StaticInfo::GetDetectorFlag("constructCopperLayer")) {
			analysisManager->CreateNtupleDColumn("CopperEnergy");  					// column Id: from 7 to 7 + (#pad - 1)*2
		}
		if(StaticInfo::GetDetectorFlag("constructSolderBalls")) {
			for(G4int i = 0; i < NofPads; i++){
				analysisManager->CreateNtupleDColumn("SolderBallEnergy_"+std::to_string(i));	// column Id: from 8 to 8 + (#pad - 1)*3
			}
		}
		analysisManager->FinishNtuple(0);		
		
		//Energy deposition for each event
		analysisManager->CreateNtuple("PCB", "PCB_Hits");
		if(StaticInfo::GetDetectorFlag("constructPCB")) { 
			analysisManager->CreateNtupleDColumn("fPCBedep");
		}
		analysisManager->FinishNtuple(1);
		
		//Scattering angle in each volume of the maps foil
		analysisManager->CreateNtuple("MapsFoil", "ScatteringAngles");
		analysisManager->CreateNtupleDColumn("Alpide");
		if(StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) analysisManager->CreateNtupleDColumn("LowerGlue");
		if(StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) analysisManager->CreateNtupleDColumn("UpperGlue");
		if(StaticInfo::GetDetectorFlag("constructKaptonLayer")) analysisManager->CreateNtupleDColumn("LowerKapton");
		if(StaticInfo::GetDetectorFlag("constructKaptonLayer")) analysisManager->CreateNtupleDColumn("UpperKapton");
		if(StaticInfo::GetDetectorFlag("constructCopperLayer")) analysisManager->CreateNtupleDColumn("Copper");
		analysisManager->FinishNtuple(2);
	}
	*/
	
	// Set ntuple output file
	//analysisManager->SetNtupleFileName(0, "outputNtuple");
	//analysisManager->SetNtupleFileName(1, "outputNtuple");
	
	
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
	
	//----------------------------------------------------------------------------------------------------------------
	// Ad ogni Run reinizializzo l'analisysManager in modo
	// che, se reinizializzo la geometria e modifico il 
	// numero di detector, posso modificare anche il numero di ntuple
	analysisManager->Clear();
	
	//----------------------------------------------------------------------------------------------------------------
	// Apro i file di output assegnando un nome in base al RunID.
	// NB: Il main analysis file viene creato nel master e i file contenenti i dati vengono creati per ogni thread.
	//     In generale il RunID del Master Thread è diverso dal RunID dei vari thread, quindi devo salvare il RunID
	//     del master per fare in modo che i vari thread creino i loro file con lo stesso nome altrimenti non 
	//     funziona il merging delle ntuple.
	//     Es: Master thread con RunID = 0 crea output0.root, thread con RunID = X deve creare un output0_tX.root per funzionare correttamente
	std::stringstream strRunID;
	if(IsMaster()) {
		StaticInfo::SetRunIdOnMasterThread(run->GetRunID());
	}
	strRunID << StaticInfo::GetRunIdOnMasterThread();
	//G4cout<<"---MyRunAction---run->GetRunID(): "<<run->GetRunID()<<G4endl;
	//G4cout<<"---MyRunAction---StaticInfo::GetRunIdOnMasterThread(): "<<StaticInfo::GetRunIdOnMasterThread()<<G4endl;
	
	analysisManager->SetFileName("output"+strRunID.str()+".root");
	analysisManager->SetNtupleFileName("output"+strRunID.str()+".root");
	
	// Reset histograms from previous run
	analysisManager->Reset();
	
	analysisManager->OpenFile("output"+strRunID.str()+".root");	
	
	//----------------------------------------------------------------------------------------------------------------
	// Creo le ntuple in base alle flag di costruzione dei detector 
	// inizializzate in MyDetectorConstruction (e prese dal file di configurazione)
	analysisManager->CreateNtuple("MapsFoil_Hits", "Hits");
	analysisManager->CreateNtupleDColumn("AlpideEnergy");  						// column Id = 0
	if(StaticInfo::GetDetectorFlag("constructAlpidePads")) {
		for(G4int i = 0; i < NofPads; i++){
			analysisManager->CreateNtupleDColumn("AlpidePad1Energy_"+std::to_string(i));  	// column Id: from 1 to 1 + (#pad - 1)*2
			analysisManager->CreateNtupleDColumn("AlpidePad2Energy_"+std::to_string(i));  	// column Id: from 2 to 2 + (#pad - 1)*2
		}
	}
	if(StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) {
		analysisManager->CreateNtupleDColumn("LowerGlueEnergy");  				// column Id: from 3 to 3 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("UpperGlueEnergy");  				// column Id: from 4 to 4 + (#pad - 1)*2
	}
	if(StaticInfo::GetDetectorFlag("constructKaptonLayer")) {
		analysisManager->CreateNtupleDColumn("LowerKaptonEnergy");  				// column Id: from 5 to 5 + (#pad - 1)*2
		analysisManager->CreateNtupleDColumn("UpperKaptonEnergy");  				// column Id: from 6 to 6 + (#pad - 1)*2
	}
	if(StaticInfo::GetDetectorFlag("constructCopperLayer")) {
		analysisManager->CreateNtupleDColumn("CopperEnergy");  					// column Id: from 7 to 7 + (#pad - 1)*2
	}
	if(StaticInfo::GetDetectorFlag("constructSolderBalls")) {
		for(G4int i = 0; i < NofPads; i++){
			analysisManager->CreateNtupleDColumn("SolderBallEnergy_"+std::to_string(i));	// column Id: from 8 to 8 + (#pad - 1)*3
		}
	}
	analysisManager->FinishNtuple(0);
	
	//Energy deposition for each event
	analysisManager->CreateNtuple("PCB", "PCB_Hits");
	if(StaticInfo::GetDetectorFlag("constructPCB")) { 
		analysisManager->CreateNtupleDColumn("fPCBedep");
	}
	analysisManager->FinishNtuple(1);
	
	//Scattering angle in each volume of the maps foil
	analysisManager->CreateNtuple("MapsFoil_ScatteringAngles", "ScatteringAngles");
	analysisManager->CreateNtupleDColumn("Alpide");
	if(StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) analysisManager->CreateNtupleDColumn("LowerGlue");
	if(StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) analysisManager->CreateNtupleDColumn("UpperGlue");
	if(StaticInfo::GetDetectorFlag("constructKaptonLayer")) analysisManager->CreateNtupleDColumn("LowerKapton");
	if(StaticInfo::GetDetectorFlag("constructKaptonLayer")) analysisManager->CreateNtupleDColumn("UpperKapton");
	if(StaticInfo::GetDetectorFlag("constructCopperLayer")) analysisManager->CreateNtupleDColumn("Copper");
	analysisManager->FinishNtuple(2);
	
	// Set ntuple output file
	//analysisManager->SetNtupleFileName(0, "output"+strRunID.str()+".root");
	//analysisManager->SetNtupleFileName(1, "output"+strRunID.str()+".root");
	//analysisManager->SetNtupleFileName(2, "output"+strRunID.str()+".root");
	
	

}

// ######## End of the run
void MyRunAction::EndOfRunAction(const G4Run*){

        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
        analysisManager->Write();
        analysisManager->CloseFile(false);

}


