#include "physics.hh"

// ######## Physics libraries constructor 

    MyPhysicsList::MyPhysicsList(){

        RegisterPhysics(new G4EmStandardPhysics());//Em interactions, no hadron interactions. 
        RegisterPhysics(new G4OpticalPhysics());//For optical photon propagation in the scintillators.
        RegisterPhysics(new G4DecayPhysics());
        RegisterPhysics(new G4RadioactiveDecayPhysics());//For 60Co

    }

// ######## Destructor 
   
    MyPhysicsList::~MyPhysicsList(){}



