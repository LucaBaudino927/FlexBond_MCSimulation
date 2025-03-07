#include "construction.hh"

// ######## Constructor 

    MyDetectorConstruction::MyDetectorConstruction(){

        // ######## User Defined Messages

            fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");//non mi funziona sulla interfaccia grafica...
            fMessenger->DeclareProperty("nCols", nCols, "N cols");
            fMessenger->DeclareProperty("nRows", nRows, "N rows");
            fMessenger->DeclareProperty("cherenkov", isCherenkov, "Construct Cherenkov detector");
            fMessenger->DeclareProperty("scintillator", isScintillator, "Construct Scintillator");
            fMessenger->DeclareProperty("tof", isScintillator, "Construct Time Of Flight");
            fMessenger->DeclareProperty("atmosphere", isAtmosphere, "Construct Atmosphere");
        
        // ######## Void function of this class definted in the next rows. Material properties definition.

            DefineMaterials();

        // ######## Boolean for User Message option definitions

            isCherenkov = true;
            isScintillator = false;// Set particle momentum = 0 in generator.cc and particle = "geantino"
            isTOF= false;
            isAtmosphere = false;

        // ######## World dimension definition

            if(isAtmosphere){
                xWorld = 40.*km;// x2 is the real distance. The arrow in the visualization is insted x0.5
                yWorld = 40.*km;
                zWorld = 20.*km;
            }else{
                xWorld = 10*cm;// x2 is the real distance. The arrow in the visualization is insted x0.5
                yWorld = 10*cm;
                zWorld = 10*cm;
            }

    }

// ######## Destructor

    MyDetectorConstruction::~MyDetectorConstruction(){}

// ######## Function to define material properties used in the simulation

    void MyDetectorConstruction::DefineMaterials(){

        // ######## AIR

            G4NistManager* nist = G4NistManager::Instance();
            worldMat = nist->FindOrBuildMaterial("G4_Galactic");

        // ######## Si

            Si = nist->FindOrBuildMaterial("G4_Si");

        // ######## Kapton

            Kapton = nist->FindOrBuildMaterial("G4_KAPTON");

        // ######## Al

            Al = nist->FindOrBuildMaterial("G4_Al");

        // ######## Cu

            Cu = nist->FindOrBuildMaterial("G4_Cu");

        // ######## Be

            Cu = nist->FindOrBuildMaterial("G4_Be");

        // ######## SiO2 
            
            SiO2 = new G4Material("SiO2",2.201*g/cm3,2);//2 components
            SiO2->AddElement(nist->FindOrBuildElement("Si"),1);//1 atomo di Si
            SiO2->AddElement(nist->FindOrBuildElement("O"),2);//2 atomo di ossigeno
        
        // ####### H2O

            H2O = new G4Material("H2O",1.000*g/cm3,2);//2 components
            H2O->AddElement(nist->FindOrBuildElement("H"),2);//1 atomo di Si
            H2O->AddElement(nist->FindOrBuildElement("O"),1);//2 atomo di ossigeno

        // ####### C

            C = nist->FindOrBuildElement("C");

        // ####### Aerogel 

            Aerogel = new G4Material("Aerogel",0.200*g/cm3,3);
            Aerogel->AddMaterial(SiO2, 62.5*perCent);
            Aerogel->AddMaterial(H2O, 37.4*perCent);
            Aerogel->AddElement(C, 0.1*perCent);
        
        // ####### NaI(Tl)
            
            Na = nist->FindOrBuildElement("Na");
            I = nist->FindOrBuildElement("I");
            NaI = new G4Material("NaI", 3.67*g/cm3, 2);
            NaI->AddElement(Na, 1);
            NaI->AddElement(I, 1);

        // ####### Wrapping of NaI(Tl)

            mirrorSurface = new G4OpticalSurface("mirrorSurface");
            mirrorSurface->SetType(dielectric_metal);
            mirrorSurface->SetFinish(ground);
            mirrorSurface->SetModel(unified);

        // ######## Air for atmosphere with different density at different altitudes
        
            G4double density0 = 1.29*kg/m3;
            G4double aN = 14.01*g/mole;//70% nitrogen
            G4double aO = 16.00*g/mole;//30% oxigen
            G4double f = 3;
            G4double R = 8.3144626181532;//gas constant
            G4double g0 = 9.81;
            G4double kappa = (f+2)/f;
            G4double T = 293.15;//Kelvin
            G4double M = (0.3*aO+0.7*aN)/1000;//molar mass conversion. 70%N e 30%O
            N= new G4Element("Nitrogen","N",7,aN);
            O= new G4Element("Oxygen","O",8,aO);

            for(G4int i= 0;i<10;i++){
                std::stringstream stri;
                stri << i;
                G4double h = 40e3/10.*i;
                G4double density = density0*pow((1-(kappa-1)/kappa*M*g0*h/(R*T)),(1/(kappa-1)));
                Air[i] = new G4Material("G4_AIR_"+stri.str(), density, 2);//2 components
                Air[i]->AddElement(N, 70*perCent);
                Air[i]->AddElement(O, 30*perCent);
            }

        // ######## Optical paremeters of Aerogel, World and NaI

            G4double energy[2] = {1.239841939*eV/0.9,1.239841939*eV/0.2};//0.2 -> 200 nm (blue). 900 nm red light. Conversion factor is 1240 eV*nm (h*c).
            G4double fraction[2] = {1.0, 1.0};//hypotesis, fraction of photons in blue and red is the same
            G4double reflectivity[2] = {1.0, 1.0};//all reflected for all wavelenghts (wrapping)
            G4double rindexAerogel[2] = {1.1,1.1};
            G4double rindexWorld[2] = {1.0,1.0};
            G4double rindexNaI[2] = {1.78, 1.78};
            G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
            G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
            G4MaterialPropertiesTable *mptNaI = new G4MaterialPropertiesTable();
            G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
            mptAerogel->AddProperty("RINDEX",energy, rindexAerogel,2); //2 values in the array.
            mptWorld->AddProperty("RINDEX",energy, rindexWorld,2);
            mptNaI->AddProperty("RINDEX", energy, rindexNaI, 2);
            mptNaI->AddProperty("SCINTILLATIONCOMPONENT1", energy, fraction, 2);// how many photons in each wavelenght
            mptNaI->AddConstProperty("SCINTILLATIONYIELD",38./keV);//photons per energy loss of the particle
            mptNaI->AddConstProperty("RESOLUTIONSCALE",1.0);//
            mptNaI->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 250.*ns);//exponential function. Decay time of the scint. 
            mptNaI->AddConstProperty("SCINTILLATIONYIELD1",1.);//distribution of the photons. you can create a sigma of the desided spectrum, now =1. 
            mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
            Aerogel->SetMaterialPropertiesTable(mptAerogel);
            worldMat->SetMaterialPropertiesTable(mptWorld);
            NaI->SetMaterialPropertiesTable(mptNaI);
            mirrorSurface->SetMaterialPropertiesTable(mptMirror);
            
            //Note: I was using Geant v.11 and found you need to replace FASTCOMPONENT->SCINTILLATIONCOMPONENT1, FASTTIMECONST->SCINTILLATIONTIMECONSTANT1 and YIELDRATIO->SCINTILLATIONYIELD1 and then things worked the same
    }

// ######## Cherenkov detector with radiator and silicon detectors in an array of rectangular shape.

    void MyDetectorConstruction::ConstructCherenkov(){

            CuTck = 0.0150;//0.0020;// cm 
            AlTck = 0.0020;// cm
            SiTck = 0.0050;// cm
            KaTck = 0.0150;//0.0025;// cm
            PlaneDistance = 20; // mm

        // ######## PCB

            solidRadiator = new G4Box("solidRadiator",7.5*mm*2+1*cm,15*mm*5+1*cm,KaTck/2*cm);//The real dimension is x2. 
            logicRadiator = new G4LogicalVolume(solidRadiator,Kapton,"logicalRadiator");//Fill the volume 
            //fScoringVolume = logicRadiator;//Where the energy deposit is evaluated for each step of the event. 

            solidRadiator2 = new G4Box("solidRadiator2",7.5*mm*2+0.1*cm,15*mm*5+0.1*cm,AlTck/2*cm);//The real dimension is x2. 
            logicRadiator2 = new G4LogicalVolume(solidRadiator2,Cu,"logicalRadiator2");//Fill the volume 

            solidDetector = new G4Box("solidDetector",7.5*mm,15*mm,SiTck/2*cm);//The real dimension is x2. 
            logicDetector = new G4LogicalVolume(solidDetector,Si,"logicalDetector");//Fill the volume 

            fScoringVolume = logicDetector;//Where the energy deposit is evaluated for each step of the event. 


        // ######## Detector (array of rectangular solid state detectors)

            G4VisAttributes* yellowVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); // Yellow color
            G4VisAttributes* redVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Red color
            G4VisAttributes* grayVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5)); // RGB values (0.5, 0.5, 0.5) for gray
            yellowVisAtt->SetForceSolid(true);
            redVisAtt->SetForceSolid(true);
            grayVisAtt->SetForceSolid(true);

            nCols = 5;
            nRows = 2;
            nPlanes = 3;// NB energia depositata e' calcolata su tutti i volumi identici che metti, fa la somma. Si vede che con 3 o 5 piani cambia Edep.
            //Array of detectors. nRows and nCols define the array (in the constructor). 
            
            for(G4int k=0;k<nPlanes;k++){
                physRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0*cm+PlaneDistance*mm*k),logicRadiator,"physRadiator",logicWorld,false,0,true);//Placing of the volume. x=0,y=0,z=0.25. y is directed versus the top.
                physRadiator2 = new G4PVPlacement(0, G4ThreeVector(0.,0.,0*cm+PlaneDistance*mm*k+0.5*(KaTck+AlTck)*cm),logicRadiator2,"physRadiator2",logicWorld,false,0,true);
                for(G4int i=0;i<nRows;i++){
                    for(G4int j=0;j<nCols;j++){
                            physDetector = new G4PVPlacement(0,G4ThreeVector(-7.5*mm+(i*15)*mm,-60*mm+(j*30)*mm,(0*cm+(0.5*KaTck+AlTck+0.5*SiTck)*cm)+PlaneDistance*mm*k),logicDetector,"physDetector",logicWorld,false,j+i*nCols,true);
                    }
                }
            }
            logicRadiator->SetVisAttributes(yellowVisAtt);
            logicDetector->SetVisAttributes(redVisAtt);
            logicRadiator2->SetVisAttributes(grayVisAtt);

    }

// ######## TOF with two detectors placed at 7 meters of distance along the Z axis

    void MyDetectorConstruction::ConstructTOF(){

        solidDetector = new G4Box("solidDetector", 1.*m, 1.*m, 0.1*m);
        logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");//Worldmat as material to avoi secondary production
        physDetector = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, -4.*m), logicDetector, "physDetector", logicWorld, false, 0, true);
        physDetector = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 3.*m), logicDetector, "physDetector", logicWorld, false, 1, true);
        fScoringVolume = logicDetector;//Both the phys detector will store the energy release. The logic volume is the same.

    }

// ######## Atmosphere for shower production. 10 layers of atmosphere with different logicvolumes. Each volume has different density with exponential decrease. 

    void MyDetectorConstruction::ConstructAtmosphere(){

        solidAtmosphere = new G4Box("solidAtmosphere", xWorld, yWorld, zWorld/10.);//divido per 10 perche ho 10 layers, di larghezza 1/10 zworld
        for(G4int i = 0; i < 10; i++){
            logicAtmosphere[i] = new G4LogicalVolume(solidAtmosphere,Air[i],"logicAtmosphere");
            physAtmosphere[i] = new G4PVPlacement(0, G4ThreeVector(0, 0, zWorld/10.*2*i - zWorld + zWorld/10.), logicAtmosphere[i], "physAtmosphere", logicWorld, false, i, true);
        }

    }

// ######## Scintillators for PET detector. Cilindrical geometry with 6 layers of 360 degree covering detectors. Each detector is 10x10x12 cmˆ3 with sensitive detectors.

    void MyDetectorConstruction::ConstructScintillator(){

        // ######## Scintillators fot PET detector. 

            //solidScintillator = new G4Tubs("solidScintillator",10*cm,20*cm,30*cm,0*deg,360*deg);
            solidScintillator = new G4Box("solidScintillator",5*cm,5*cm,6*cm);
            logicScintillator = new G4LogicalVolume(solidScintillator,NaI,"logicalScintillator");
            //physScintillator = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicScintillator,"pyisScintillator",logicWorld,false,0,true);
            G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirrorSurface);//for the reflectivity
            fScoringVolume = logicScintillator;

        // ######## Detectors to be coupled with NaI for PET detector

            solidDetector = new G4Box("solidDetector", 1.*cm, 5.*cm, 6*cm);
            logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

        // ####### Array creation for both scintillators and detectors

            for(G4int i=0;i<6;i++){ // 6 layers along the Z axis
                for(G4int j=0;j<16;j++){// Pi/16  
                    G4Rotate3D rotZ(j*22.5*deg, G4ThreeVector(0,0,1));//360/16 = 22.5. (0,0,1) rotation along Z axis 
                    //scint rotation
                    G4Translate3D transXScint(G4ThreeVector(5./tan(22.5/2*deg)*cm+5.*cm, 0.*cm, -40.*cm + i*15*cm));
                    G4Transform3D transformScint = (rotZ)*(transXScint);
                    //det rotation
                    G4Translate3D transXDet(G4ThreeVector(5./tan(22.5/2*deg)*cm+5.*cm+6.*cm, 0.*cm, -40.*cm + i*15*cm));
                    G4Transform3D transformDet = (rotZ)*(transXDet);

                    physScintillator = new G4PVPlacement(transformScint, logicScintillator, "physScintillator", logicWorld, false, 0, true);
                    physDetector = new G4PVPlacement(transformDet, logicDetector, "physDetector", logicWorld, false, 0, true);
                } 
            }

        

    }

// ######## Actual construction of the detector based on the boolean selections 

    G4VPhysicalVolume* MyDetectorConstruction::Construct(){
        
        solidWorld = new G4Box("solidWorld",xWorld,yWorld,zWorld);
        logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicworld");
        physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,true);//nel centro. altro numero dice se e' il volume meadre o no. Deve essere incluso nel volume madre se faccio un volume dentro a un altro. Posso anche fare operazioni booleane (false). Ultimo true check sugli overlap.

        if(isCherenkov) {ConstructCherenkov();};
        if(isScintillator) {ConstructScintillator();};
        if(isTOF){ConstructTOF();};
        if(isAtmosphere){ConstructAtmosphere();};
        return physWorld;//mother volume
    }

// ######## Construction of Sensitive Detector 

    /*void MyDetectorConstruction::ConstructSDandField(){
        MySensitiveDetector* sensDet = new MySensitiveDetector("SensitiveDetector");//detector.hh
        if(logicDetector != NULL)
            logicDetector->SetSensitiveDetector(sensDet);
    }*/
