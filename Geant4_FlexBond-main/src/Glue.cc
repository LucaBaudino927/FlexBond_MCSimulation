#include "Glue.hh"

//Notice that: "mother volume" refers to the volume in which the object has to be placed:
//it can be inside other objects or in a more general frame.

//constructor
Glue::Glue(G4double x, G4double y, G4double glueThickness, G4Material* glue, G4Material* holeMaterial) {

    fGlue = glue;

    if (fGlue == nullptr)
    {

        G4cerr << "  ERROR Glue() " << G4endl
               << "  G4Material* epoxyGlue was not correctly created in MyDetectorConstruction::DefineMaterials()!"
               << G4endl;
    }

    fGlueThickness = glueThickness;
    fGlueXDimension = x;
    fGlueYDimension = y;
    fHoleMaterial = holeMaterial;
    
}

//destructor
Glue::~Glue(){};

//Construction and placement of single glue layer physical volume, covering all the detection system
void Glue::ConstructLowerGlueLayerPV(G4double xInWorld, G4double yInWorld, G4double zInWorld, G4LogicalVolume *worldLog) {

    //G4cout << "Lower glue X: " << GetGlueXDimension()/cm << "cm" << G4endl;
    //G4cout << "Lower glue Y: " << GetGlueYDimension()/cm << "cm" << G4endl;
    G4cout << "Lower glue Z thickness: " << GetGlueThickness()/CLHEP::um << " um" << G4endl;
    G4cout << "Lower xInWorld: " << xInWorld/cm << "cm" << G4endl;
    G4cout << "Lower yInWorld: " << yInWorld/cm << "cm" << G4endl;
    G4cout << "Lower zInWorld: " << zInWorld/CLHEP::um << " um" << G4endl;
    G4cout << "Lower glue goes from: " << (zInWorld - GetGlueThickness()*0.5)/um << " um to " << (zInWorld + GetGlueThickness()*0.5)/um << " um" << G4endl;
	
    G4Box* solidGlue = new G4Box("solidLowerGlue", GetGlueXDimension()*0.5, GetGlueYDimension()*0.5, GetGlueThickness()*0.5);
    G4LogicalVolume* logicGlue = new G4LogicalVolume(solidGlue, GetGlueMaterial(), "logicLowerGlue", 0);
    MapsFoilDetectorList::AddToLogicalDetectorList(logicGlue);
    G4VisAttributes* green = new G4VisAttributes(G4Colour::Green());
    green->SetVisibility(true);
    logicGlue->SetVisAttributes(green);
    
    //placement of the layer logical volume into its mother frame
    new G4PVPlacement(0, {xInWorld, yInWorld, zInWorld}, logicGlue, "physLowerGlue", worldLog, false, 1, true);

}

//Construction and placement of single glue layer physical volume, covering all the detection system
void Glue::ConstructUpperGlueLayerPV(G4double xInWorld, G4double yInWorld, G4double zInWorld, G4LogicalVolume *worldLog, Alpide* alpide){

    std::vector<G4ThreeVector> padPositions = alpide->GetPadCoordinates();
    
    //G4cout << "Upper glue X: " << GetGlueXDimension()/cm << "cm" << G4endl;
    //G4cout << "Upper glue Y: " << GetGlueYDimension()/cm << "cm" << G4endl;
    G4cout << "Upper glue Z thickness: " << GetGlueThickness()/CLHEP::um << " um" << G4endl;
    G4cout << "Upper xInWorld: " << xInWorld/cm << "cm" << G4endl;
    G4cout << "Upper yInWorld: " << yInWorld/cm << "cm" << G4endl;
    G4cout << "Upper zInWorld: " << zInWorld/CLHEP::um << " um" << G4endl;
    G4cout << "Upper glue goes from: " << (zInWorld - GetGlueThickness()*0.5)/um << " um to " << (zInWorld + GetGlueThickness()*0.5)/um << " um" << G4endl;
	
    G4VSolid* solidGlue = new G4Box("solidGlue", GetGlueXDimension()*0.5, GetGlueYDimension()*0.5, GetGlueThickness()*0.5);
    for(int i = 0; i < alpide->GetNOfPads(); i++){
    
    	G4Tubs* solidPadHole = new G4Tubs("solidPadHole", 0., alpide->GetPadRadius(),GetGlueThickness()*0.5, 0., 360.*degree);
    	G4ThreeVector* translation = new G4ThreeVector(padPositions[i].x(), padPositions[i].y(), padPositions[i].z());
    	solidGlue = new G4SubtractionSolid("solidUpperGlue", solidGlue, solidPadHole, 0, *translation);
    	
    	//logs
    	G4cout << "solidPadHole Z: " 
    		<< padPositions[i].z()+(alpide->GetAlpideThickness()+GetGlueThickness())*0.5/um << " um" << G4endl;
    	G4cout << "solidPadHole goes from: " 
    	<< (padPositions[i].z()+(alpide->GetAlpideThickness()+GetGlueThickness())*0.5 - GetGlueThickness()*0.5)/um << " um to " 
    	<< (padPositions[i].z()+(alpide->GetAlpideThickness()+GetGlueThickness())*0.5 + (GetGlueThickness())*0.5)/um << " um" << G4endl;
    	G4cout << "solidGlue volume: " << solidGlue->GetCubicVolume() << G4endl;
    	
    }
    
    G4LogicalVolume* logicGlue = new G4LogicalVolume(solidGlue, GetGlueMaterial(), "logicUpperGlue", 0);
    MapsFoilDetectorList::AddToLogicalDetectorList(logicGlue);
    G4VisAttributes* green = new G4VisAttributes(G4Colour::Green());
    green->SetVisibility(true);
    logicGlue->SetVisAttributes(green);
    
    //placement of the layer logical volume into its mother frame
    new G4PVPlacement(0, {xInWorld, yInWorld, zInWorld}, logicGlue, "physUpperGlue", worldLog, false, 1, true);

}



/*



//Construction and placement of a glue matrix physical volume.
//The first argument, is a single glue square, which can glue a single silicon chip.
//xDimGluedPad and yDimGlued pad refers to a single silicon chip dimensions.
G4VPhysicalVolume *Glue::ConstructGlueMatrixPhVolume(Glue *glue, G4double xDimGluedPad,
                                                     G4double yDimGluedPad, G4int nOfColumn,
                                                     G4int nOfRows, G4double xInWorld,
                                                     G4double yInWorld, G4double zInWorld,
                                                     G4LogicalVolume *worldLog)
{
    G4NistManager *nist = G4NistManager::Instance();

    if (glue->GetGlueXDimension() > xDimGluedPad || glue->GetGlueYDimension() > yDimGluedPad)
    {
        G4cerr << "  ERROR ConstructGlueMatrixPhVolume() \n"
               << " Glue dimensions exceed the object: are you sure you want it spilt all over? \n"
               << G4endl;
    }
    G4VisAttributes *visAttr = new G4VisAttributes();
    visAttr->SetVisibility(false);

    //solid and logical volume for a single glue square are created here
    G4Box *sGlue = new G4Box("Glue", glue->_glueXDimension * 0.5, glue->_glueYDimension * 0.5,
                             glue->_glueThickness * 0.5);
    G4LogicalVolume *lGlue = new G4LogicalVolume(sGlue, glue->GetGlueMaterial(), "lGlue");
    G4VisAttributes *yellow = new G4VisAttributes(G4Colour::Yellow());
    yellow->SetVisibility(true);
    lGlue->SetVisAttributes(yellow);

    //creation of padToBeGlued envelope solid and logical volumes: its dimensions are equal to the object
    //to be glued ones, i.e. silicon chip in this case; a glue square will be placed inside it.
    G4Box *padToBeGlued = new G4Box("padToBeGlued", xDimGluedPad * 0.5, yDimGluedPad * 0.5,
                                    glue->GetGlueThickness() * 0.5);
    G4LogicalVolume *lPadToBeGlued = new G4LogicalVolume(padToBeGlued, nist->FindOrBuildMaterial("G4_Galactic"),
                                                         "lPadToBeGlued");
    lPadToBeGlued->SetVisAttributes(visAttr);

    //placement of glue inside its envelope
    G4VPhysicalVolume *pGluedPad = new G4PVPlacement(0, {0, 0, 0}, lGlue, "pGluedPad", lPadToBeGlued, 0, 0, 0);

    //creation of glueArray envelope solid and logical volumes: it will contain glue squared in their envelopes
    G4Box *glueArray = new G4Box("glueArray", glue->_glueXDimension * nOfColumn * 0.5,
                                 glue->_glueYDimension * 0.5, glue->_glueThickness * 0.5);
    G4LogicalVolume *lGlueArray = new G4LogicalVolume(glueArray, nist->FindOrBuildMaterial("G4_Galactic"),
                                                      "lGlueArray");
    lGlueArray->SetVisAttributes(visAttr);

    //creation of glueMatrix envelope solid and logical volumes: it will contain glue Arrays
    G4Box *glueMatrix = new G4Box("glueMatrix", xDimGluedPad * 0.5, yDimGluedPad * 0.5,
                                  glue->GetGlueThickness());
    G4LogicalVolume *lGlueMatrix = new G4LogicalVolume(glueMatrix, nist->FindOrBuildMaterial("G4_Galactic"),
                                                       "lGlueMatrix");
    lGlueMatrix->SetVisAttributes(visAttr);


    //glues in their envelope are replicated inside a glueArray, on the x dimension
    G4VPhysicalVolume *replicaPadX = new G4PVReplica("pReplicaX", lPadToBeGlued, lGlueArray, kXAxis,
                                                     nOfColumn, xDimGluedPad);

    //glueArray are replicated inside glueMatrix, on the y dimension
    G4VPhysicalVolume *replicaPadY = new G4PVReplica("pReplicaY", lGlueArray, lGlueMatrix, kYAxis,
                                                     nOfRows, yDimGluedPad);

    //glueMatrix is placed inside its mother volume
    G4VPhysicalVolume *pGlueMatrix = new G4PVPlacement(nullptr, {xInWorld, yInWorld, zInWorld},
                                                       lGlueMatrix, "pGlueMatrix", worldLog, 0, 0, 0);

    return pGlueMatrix;
}


*/
