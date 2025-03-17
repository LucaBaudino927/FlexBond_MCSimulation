#include "Kapton.hh"

//Notice that: "mother volume" refers to the volume in which the object has to be placed:
//it can be inside other objects or in a more general frame.

//constructor
Kapton::Kapton(G4double x, G4double y, G4double kaptonThickness, G4Material* holeMaterial) {

    fKaptonThickness = kaptonThickness;
    fKaptonXDimension = x;
    fKaptonYDimension = y;
    fHoleMaterial = holeMaterial;
    
}

//destructor
Kapton::~Kapton(){};

//Construction and placement of single kapton layer physical volume, covering all the detection system
void Kapton::ConstructLowerKaptonLayerPV(G4double xInWorld, G4double yInWorld, G4double zInWorld, G4LogicalVolume *worldLog)
{

    G4Box* solidKapton = new G4Box("solidKapton", GetKaptonXDimension()*0.5, GetKaptonYDimension()*0.5, GetKaptonThickness()*0.5);
    G4LogicalVolume* logicKapton = new G4LogicalVolume(solidKapton, GetKaptonMaterial(), "logicKapton");
    G4VisAttributes* brown = new G4VisAttributes(G4Colour::Brown());
    brown->SetVisibility(true);
    logicKapton->SetVisAttributes(brown);
    
    //placement of the layer logical volume into its mother frame
    new G4PVPlacement(0, {xInWorld, yInWorld, zInWorld}, logicKapton, "physLowerKapton", worldLog, false, 1, true);
    
    	/*G4cout << "kapton half X: " << solidKapton->GetXHalfLength() << G4endl;
	G4cout << "kapton half Y: " << solidKapton->GetYHalfLength() << G4endl;
	G4cout << "kapton half Z: " << solidKapton->GetZHalfLength()/CLHEP::um << " um" << G4endl;
    	G4cout << "xInWorld: " << xInWorld << G4endl;
	G4cout << "yInWorld: " << yInWorld << G4endl;
	G4cout << "zInWorld: " << zInWorld/CLHEP::um << " um" << G4endl;*/

}

//Construction and placement of single kapton layer physical volume, covering all the detection system
void Kapton::ConstructUpperKaptonLayerPV(G4double xInWorld, G4double yInWorld, G4double zInWorld, G4LogicalVolume *worldLog, Alpide* alpide)
{

    G4Box* solidKapton = new G4Box("solidKapton", GetKaptonXDimension()*0.5, GetKaptonYDimension()*0.5, GetKaptonThickness()*0.5);
    G4LogicalVolume* logicKapton = new G4LogicalVolume(solidKapton, GetKaptonMaterial(), "logicKapton");
    G4VisAttributes* brown = new G4VisAttributes(G4Colour::Brown());
    brown->SetVisibility(true);
    logicKapton->SetVisAttributes(brown);
    
    //holes
    for(int i = 0; i < alpide->GetNOfPads(); i++){
    	std::vector<G4ThreeVector> padPositions = alpide->GetPadCoordinates();
    	G4Tubs* solidHole = new G4Tubs("solidHole" + i, 0., alpide->GetPadRadius(), GetKaptonThickness()*0.5, 0., 360.*degree);
    	G4LogicalVolume* logicHole = new G4LogicalVolume(solidHole, GetHoleMaterial(), "logicKapton");
    	new G4PVPlacement(0, {padPositions[i].x(), padPositions[i].y(), padPositions[i].z()}, logicHole, "physKapton", logicKapton, false, 1, true);
    }
    
    //placement of the layer logical volume into its mother frame
    new G4PVPlacement(0, {xInWorld, yInWorld, zInWorld}, logicKapton, "physUpperKapton", worldLog, false, 1, true);
    
    	/*G4cout << "kapton half X: " << solidKapton->GetXHalfLength() << G4endl;
	G4cout << "kapton half Y: " << solidKapton->GetYHalfLength() << G4endl;
	G4cout << "kapton half Z: " << solidKapton->GetZHalfLength()/CLHEP::um << " um" << G4endl;
    	G4cout << "xInWorld: " << xInWorld << G4endl;
	G4cout << "yInWorld: " << yInWorld << G4endl;
	G4cout << "zInWorld: " << zInWorld/CLHEP::um << " um" << G4endl;*/

}



/*



//Construction and placement of a kapton matrix physical volume.
//The first argument, is a single kapton square, which can kapton a single silicon chip.
//xDimKaptondPad and yDimKaptond pad refers to a single silicon chip dimensions.
G4VPhysicalVolume *Kapton::ConstructKaptonMatrixPhVolume(Kapton *kapton, G4double xDimKaptondPad,
                                                     G4double yDimKaptondPad, G4int nOfColumn,
                                                     G4int nOfRows, G4double xInWorld,
                                                     G4double yInWorld, G4double zInWorld,
                                                     G4LogicalVolume *worldLog)
{
    G4NistManager *nist = G4NistManager::Instance();

    if (kapton->GetKaptonXDimension() > xDimKaptondPad || kapton->GetKaptonYDimension() > yDimKaptondPad)
    {
        G4cerr << "  ERROR ConstructKaptonMatrixPhVolume() \n"
               << " Kapton dimensions exceed the object: are you sure you want it spilt all over? \n"
               << G4endl;
    }
    G4VisAttributes *visAttr = new G4VisAttributes();
    visAttr->SetVisibility(false);

    //solid and logical volume for a single kapton square are created here
    G4Box *sKapton = new G4Box("Kapton", kapton->_kaptonXDimension * 0.5, kapton->_kaptonYDimension * 0.5,
                             kapton->_kaptonThickness * 0.5);
    G4LogicalVolume *lKapton = new G4LogicalVolume(sKapton, kapton->GetKaptonMaterial(), "lKapton");
    G4VisAttributes *yellow = new G4VisAttributes(G4Colour::Yellow());
    yellow->SetVisibility(true);
    lKapton->SetVisAttributes(yellow);

    //creation of padToBeKaptond envelope solid and logical volumes: its dimensions are equal to the object
    //to be kaptond ones, i.e. silicon chip in this case; a kapton square will be placed inside it.
    G4Box *padToBeKaptond = new G4Box("padToBeKaptond", xDimKaptondPad * 0.5, yDimKaptondPad * 0.5,
                                    kapton->GetKaptonThickness() * 0.5);
    G4LogicalVolume *lPadToBeKaptond = new G4LogicalVolume(padToBeKaptond, nist->FindOrBuildMaterial("G4_Galactic"),
                                                         "lPadToBeKaptond");
    lPadToBeKaptond->SetVisAttributes(visAttr);

    //placement of kapton inside its envelope
    G4VPhysicalVolume *pKaptondPad = new G4PVPlacement(0, {0, 0, 0}, lKapton, "pKaptondPad", lPadToBeKaptond, 0, 0, 0);

    //creation of kaptonArray envelope solid and logical volumes: it will contain kapton squared in their envelopes
    G4Box *kaptonArray = new G4Box("kaptonArray", kapton->_kaptonXDimension * nOfColumn * 0.5,
                                 kapton->_kaptonYDimension * 0.5, kapton->_kaptonThickness * 0.5);
    G4LogicalVolume *lKaptonArray = new G4LogicalVolume(kaptonArray, nist->FindOrBuildMaterial("G4_Galactic"),
                                                      "lKaptonArray");
    lKaptonArray->SetVisAttributes(visAttr);

    //creation of kaptonMatrix envelope solid and logical volumes: it will contain kapton Arrays
    G4Box *kaptonMatrix = new G4Box("kaptonMatrix", xDimKaptondPad * 0.5, yDimKaptondPad * 0.5,
                                  kapton->GetKaptonThickness());
    G4LogicalVolume *lKaptonMatrix = new G4LogicalVolume(kaptonMatrix, nist->FindOrBuildMaterial("G4_Galactic"),
                                                       "lKaptonMatrix");
    lKaptonMatrix->SetVisAttributes(visAttr);


    //kaptons in their envelope are replicated inside a kaptonArray, on the x dimension
    G4VPhysicalVolume *replicaPadX = new G4PVReplica("pReplicaX", lPadToBeKaptond, lKaptonArray, kXAxis,
                                                     nOfColumn, xDimKaptondPad);

    //kaptonArray are replicated inside kaptonMatrix, on the y dimension
    G4VPhysicalVolume *replicaPadY = new G4PVReplica("pReplicaY", lKaptonArray, lKaptonMatrix, kYAxis,
                                                     nOfRows, yDimKaptondPad);

    //kaptonMatrix is placed inside its mother volume
    G4VPhysicalVolume *pKaptonMatrix = new G4PVPlacement(nullptr, {xInWorld, yInWorld, zInWorld},
                                                       lKaptonMatrix, "pKaptonMatrix", worldLog, 0, 0, 0);

    return pKaptonMatrix;
}


*/
