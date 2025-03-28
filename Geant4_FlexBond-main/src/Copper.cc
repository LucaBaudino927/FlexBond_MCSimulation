#include "Copper.hh"

//Notice that: "mother volume" refers to the volume in which the object has to be placed:
//it can be inside other objects or in a more general frame.

//constructor
Copper::Copper(G4double x, G4double y, G4double copperThickness) {

    fCopperThickness = copperThickness;
    fCopperXDimension = x;
    fCopperYDimension = y;
    
}

//destructor
Copper::~Copper(){};

//Construction and placement of single copper layer physical volume, covering all the detection system
void Copper::ConstructCopperLayerPV(G4double xInWorld, G4double yInWorld, G4double zInWorld, G4AssemblyVolume* assemblyDetector)
{

    G4Box* solidCopper = new G4Box("solidCopper", GetCopperXDimension()*0.5, GetCopperYDimension()*0.5, GetCopperThickness()*0.5);
    G4LogicalVolume* logicCopper = new G4LogicalVolume(solidCopper, GetCopperMaterial(), "logicCopper");
    MapsFoilDetectorList::AddToLogicalDetectorList(logicCopper);
    G4VisAttributes* red = new G4VisAttributes(G4Colour::Red());
    red->SetVisibility(true);
    logicCopper->SetVisAttributes(red);
   
    G4cout << "CopperThickness: " << GetCopperThickness()/um << " um" << G4endl;
    G4cout << "Copper Z center: " << zInWorld/um << " um" << G4endl;
    G4cout << "Copper Z goes from: " << (zInWorld - GetCopperThickness()*0.5)/um << " um to " << (zInWorld + GetCopperThickness()*0.5)/um << " um" << G4endl;
    
    // Rotation and translation of a plate inside the assembly
    G4RotationMatrix Ra;
    G4ThreeVector Ta;
    G4Transform3D Tr;

    // Fill the assembly by the plates
    Ta.setX(xInWorld); 
    Ta.setY(yInWorld);
    Ta.setZ(zInWorld);
    Tr = G4Transform3D(Ra,Ta);
    assemblyDetector->AddPlacedVolume(logicCopper, Tr);
    
    //placement of the layer logical volume into its mother frame
    //new G4PVPlacement(0, {xInWorld, yInWorld, zInWorld}, logicCopper, "physCopper", worldLog, false, 1, true);
    
    	/*G4cout << "copper half X: " << solidCopper->GetXHalfLength() << G4endl;
	G4cout << "copper half Y: " << solidCopper->GetYHalfLength() << G4endl;
	G4cout << "copper half Z: " << solidCopper->GetZHalfLength()/CLHEP::um << " um" << G4endl;
    	G4cout << "xInWorld: " << xInWorld << G4endl;
	G4cout << "yInWorld: " << yInWorld << G4endl;
	G4cout << "zInWorld: " << zInWorld/CLHEP::um << " um" << G4endl;*/

}



/*



//Construction and placement of a copper matrix physical volume.
//The first argument, is a single copper square, which can copper a single silicon chip.
//xDimCopperdPad and yDimCopperd pad refers to a single silicon chip dimensions.
G4VPhysicalVolume *Copper::ConstructCopperMatrixPhVolume(Copper *copper, G4double xDimCopperdPad,
                                                     G4double yDimCopperdPad, G4int nOfColumn,
                                                     G4int nOfRows, G4double xInWorld,
                                                     G4double yInWorld, G4double zInWorld,
                                                     G4LogicalVolume *worldLog)
{
    G4NistManager *nist = G4NistManager::Instance();

    if (copper->GetCopperXDimension() > xDimCopperdPad || copper->GetCopperYDimension() > yDimCopperdPad)
    {
        G4cerr << "  ERROR ConstructCopperMatrixPhVolume() \n"
               << " Copper dimensions exceed the object: are you sure you want it spilt all over? \n"
               << G4endl;
    }
    G4VisAttributes *visAttr = new G4VisAttributes();
    visAttr->SetVisibility(false);

    //solid and logical volume for a single copper square are created here
    G4Box *sCopper = new G4Box("Copper", copper->_copperXDimension * 0.5, copper->_copperYDimension * 0.5,
                             copper->_copperThickness * 0.5);
    G4LogicalVolume *lCopper = new G4LogicalVolume(sCopper, copper->GetCopperMaterial(), "lCopper");
    G4VisAttributes *yellow = new G4VisAttributes(G4Colour::Yellow());
    yellow->SetVisibility(true);
    lCopper->SetVisAttributes(yellow);

    //creation of padToBeCopperd envelope solid and logical volumes: its dimensions are equal to the object
    //to be copperd ones, i.e. silicon chip in this case; a copper square will be placed inside it.
    G4Box *padToBeCopperd = new G4Box("padToBeCopperd", xDimCopperdPad * 0.5, yDimCopperdPad * 0.5,
                                    copper->GetCopperThickness() * 0.5);
    G4LogicalVolume *lPadToBeCopperd = new G4LogicalVolume(padToBeCopperd, nist->FindOrBuildMaterial("G4_Galactic"),
                                                         "lPadToBeCopperd");
    lPadToBeCopperd->SetVisAttributes(visAttr);

    //placement of copper inside its envelope
    G4VPhysicalVolume *pCopperdPad = new G4PVPlacement(0, {0, 0, 0}, lCopper, "pCopperdPad", lPadToBeCopperd, 0, 0, 0);

    //creation of copperArray envelope solid and logical volumes: it will contain copper squared in their envelopes
    G4Box *copperArray = new G4Box("copperArray", copper->_copperXDimension * nOfColumn * 0.5,
                                 copper->_copperYDimension * 0.5, copper->_copperThickness * 0.5);
    G4LogicalVolume *lCopperArray = new G4LogicalVolume(copperArray, nist->FindOrBuildMaterial("G4_Galactic"),
                                                      "lCopperArray");
    lCopperArray->SetVisAttributes(visAttr);

    //creation of copperMatrix envelope solid and logical volumes: it will contain copper Arrays
    G4Box *copperMatrix = new G4Box("copperMatrix", xDimCopperdPad * 0.5, yDimCopperdPad * 0.5,
                                  copper->GetCopperThickness());
    G4LogicalVolume *lCopperMatrix = new G4LogicalVolume(copperMatrix, nist->FindOrBuildMaterial("G4_Galactic"),
                                                       "lCopperMatrix");
    lCopperMatrix->SetVisAttributes(visAttr);


    //coppers in their envelope are replicated inside a copperArray, on the x dimension
    G4VPhysicalVolume *replicaPadX = new G4PVReplica("pReplicaX", lPadToBeCopperd, lCopperArray, kXAxis,
                                                     nOfColumn, xDimCopperdPad);

    //copperArray are replicated inside copperMatrix, on the y dimension
    G4VPhysicalVolume *replicaPadY = new G4PVReplica("pReplicaY", lCopperArray, lCopperMatrix, kYAxis,
                                                     nOfRows, yDimCopperdPad);

    //copperMatrix is placed inside its mother volume
    G4VPhysicalVolume *pCopperMatrix = new G4PVPlacement(nullptr, {xInWorld, yInWorld, zInWorld},
                                                       lCopperMatrix, "pCopperMatrix", worldLog, 0, 0, 0);

    return pCopperMatrix;
}


*/
