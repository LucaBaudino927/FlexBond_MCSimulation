#include "MyDetectorConstruction.hh"

// ######## Constructor 
MyDetectorConstruction::MyDetectorConstruction(){

        // ######## User Defined Messages
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
	//fMessenger->DeclareProperty("nCols", nCols, "N cols");
	//fMessenger->DeclareProperty("nRows", nRows, "N rows");
	fMessenger->DeclareProperty("cherenkov", isCherenkov, "Construct Cherenkov detector");
	fMessenger->DeclareProperty("scintillator", isScintillator, "Construct Scintillator");
	fMessenger->DeclareProperty("tof", isTOF, "Construct Time Of Flight");
	fMessenger->DeclareProperty("atmosphere", isAtmosphere, "Construct Atmosphere");
	fMessenger->DeclareProperty("mapsFoil",  		isMapsFoil, 			"Construct Maps Foil");
	fMessenger->DeclareProperty("constructEpoxyGlueLayer", 	constructEpoxyGlueLayer, 	"Use Epoxy Glue Layers");
	fMessenger->DeclareProperty("constructKaptonLayer",    	constructKaptonLayer, 		"Use Kapton Layers");
	fMessenger->DeclareProperty("constructCopperLayer", 	constructCopperLayer, 		"Use Copper Layer");
	fMessenger->DeclareProperty("constructSolderBalls", 	constructSolderBalls, 		"Use Solder Balls");
	fMessenger->DeclareProperty("alpideXDimension", 	alpideXFromMessenger, 		"Alpide X-Dimension");
	fMessenger->DeclareProperty("alpideYDimension", 	alpideYFromMessenger, 		"Alpide Y-Dimension");
	fMessenger->DeclareProperty("alpideThickness",  	alpideThicknessFromMessenger, 	"Alpide Z-Thickness");
	fMessenger->DeclareProperty("alpidePadRadius",  	alpidePadRadiusFromMessenger, 	"Alpide Pad Radius");
	fMessenger->DeclareProperty("glueThickness", 		glueThicknessFromMessenger, 	"Glue Thickness");
	fMessenger->DeclareProperty("kaptonThickness", 		kaptonThicknessFromMessenger, 	"Kapton Thickness");
	fMessenger->DeclareProperty("copperThickness", 		copperThicknessFromMessenger, 	"Copper Thickness");
        
        // ######## Void function of this class definted in the next rows. Material properties definition.
	if(!materialsDefined){
		DefineMaterials();
		materialsDefined = true;
	}

        // ######## Boolean for User Message option definitions
	isCherenkov = false;
	isScintillator = false;// Set particle momentum = 0 in generator.cc and particle = "geantino"
	isTOF= false;
	isAtmosphere = false;
	isMapsFoil = true;

        // ######## World dimension definition
	if(isAtmosphere){
		xWorld = 40.*km;// x2 is the real distance. The arrow in the visualization is insted x0.5
		yWorld = 40.*km;
		zWorld = 20.*km;
	}else{
		xWorld = 5.*cm;// x2 is the real distance. The arrow in the visualization is insted x0.5
		yWorld = 5.*cm;
		zWorld = 5.*cm;
	}
	
	if(isMapsFoil){
		constructEpoxyGlueLayer = true;
		constructKaptonLayer = true;
		constructCopperLayer = true;
		constructSolderBalls = true;
	}
	
}

// ######## Destructor
MyDetectorConstruction::~MyDetectorConstruction(){}

// ######## Actual construction of the detector based on the boolean selections 
G4VPhysicalVolume* MyDetectorConstruction::Construct(){
        
        G4cout << "------------------------MyDetectorConstruction::Construct()---------------" << G4endl;
        G4cout << "------------------------G4bool reinitialize: " << reinitialize << "--------------" << G4endl;
        /*if(isMapsFoil){
        	SD = nullptr;
        }*/
        
        //per eliminare la geometria e reinizializzarla da zero
        if(reinitialize){
		G4GeometryManager::GetInstance()->OpenGeometry();
		DeleteOldSensitiveDetectors();
		//G4PhysicalVolumeStore::GetInstance()->Clean();
		//G4LogicalVolumeStore::GetInstance()->Clean();
		//G4SolidStore::GetInstance()->Clean();
	}

	//inizializzare geometria
        solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
        logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicworld");
        G4VisAttributes* white = new G4VisAttributes(G4Colour::White());
    	white->SetVisibility(true);
    	logicWorld->SetVisAttributes(white);
        
        //Deve essere incluso nel volume madre se faccio un volume dentro a un altro. 
        //Posso anche fare operazioni booleane (false). Ultimo true check sugli overlap.
        physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

        if(isCherenkov) 	{ ConstructCherenkov(); }
        if(isScintillator) 	{ ConstructScintillator(); }
        if(isTOF) 		{ ConstructTOF(); }
        if(isAtmosphere) 	{ ConstructAtmosphere(); }
        if(isMapsFoil) 		{ ConstructMapsFoil(); }
        
        if(reinitialize){
        	G4MTRunManager::GetRunManager()->GeometryHasBeenModified();
        	G4GeometryManager::GetInstance()->CloseGeometry();
        }
        
        reinitialize = true;
        
        return physWorld;//mother volume
}

// ######## Function to define material properties used in the simulation
void MyDetectorConstruction::DefineMaterials(){

	/************************************************************************
	 *									*
	 *	IMPORTANTE: 							*
	 *	Se costruisco un G4Material lo cerco come "G4_XYZ"		*
	 *	Se costruisco un G4Element lo cerco come "XYZ"			*
	 *	G4Material* Cu = nist->FindOrBuildMaterial("G4_Cu");		*
	 *	G4Element* C = nist->FindOrBuildElement("C");			*
	 *									*
	 ************************************************************************/
	
        // ######## AIR
	G4NistManager* nist = G4NistManager::Instance();
	worldMat = nist->FindOrBuildMaterial("G4_Galactic");

        // ######## Si
	Si = nist->FindOrBuildMaterial("G4_Si");

        // ######## Kapton
	KaptonMaterial = nist->FindOrBuildMaterial("G4_KAPTON");

        // ######## Al
	Al = nist->FindOrBuildMaterial("G4_Al");
	
	// ####### C
	C = nist->FindOrBuildElement("C");
	
	// ######## H
	H = nist->FindOrBuildElement("H");
	
	// ######## N
	N = nist->FindOrBuildElement("N");
	
	// ######## O
	O = nist->FindOrBuildElement("O");
	
	// ####### Epoxy glue C8H20N2O
	epoxyGlue = new G4Material("EpoxyGlue", 1.25 * CLHEP::g / CLHEP::cm3, 4);
    	epoxyGlue->AddElement(C, 25.8064516*perCent);
    	epoxyGlue->AddElement(H, 64.516129*perCent);
    	epoxyGlue->AddElement(N, 6.4516129*perCent);
    	epoxyGlue->AddElement(O, 3.2258065*perCent);

        // ######## SiO2 
	SiO2 = new G4Material("SiO2",2.201*g/cm3,2);//2 components
	SiO2->AddElement(nist->FindOrBuildElement("Si"),1);//1 atomo di Si
	SiO2->AddElement(nist->FindOrBuildElement("O"),2);//2 atomo di ossigeno
        
        // ####### H2O
	H2O = new G4Material("H2O",1.000*g/cm3,2);//2 components
	H2O->AddElement(nist->FindOrBuildElement("H"),2);//1 atomo di Si
	H2O->AddElement(nist->FindOrBuildElement("O"),1);//2 atomo di ossigeno

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
	N = new G4Element("Nitrogen","N",7,aN);
	O = new G4Element("Oxygen","O",8,aO);

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
            
        //Note: I was using Geant v.11 and found you need to replace FASTCOMPONENT->SCINTILLATIONCOMPONENT1, 
        //FASTTIMECONST->SCINTILLATIONTIMECONSTANT1 and YIELDRATIO->SCINTILLATIONYIELD1 and then things worked the same
    }

// ######## Cherenkov detector with radiator and silicon detectors in an array of rectangular shape.
void MyDetectorConstruction::ConstructCherenkov(){

	AlTck = 20*um;
	SiTck = 50*um;
	KaTck = 150*um;
	PlaneDistance = 20*mm;

        // ######## PCB
	solidRadiator = new G4Box("solidRadiator", 7.5*mm*2+1*cm, 15*mm*5+1*cm, KaTck/2);//spessore 75 um
	logicRadiator = new G4LogicalVolume(solidRadiator, KaptonMaterial, "logicalRadiator");
	fScoringVolume = logicRadiator;//Where the energy deposit is evaluated for each step of the event. 
	solidRadiator2 = new G4Box("solidRadiator2", 7.5*mm*2+0.1*cm, 15*mm*5+0.1*cm, AlTck/2);//spessore 10 um
	logicRadiator2 = new G4LogicalVolume(solidRadiator2, Al, "logicalRadiator2");
	solidDetector = new G4Box("solidDetector", 7.5*mm, 15*mm, SiTck/2);//spessore 25 um
	logicDetector = new G4LogicalVolume(solidDetector, Si, "logicalCherenkovDetector");

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

	for(G4int k = 0; k < nPlanes; k++){
		physRadiator = new G4PVPlacement(
			0, 
			G4ThreeVector(0.,0.,PlaneDistance*k),
			logicRadiator,
			"physRadiator",
			logicWorld,
			false,
			0,
			true);
		physRadiator2 = new G4PVPlacement(
			0,
			G4ThreeVector(0.,0.,PlaneDistance*k+0.5*(KaTck+AlTck)),
			logicRadiator2, 
			"physRadiator2", 
			logicWorld,
			false,
			0,
			true);
		for(G4int i = 0; i < nRows; i++){
			for(G4int j = 0; j < nCols; j++){
				physDetector = new G4PVPlacement(
					0,					
					G4ThreeVector(-7.5*mm+(i*15)*mm,-60*mm+(j*30)*mm,PlaneDistance*k+(0.5*KaTck+AlTck+0.5*SiTck)),
					logicDetector,
					"physDetector",
					logicWorld,
					false,
					j+i*nCols,
					true);
			}
		}
	}
	
	logicRadiator->SetVisAttributes(yellowVisAtt);
	logicDetector->SetVisAttributes(redVisAtt);
	logicRadiator2->SetVisAttributes(grayVisAtt);

}

// ######## TOF with two detectors placed at 7 meters of distance along the Z axis
void MyDetectorConstruction::ConstructTOF(){

        solidDetector = new G4Box("solidDetector", 1.*cm, 1.*cm, 0.1*cm);
        logicDetector = new G4LogicalVolume(solidDetector, Si, "logicTOFDetector");//Worldmat as material to avoid secondary production
        physDetector = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, -4.*cm), logicDetector, "physDetector", logicWorld, false, 0, true);
        //physDetector = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, 3.*m), logicDetector, "physDetector", logicWorld, false, 1, true);
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
	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicScintillatorDetector");

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

// ######## Counstruct Maps detector surrounded by foils of glue and polyimide
// TODO: tutte le dimensioni qui saranno da parametrizzare!!!
void MyDetectorConstruction::ConstructMapsFoil(){

	MapsFoilDetectorList::ClearLogicalDetectorList();

	G4double alpideX 	 =	(alpideXFromMessenger != 0.) 		? alpideXFromMessenger*mm 	  : 30.*mm;
	G4double alpideY 	 = 	(alpideYFromMessenger != 0.) 		? alpideYFromMessenger*mm 	  : 15.*mm;
	G4double alpideThickness = 	(alpideThicknessFromMessenger != 0.) 	? alpideThicknessFromMessenger*um : 50.*um;
	G4double alpidePadRadius = 	(alpidePadRadiusFromMessenger != 0.) 	? alpidePadRadiusFromMessenger*um : 150.*um;
	G4double glueThickness 	 = 	(glueThicknessFromMessenger != 0.) 	? glueThicknessFromMessenger*um   : 25.*um;
	G4double kaptonThickness = 	(kaptonThicknessFromMessenger != 0.) 	? kaptonThicknessFromMessenger*um : 50.*um;
	G4double copperThickness = 	(copperThicknessFromMessenger != 0.) 	? copperThicknessFromMessenger*um : 5.*um;
	/**/
	
	G4double totalThickness = alpideThickness + ((constructEpoxyGlueLayer) 	? glueThickness*2   : 0.) 
						  + ((constructKaptonLayer) 	? kaptonThickness*2 : 0.)
						  + ((constructCopperLayer) 	? copperThickness*2 : 0.)
						  + ((constructSolderBalls) 	? alpidePadRadius*4 : 0.);						  
						  
	//costruisco il logicalDetector che sarà la parte sensibile del layer e il logicVolume nel quale inserirò gli altri layer
	//solidDetector = new G4Box("solidDetector", alpideX*0.5, alpideY*0.5, totalThickness*0.5);
	//logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
	
	//*
	//usare G4AssemblyVolume?
	//*
	
	// Define one layer as one assembly volume
	G4AssemblyVolume* assemblyDetector = new G4AssemblyVolume();
	
	//costruisco i vari layer e li piazzo rispetto alla posizione del logicDetector
	//metodi che contengono G4VPhysicalVolume *xyz = new G4PVPlacement(nullptr, {x, y, z}, logicXYZ, "physXYZ", logicDetector, false, 1, true);
	G4double Z = 0.*um;
	Alpide *alpide = new Alpide(alpideX, alpideY, alpideThickness, alpidePadRadius);
	alpide->ConstructAlpideLayerPV(0.*um, 0.*um, Z, assemblyDetector);
	if(constructEpoxyGlueLayer) {
		Glue *lowerGlue = new Glue(alpideX, alpideY, glueThickness, epoxyGlue, worldMat);
		Z = 0 - alpideThickness*0.5 - glueThickness*0.5;
		lowerGlue->ConstructLowerGlueLayerPV(0.*um, 0.*um, Z, assemblyDetector);
		Glue *upperGlue = new Glue(alpideX, alpideY, glueThickness, epoxyGlue, worldMat);
		Z = 0 + alpideThickness*0.5 + glueThickness*0.5;
		upperGlue->ConstructUpperGlueLayerPV(0.*um, 0.*um, Z, assemblyDetector, alpide);
	}
	if(constructKaptonLayer) {
		Kapton *lowerKapton = new Kapton(alpideX, alpideY, kaptonThickness, worldMat);
		Z = 0 - alpideThickness*0.5 - ((constructEpoxyGlueLayer) ? glueThickness : 0.) - kaptonThickness*0.5;
		lowerKapton->ConstructLowerKaptonLayerPV(0.*um, 0.*um, Z, assemblyDetector);
		Kapton *upperKapton = new Kapton(alpideX, alpideY, kaptonThickness, worldMat);
		Z = 0 + alpideThickness*0.5 + ((constructEpoxyGlueLayer) ? glueThickness : 0.) + kaptonThickness*0.5;
		upperKapton->ConstructUpperKaptonLayerPV(0.*um, 0.*um, Z, assemblyDetector, alpide);
	}
	if(constructCopperLayer) {
		Copper *copperLayer = new Copper(alpideX, alpideY, copperThickness);
		Z = 0+alpideThickness*0.5+((constructEpoxyGlueLayer) ? glueThickness : 0.)+((constructKaptonLayer) ? kaptonThickness : 0.)+copperThickness*0.5;
		copperLayer->ConstructCopperLayerPV(0.*um, 0.*um, Z, assemblyDetector);
	}
	if(constructSolderBalls) {
		SolderBall *solderBalls = new SolderBall(alpide);
		Z = alpideThickness*0.5 + ((constructEpoxyGlueLayer) ? glueThickness : 0.)
					+ ((constructKaptonLayer) ? kaptonThickness : 0.) 
					+ ((constructCopperLayer) ? copperThickness : 0.) 
					+ alpidePadRadius;
		solderBalls->ConstructSolderBallLayerPV(Z, assemblyDetector);
	}
	//*
	//*
	//*
	
	// Inserisco l'assembly nel world logical volume
	G4int NofLayer = 1;
	for(unsigned int i = 0; i < NofLayer; i++) {
		// Rotation of the assembly inside the world
		G4RotationMatrix Rm;
		// Translation of the assembly inside the world
		G4double offset = 1.*cm;
		G4ThreeVector Tm(0., 0., 0. + i*offset);
		G4Transform3D Tr = G4Transform3D(Rm,Tm);
		assemblyDetector->MakeImprint(logicWorld, Tr);
	}

	
	//posiziono il logicDetector (con tutti i suoi componenti attaccati) nel logicWorld
	//physDetector = new G4PVPlacement(0, {0., 0., 0.}, logicDetector, "physDetector", logicWorld, false, 0, true);
	
}

// ######## Construction of Sensitive Detector 
void MyDetectorConstruction::ConstructSDandField(){
        
        //v1 funziona con tutti i layer costruiti e tutti i layer sensibili ma ad esclusione di uno tra upperGlue e pad1
        //inoltre non posso attivare pad1 e pad2 sensitive insieme
        //quindi direi che avere una sola istanza di MySensitiveDetector per tutti layer non risolve.
        //Problemi:
        // pad1 e pad2 sensitive contemporaneamente
        // pad1 (o pad2) e upperGlue sensitive contemporaneamente
        
        // sensitive detectors -----------------------------------------------------
        G4cout << "-------------Number of logical detector: " << MapsFoilDetectorList::GetLogicalDetectorList().size() << "--------------" << G4endl;
	auto sdManager = G4SDManager::GetSDMpointer();
	G4String SDname;
	for(int i = 0; i < MapsFoilDetectorList::GetLogicalDetectorList().size(); i++){
		auto sensLayer = new MySensitiveDetector(SDname = MapsFoilDetectorList::GetLogicalDetectorList()[i]->GetName());
		sdManager->AddNewDetector(sensLayer);
		MapsFoilDetectorList::GetLogicalDetectorList()[i]->SetSensitiveDetector(sensLayer);
	}
	
	//TODO
	/*
	programma prossima settimana:
	-rendere configurabile TUTTO! pure le costanti che ho messo in MyEventAction
	-risolvere problemi con i pad (chiedere a Mario?)
	-creare il detector usando G4AssemblyDetector?
	-risolvere problema sull'istogramma dei tempi delle hit
	
	- per importare la geometria del flexbond dal file step leggere la guida per gli sviluppatori, paragrafo Tessellated Solids, G4TessellatedSolid
	*/
	
}	

void MyDetectorConstruction::DeleteOldSensitiveDetectors(){
	auto sdManager = G4SDManager::GetSDMpointer();
	G4SDStructure* structure = sdManager->GetTreeTop();
	G4String SDname;
	for(int i = 0; i < MapsFoilDetectorList::GetLogicalDetectorList().size(); i++){
		auto SDobject = structure->GetSD(MapsFoilDetectorList::GetLogicalDetectorList()[i]->GetName());
		G4cout << "Deleting SD with name: " << MapsFoilDetectorList::GetLogicalDetectorList()[i]->GetName() << G4endl;
		//non funziona
		delete SDobject;
		SDobject = 0;
	}
}




