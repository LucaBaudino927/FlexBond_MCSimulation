#include "detector.hh"

// ######## Quantum efficiency of the PMT from data eff.dat taken online 

    MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
    {
        quEff = new G4PhysicsOrderedFreeVector();
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
    }

// ######## Destructor

    MySensitiveDetector::~MySensitiveDetector(){}

// ######## Get informations from the sensistive detectors, MC truth and experimental-like simulation

    G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROHist){

        // ######## MC trouth

            G4Track* track = aStep->GetTrack();
            // Comment for TOF the following line
            //track->SetTrackStatus(fStopAndKill);//si ferma la traccia appena tocca il detector. Comment for TOF!
            G4StepPoint *preStepPoint = aStep ->GetPreStepPoint();
            G4StepPoint *postStepPoint = aStep ->GetPostStepPoint();
            G4ThreeVector posPhoton = preStepPoint->GetPosition();

        // ######## Experimental-like simulation

            const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
            G4int copyNo = touchable->GetCopyNumber(); //Touched detector.
            G4VPhysicalVolume* physVol = touchable->GetVolume();
            G4ThreeVector posDetector = physVol->GetTranslation();

        // ######## Time

            G4double time = preStepPoint->GetGlobalTime();//local esiste anche. global dipende da quando e' stata creata la particella. 

        // ####### Wlen from the momentum

            G4ThreeVector momPhoton = preStepPoint->GetMomentum();
            G4double wlen = (1.239841939*eV)/momPhoton.mag()*1E+03;//nm value. .mag e' il valore assoluto.

        // ######## Data storing into Tree
            G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); 
            G4AnalysisManager* man = G4AnalysisManager::Instance();
            man->FillNtupleIColumn(0,0,evt);
            man->FillNtupleDColumn(0,1,posPhoton[0]);
            man->FillNtupleDColumn(0,2,posPhoton[1]);
            man->FillNtupleDColumn(0,3,posPhoton[2]);
            man->FillNtupleDColumn(0,4,wlen);
            man->FillNtupleDColumn(0,5,time);
            man->AddNtupleRow(0);

        // ####### Hard-coded MC sampling for the efficiency

            if(G4UniformRand() < quEff->Value(wlen)){//random between 0,1. Di fatto fa un sampling montecarlo. Se sta sotto al qe della singola wlen, e' stato rivelato, se sta sopra no. E' come associare la qe alla singola wlen.
                man->FillNtupleIColumn(1,0,evt);
                man->FillNtupleDColumn(1,1,posDetector[0]);
                man->FillNtupleDColumn(1,2,posDetector[1]);
                man->FillNtupleDColumn(1,3,posDetector[2]);
                man->AddNtupleRow(1);
            }

        // ######## Cout only is MT is not present

            #ifndef G4MULTITHREADED
                G4cout << "Detector position: " << posDetector << G4endl;
                G4cout << "Photon Position = " << posPhoton << G4endl;
                G4cout<< "Copy number = "<< copyNo << G4endl;
            #endif

        return true;
    }

