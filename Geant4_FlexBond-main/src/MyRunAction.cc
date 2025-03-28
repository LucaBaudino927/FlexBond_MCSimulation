#include "MyRunAction.hh"

// ######## Costructor
MyRunAction::MyRunAction() {

	//G4cout<<"---MyRunAction---"<<G4endl;
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	//analysisManager->SetVerboseLevel(1);
	analysisManager->SetNtupleMerging(true);
	//analysisManager->SetHistoDirectoryName("output");
	//analysisManager->SetFileName("output");
	//analysisManager->SetDefaultFileType("root");
	
	
	/***********************************************************************************************************************************
	 *	NofMySensitiveDetector = 6          se ho alpide, colla, kapton e rame							   *
	 *	NofMySensitiveDetector = 6+(#pad*2) se ho alpide, colla, kapton, rame e pad dell'alpide					   *
	 *	NofMySensitiveDetector = 6+(#pad*3) se ho alpide, colla, kapton, rame, pad dell'alpide e solder balls per ogni pad	   *
	 ***********************************************************************************************************************************/
	G4int NofMySensitiveDetector = 6;
	for(int i = 0; i < NofMySensitiveDetector; i++){
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
	
	//Energy deposition for each event
	analysisManager->CreateNtuple("Scoring", "Scoring");
	analysisManager->CreateNtupleDColumn("fEdep");
	analysisManager->FinishNtuple(0);
	
/*-------- WWWW ------- G4Exception-START -------- WWWW -------
*** G4Exception : Analysis_W001
      issued by : G4THnManager<T>::Fillh1
Histogram 45 does not exist.
*** This is just a warning message. ***
-------- WWWW -------- G4Exception-END --------- WWWW -------

G4WT3 > 
-------- WWWW ------- G4Exception-START -------- WWWW -------
*** G4Exception : Analysis_W001
      issued by : G4THnToolsManager::Fill
Failed to fill h1 id 45. Histogram does not exist.
*** This is just a warning message. ***
-------- WWWW -------- G4Exception-END --------- WWWW -------*/
	
	
	
	/*
        // ######## MC data truth
	analysisManager->CreateNtuple("Photons","Photons");
	analysisManager->CreateNtupleIColumn("fEvent");
	analysisManager->CreateNtupleDColumn("fX");
	analysisManager->CreateNtupleDColumn("fY");
	analysisManager->CreateNtupleDColumn("fZ");//mm
	analysisManager->CreateNtupleDColumn("fWlen");//nm
	analysisManager->CreateNtupleDColumn("fT");//ns
	analysisManager->FinishNtuple(0);// First ntuple

        // ######## Experimental-like simulation
	analysisManager->CreateNtuple("Hits","Hits");
	analysisManager->CreateNtupleIColumn("fEvent");
	analysisManager->CreateNtupleDColumn("fX");
	analysisManager->CreateNtupleDColumn("fY");
	analysisManager->CreateNtupleDColumn("fZ");
	analysisManager->FinishNtuple(1);//Seconda ntuple

        //Energy deposition for each event
	analysisManager->CreateNtuple("Scoring", "Scoring");
	analysisManager->CreateNtupleDColumn("fEdep");
	analysisManager->FinishNtuple(2);
	*/
            
}
    
// ######## Destructor
MyRunAction::~MyRunAction(){}

// ######## Begin of the run
void MyRunAction::BeginOfRunAction(const G4Run* run){

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
	// Reset histograms from previous run
	analysisManager->Reset();
  
	//G4int runID = run->GetRunID();  
	//std::stringstream strRunID;
	//strRunID << runID;
	//analysisManager->OpenFile("../output/output"+strRunID.str()+".root");
	analysisManager->OpenFile("../output/output.root");

}

// ######## End of the run
void MyRunAction::EndOfRunAction(const G4Run*){

        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
        G4cout<<"---debugEndOfRunAction()---1---"<<G4endl;
        analysisManager->Write();
        G4cout<<"---debugEndOfRunAction()---2---"<<G4endl;
        analysisManager->CloseFile(false);
        G4cout<<"---debugEndOfRunAction()---3---"<<G4endl;
        
        //delete G4AnalysisManager::Instance();

}


