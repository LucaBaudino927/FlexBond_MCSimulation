#include "MySteppingAction.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction) { 
	fEventAction = eventAction;
	fFirstMomDirectionInVolume = {0., 0., 0.};
	fLastMomDirectionInVolume = {0., 0., 0.};
	fTrackID = -1;
}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step* step){

	//Salvo la distribuzione degli angoli di scattering (e dell'energia depositata nella PCB) dei soli PROTONI
	G4String particleName = step->GetTrack()->GetParticleDefinition()->GetParticleName();
	if(particleName.compare("proton") == 0){
	
		G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
		if(volume->GetName().substr(0,8).compare("LV_SOLID") != 0 && volume->GetName().find("World") == std::string::npos) {
			
			auto analysisManager = G4AnalysisManager::Instance();
		
			if(step->IsFirstStepInVolume()) {
				fTrackID = step->GetTrack()->GetTrackID();
				fFirstMomDirectionInVolume = step->GetPreStepPoint()->GetMomentumDirection();
				
				G4double entryEnergy = step->GetPreStepPoint()->GetTotalEnergy();
				G4String detectorName = volume->GetName();
				if(detectorName.compare("logicAlpide") == 0) {
					analysisManager->FillNtupleDColumn(3, 0, entryEnergy);
				} else if(detectorName.compare("logicLowerGlue") == 0 && StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) {
					analysisManager->FillNtupleDColumn(3, 1, entryEnergy);
				} else if(detectorName.compare("logicUpperGlue") == 0 && StaticInfo::GetDetectorFlag("constructEpoxyGlueLayer")) {
					analysisManager->FillNtupleDColumn(3, 2, entryEnergy);
				} else if(detectorName.compare("logicLowerKapton") == 0 && StaticInfo::GetDetectorFlag("constructKaptonLayer")) {
					analysisManager->FillNtupleDColumn(3, 3, entryEnergy);
				} else if(detectorName.compare("logicUpperKapton") == 0 && StaticInfo::GetDetectorFlag("constructKaptonLayer")) {
					analysisManager->FillNtupleDColumn(3, 4, entryEnergy);
				} else if(detectorName.compare("logicCopper") == 0 && StaticInfo::GetDetectorFlag("constructCopperLayer")) {
					analysisManager->FillNtupleDColumn(3, 5, entryEnergy);
				} else {
					G4cerr << "Detector non trovato!!!" << G4endl;
				}
			}
			
			//la seconda condizione esclude urti inelastici
			if(step->IsLastStepInVolume() && fTrackID == step->GetTrack()->GetTrackID()) {
				
				fLastMomDirectionInVolume = step->GetPostStepPoint()->GetMomentumDirection();
				G4double scatteringAngle = fLastMomDirectionInVolume.getTheta() - fFirstMomDirectionInVolume.getTheta();
				//G4cout<<"---UserSteppingAction---scatteringAngle: "<<scatteringAngle/deg<<" deg = "<<scatteringAngle/rad<<" rad"<<G4endl;
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
			
			auto analysisManager = G4AnalysisManager::Instance();
		
			if(step->IsFirstStepInVolume()) {
				fTrackID = step->GetTrack()->GetTrackID();
				fFirstMomDirectionInVolume = step->GetPreStepPoint()->GetMomentumDirection();
				
				G4double entryEnergy = step->GetPreStepPoint()->GetTotalEnergy();
				analysisManager->FillNtupleDColumn(3, 6, entryEnergy);
			}
			
			//la seconda condizione esclude urti inelastici
			if(step->IsLastStepInVolume() && fTrackID == step->GetTrack()->GetTrackID()) {
				
				fLastMomDirectionInVolume = step->GetPostStepPoint()->GetMomentumDirection();
				G4double scatteringAngle = fLastMomDirectionInVolume.getTheta() - fFirstMomDirectionInVolume.getTheta();
				G4cout<<"---UserSteppingAction---scatteringAngle: "<<scatteringAngle/deg<<" deg = "<<scatteringAngle/rad<<" rad"<<G4endl;
				analysisManager->FillNtupleDColumn(2, 6, scatteringAngle * 180/Pi);
				
			}
			
		}
	
	}
	
	
	
	
        
}
