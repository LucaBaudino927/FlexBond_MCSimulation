#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator(){

    fParticleGun = new G4ParticleGun(1);//1 primary paerticle per event 
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "e-";//Set "proton" except in 60Co. Set "geantino" for 60Co, i.e. a general particle placeholder. If not replaces, 60Co decay taken into account.
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
    //G4ThreeVector pos (0.,0.,0.*km); // only for cosmic ray shower
    G4ThreeVector pos (0.,0.,-5*cm);
    G4ThreeVector mom (0.,0.,1.);// Particle along Z axis. 

    double Energy = 10;

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(Energy*keV);// set 0 for radioactive decay. 500 for cherenkov
    fParticleGun->SetParticleDefinition(particle);

}

// ######## Destructor 

    MyPrimaryGenerator::~MyPrimaryGenerator(){
        delete fParticleGun;
    }

// ######## Generate primary particle 

    void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent){

        G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();

        // ######## Only for 60Co decay for PET detector. User definition of the source

            if(particle == G4Geantino::Geantino())//decision if 60Co or not
            {   
                std::cout << "60Co decay was chosen"<< std::endl;
                G4int Z = 27;//protons
                G4int A = 60;//protons+neutrons
                G4double charge   = 0.*eplus;//neutral ion
                G4double energy = 0.*keV;//foundamental state
                G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,energy);
                fParticleGun->SetParticleDefinition(ion);
                fParticleGun->SetParticleCharge(charge);
            }

        fParticleGun->GeneratePrimaryVertex(anEvent); 
    }

