#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4MTRunManager.hh"
#include "QGSP_BERT.hh"//for hadronic processes

// User defined
#include "construction.hh"
#include "physics.hh"
#include "action.hh"

//main take directly argc and argv from the command line -> ./sim ciccio.mac -> argc = 2, argv = {./sim, ciccio.mac}. argv[1]=ciccio.mac. Note: char** argv = char* argv[]
int main(int argc, char** argv){

    	// ######## runManager initialization. 

        #ifdef G4MULTITHREADED
            G4MTRunManager* runManager = new G4MTRunManager;
        #else
            G4RunManager* runManager = new G4RunManager;
        #endif

    	// ######## This is the real simulation architecture construction 

        //First: construction -> creates detectors 
        runManager->SetUserInitialization(new MyDetectorConstruction);//construction.hh
        //Second: physics
        runManager->SetUserInitialization(new MyPhysicsList);//physics.hh
        //Third: action -> 1. generator, 2. run, 3. event, 4. stepping 
        runManager->SetUserInitialization(new MyActionInitialization);//action.hh

        //Only for cosmic showers in the atmosphere. It takes into account hadronic decays. 
        //G4VModularPhysicsList *physics = new QGSP_BERT();
        //physics->RegisterPhysics(new G4DecayPhysics());//decadimento dei pioni, mesoni, ecc...
        //runManager->SetUserInitialization(physics);

    	// ######## UI interface initialization. Argc = number of argument calls when writing ./sim in the terminal. ./sim ciccio.mac -> argc=2. 

        G4UIExecutive* ui = 0;

        if(argc==1){//no argument after ./sim 
            ui = new G4UIExecutive(argc,argv);
        }

        G4VisManager * visManager = new G4VisExecutive();
        visManager->Initialize(); 
        G4UImanager* UImanager = G4UImanager::GetUIpointer();  

        if(ui){//no argument after ./sim
            UImanager->ApplyCommand("/control/execute vis.mac");
            ui->SessionStart();
        }else{//a file is called after ./sim, e.g. ./sim ciccio.mac
            G4String command = "/control/execute ";
            G4String fileName = argv[1];
            UImanager->ApplyCommand(command+fileName);
        }

        return 0;
}
