#include "MySensitiveDetector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {
	
	G4cout << "------------------------MySensitiveDetector::MySensitiveDetector()---------------" << G4endl;
	G4cout << "-----------Creating an SD with name " << name << " and HitsCollection name MySensitiveDetectorColl -------------" << G4endl;
	collectionName.insert("MySensitiveDetectorColl");	

	//meccanismo per simulare sensitive detector come se fosse un PMT: per ora non mi interessa
	// ######## Quantum efficiency of the PMT from data eff.dat taken online 
        /*quEff = new G4PhysicsOrderedFreeVector();
        std::ifstream datafile;
        datafile.open("pmt_efficiency.dat");
        G4cout << "Reading PMT quantum efficiency vs wavelength data" << std::endl;
        while(!datafile.eof())//until the datafile is open
        {
            G4double wlen, queff;
            datafile >> wlen >> queff;
            G4cout << "wavelength: " << wlen << " ; quantum efficiency: " << queff << std::endl;
            quEff->InsertValues(wlen, queff/100.);
        }
        datafile.close();
        G4cout << "PMT quantum efficiency data read. " << quEff->GetVectorLength() << " QE data are stored" << std::endl;
        //quEff->SetSpline(false);//To use linear interpolation instead of Spline.
        */
}

// ######## Destructor
MySensitiveDetector::~MySensitiveDetector(){}


void MySensitiveDetector::Initialize(G4HCofThisEvent* hitsContainer){

	G4cout << "------------------------MySensitiveDetector::Initialize()-----------------------" << G4endl;
	fHitsCollection = new MySensitiveDetectorHitsCollection(SensitiveDetectorName, collectionName[0]);
	if (fHCID < 0) {
		G4cout << "------------Creating the HitsCollection: " << SensitiveDetectorName << "/" << collectionName[0] << "--------------" << G4endl;
		fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
	}
	hitsContainer->AddHitsCollection(fHCID, fHitsCollection);
  
}

void MySensitiveDetector::clear() { delete this; }


// ######## Get informations from the sensistive detectors, MC truth and experimental-like simulation
G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROHist){
	
	/****************************************************************************************
	 *	Cosa voglio misurare?								*
	 *	-energia depositata per ogni layer						*
	 *	-somma dell'energia depositata su tutti i layer (già fatto nel EventAction)	*
	 *	-tempo										*
	 *	-coordinate									*
	 *	-tipo di particella?								*
	 *	-momento della particella?							*
	 ****************************************************************************************/
	
	
	//G4cout<<"------------ProcessHit-------------"<<G4endl;
	auto edep = aStep->GetTotalEnergyDeposit();
  	if (edep == 0.) return true;

	auto preStepPoint = aStep->GetPreStepPoint();
	auto touchable = preStepPoint->GetTouchable();
	auto copyNo = touchable->GetVolume()->GetCopyNo();
	auto hitTime = preStepPoint->GetGlobalTime();

	// Create a new hit and set it to the collection
	auto hit = new MySensitiveDetectorHit(copyNo, hitTime);
	auto physical = touchable->GetVolume();
	hit->SetLogVolume(physical->GetLogicalVolume());
	auto transform = touchable->GetHistory()->GetTopTransform();
	transform.Invert();
	hit->SetRot(transform.NetRotation());
	hit->SetPos(transform.NetTranslation());
	hit->SetEdep(edep);
	fHitsCollection->insert(hit);
	
  
  

	
	//-----------------------------------Precedente inserimento dei dati nelle ntuple: per ora non mi interessa
	
        /* // ######## MC trouth
	G4Track* track = aStep->GetTrack();
	G4StepPoint *preStepPoint = aStep ->GetPreStepPoint();
	G4ThreeVector posPhoton = preStepPoint->GetPosition();

        // ######## Experimental-like simulation
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber(); //Touched detector.
	G4VPhysicalVolume* physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	
	G4cout << "Detector position: " << posDetector << G4endl;
	
	// ######## Time
	G4double time = preStepPoint->GetGlobalTime();//local esiste anche global. Dipende da quando e' stata creata la particella. 
	
	
	// ####### Wlen from the momentum
	G4ThreeVector momPhoton = preStepPoint->GetMomentum();
	G4double wlen = (1.239841939*keV)/momPhoton.mag();//nm, value.mag() e' il valore assoluto.
	// ######## Data storing into Tree
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); 
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0,0,evt);
	man->FillNtupleDColumn(0,1,posPhoton[0]);
	man->FillNtupleDColumn(0,2,posPhoton[1]);
	man->FillNtupleDColumn(0,3,posPhoton[2]);//mm
	man->FillNtupleDColumn(0,4,wlen);//nm
	man->FillNtupleDColumn(0,5,time);//ns
	man->AddNtupleRow(0);
	
	man->FillNtupleIColumn(1,0,evt);
	man->FillNtupleDColumn(1,1,posDetector[0]);
	man->FillNtupleDColumn(1,2,posDetector[1]);
	man->FillNtupleDColumn(1,3,posDetector[2]);
	man->AddNtupleRow(1);
	*/

	//Meccanismo per simulare fotomoltiplicatore: non mi interessa
	/* // ######## Photons
        if(track->GetParticleDefinition()->GetParticleName().compare("gamma") == 0){
        	// ######## Time
		G4double time = preStepPoint->GetGlobalTime();//local esiste anche global. Dipende da quando e' stata creata la particella. 
        	// ####### Wlen from the momentum
        	G4ThreeVector momPhoton = preStepPoint->GetMomentum();
		G4double wlen = (1.239841939*keV)/momPhoton.mag();//nm, value.mag() e' il valore assoluto.
		// ######## Data storing into Tree
		G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); 
		G4AnalysisManager* man = G4AnalysisManager::Instance();
		man->FillNtupleIColumn(0,0,evt);
		man->FillNtupleDColumn(0,1,posPhoton[0]);
		man->FillNtupleDColumn(0,2,posPhoton[1]);
		man->FillNtupleDColumn(0,3,posPhoton[2]);//mm
		man->FillNtupleDColumn(0,4,wlen);//nm
		man->FillNtupleDColumn(0,5,time);//ns
		man->AddNtupleRow(0);
		
		// ####### Hard-coded MC sampling for the efficiency
		// Random tra 0,1. E' un sampling montecarlo. Se sta sotto al QE della singola wlen, e' stato rivelato, se sta sopra no.
		if(G4UniformRand() < quEff->Value(wlen)){
			man->FillNtupleIColumn(1,0,evt);
			man->FillNtupleDColumn(1,1,posDetector[0]);
			man->FillNtupleDColumn(1,2,posDetector[1]);
			man->FillNtupleDColumn(1,3,posDetector[2]);
			man->AddNtupleRow(1);
		}
        }

        // ######## Cout only if MT is not present
	#ifndef G4MULTITHREADED
                G4cout << "Detector position: " << posDetector << G4endl;
                G4cout << "Photon Position = " << posPhoton << G4endl;
                G4cout<< "Copy number = "<< copyNo << G4endl;
	#endif*/

        return true;
    
}



