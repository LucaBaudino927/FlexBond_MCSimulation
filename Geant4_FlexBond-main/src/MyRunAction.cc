#include "MyRunAction.hh"

// ######## Costructor
MyRunAction::MyRunAction(){

	G4AnalysisManager* man = G4AnalysisManager::Instance();

        // ######## MC data truth
	man->CreateNtuple("Photons","Photons");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");//mm
	man->CreateNtupleDColumn("fWlen");//nm
	man->CreateNtupleDColumn("fT");//ns
	man->FinishNtuple(0);// First ntuple

        // ######## Experimental-like simulation
	man->CreateNtuple("Hits","Hits");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(1);//Seconda ntuple

        //Energy deposition for each event
	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleDColumn("fEdep");
	man->FinishNtuple(2);
            
}
    
// ######## Destructor
MyRunAction::~MyRunAction(){}

// ######## Begin of the run
void MyRunAction::BeginOfRunAction(const G4Run* run){

	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->SetNtupleMerging(true);
	//G4int runID = run->GetRunID();    
	//std::stringstream strRunID;
	//strRunID << runID;
	//man->OpenFile("../output/output"+strRunID.str()+".root");
	man->OpenFile("../output/output.root");

}

// ######## End of the run
void MyRunAction::EndOfRunAction(const G4Run*){

        G4AnalysisManager* man = G4AnalysisManager::Instance();
        man->Write();
        man->CloseFile();

}


