#include "MyPrimaryGenerator.hh"

MyPrimaryGenerator::MyPrimaryGenerator(){
	
	G4int nofParticles = 1; //# of primary particle per event
	fParticleGun = new G4ParticleGun(nofParticles); 
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	
	fPositron = particleTable->FindParticle("e+");
	fElectron = particleTable->FindParticle("e-");
	fKaon = particleTable->FindParticle("kaon+");
	fNeutron = particleTable->FindParticle("neutron");
	fProton = particleTable->FindParticle("proton");

	fParticleGun->SetParticlePosition(G4ThreeVector(0., -7.*mm, -2.*cm));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	fParticleGun->SetParticleMomentum(fMomentum);// set 0 for radioactive decay. 500 for cherenkov

	// default particle: positron, p = 10 MeV along Z
	auto positronMass = fPositron->GetPDGMass();
	auto positronKinEnergy = std::sqrt(fMomentum * fMomentum + positronMass * positronMass) - positronMass;
	fParticleGun->SetParticleEnergy(positronKinEnergy);
	fParticleGun->SetParticleDefinition(fPositron);

	// define commands for this class
	DefineCommands();

}

// ######## Destructor 
MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
  delete fMessenger;
}

// ######## Generate primary particle 
void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent){

        G4ParticleDefinition* particle;
	if (fRandomizePrimary) {
		auto i = (int)(5. * G4UniformRand());
		switch (i) {
			case 0:
				particle = fPositron;
				break;
			case 1:
				particle = fElectron;
				break;
			case 2:
				particle = fKaon;
				break;
			case 3:
				particle = fNeutron;
				break;
			default:
				particle = fProton;
				break;
		}
		fParticleGun->SetParticleDefinition(particle);
		auto pp = fMomentum + (G4UniformRand() - 0.5) * fSigmaMomentum;
		auto mass = particle->GetPDGMass();
		auto ekin = std::sqrt(pp * pp + mass * mass) - mass;
		fParticleGun->SetParticleEnergy(ekin);
		auto angle = (G4UniformRand() - 0.5) * fSigmaAngle;
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(std::sin(angle), 0., std::cos(angle)));
	} else {
		particle = fParticleGun->GetParticleDefinition();
	}

        fParticleGun->GeneratePrimaryVertex(anEvent);
        
}

void MyPrimaryGenerator::DefineCommands()
{
	// Define /generator command directory using generic messenger class
	fMessenger = new G4GenericMessenger(this, "/generator/", "Primary generator control");

	// randomizePrimary command
	auto& randomCmd = fMessenger->DeclareProperty("randomizePrimary", fRandomizePrimary);
	G4String guidance = "Boolean flag for randomizing primary particle types.\n";
	guidance 	 += "In case this flag is false, you can select the primary particle\n";
	guidance	 += " with /gun/particle command.";
	randomCmd.SetGuidance(guidance);
	randomCmd.SetParameterName("flag", true);
	randomCmd.SetDefaultValue("false");
	
	// momentum command
	auto& momentumCmd = fMessenger->DeclarePropertyWithUnit("momentum", "MeV", fMomentum, "Mean momentum of primaries in MeV");
	momentumCmd.SetParameterName("p", true);
	momentumCmd.SetRange("p>=0.");
	momentumCmd.SetDefaultValue("10.");

	// sigmaMomentum command
	auto& sigmaMomentumCmd = fMessenger->DeclarePropertyWithUnit("sigmaMomentum", "MeV", fSigmaMomentum, "Sigma momentum of primaries in MeV");
	sigmaMomentumCmd.SetParameterName("sp", true);
	sigmaMomentumCmd.SetRange("sp>=0.");
	sigmaMomentumCmd.SetDefaultValue("1.");

	// sigmaAngle command
	auto& sigmaAngleCmd = fMessenger->DeclarePropertyWithUnit("sigmaAngle", "deg", fSigmaAngle, "Sigma angle divergence of primaries in degree");
	sigmaAngleCmd.SetParameterName("t", true);
	sigmaAngleCmd.SetRange("t>=0.");
	sigmaAngleCmd.SetDefaultValue("1.");
  
}

