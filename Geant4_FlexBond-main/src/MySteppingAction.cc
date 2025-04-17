#include "MySteppingAction.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction) { 
	fEventAction = eventAction;
	fFirstMomDirectionInVolume = {0., 0., 0.};
	fLastMomDirectionInVolume = {0., 0., 0.};
}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step* step){

	// Add Step by step get the energy deposition and add it to the total deposit
	
	G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	if(volume->GetName().substr(0,8).compare("LV_SOLID") != 0 && volume->GetName().find("World") == std::string::npos) {
		
		auto analysisManager = G4AnalysisManager::Instance();
	
		if(step->IsFirstStepInVolume()) {
			fFirstMomDirectionInVolume = step->GetPreStepPoint()->GetMomentumDirection();
		}
		
		if(step->IsLastStepInVolume()) {
			
			fLastMomDirectionInVolume = step->GetPostStepPoint()->GetMomentumDirection();
			
			G4double scatteringAngle = fLastMomDirectionInVolume.getTheta() - fFirstMomDirectionInVolume.getTheta();
			//G4cout << "---UserSteppingAction---scatteringAngle: " << scatteringAngle/deg << " deg = " << scatteringAngle/rad << " rad" << G4endl;
	
			G4String detectorName = volume->GetName();
			if(detectorName.compare("logicAlpide") == 0) {
				analysisManager->FillNtupleDColumn(2, 0, scatteringAngle * 180/Pi);
			} else if(detectorName.compare("logicLowerGlue") == 0 && StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) {
				analysisManager->FillNtupleDColumn(2, 1, scatteringAngle * 180/Pi);
			} else if(detectorName.compare("logicUpperGlue") == 0 && StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) {
				analysisManager->FillNtupleDColumn(2, 2, scatteringAngle * 180/Pi);
			} else if(detectorName.compare("logicLowerKapton") == 0 && StaticInfo::GetDetectorFlag("constructKaptonLayer")) {
				analysisManager->FillNtupleDColumn(2, 3, scatteringAngle * 180/Pi);
			} else if(detectorName.compare("logicUpperKapton") == 0 && StaticInfo::GetDetectorFlag("constructKaptonLayer")) {
				analysisManager->FillNtupleDColumn(2, 4, scatteringAngle * 180/Pi);
			} else if(detectorName.compare("logicCopper") == 0 && StaticInfo::GetDetectorFlag("constructCopperLayer")) {
				analysisManager->FillNtupleDColumn(2, 5, scatteringAngle * 180/Pi);
			} else {
				G4cerr << "Detector non trovato!!!" << G4endl;
			}
			
		}
		
	} else if(volume->GetName().substr(0,8).compare("LV_SOLID") == 0) {
		//PCB energy deposition
		G4double edep = step->GetTotalEnergyDeposit();
		fEventAction->AddEdep(edep);
	};
	
	
        
}
