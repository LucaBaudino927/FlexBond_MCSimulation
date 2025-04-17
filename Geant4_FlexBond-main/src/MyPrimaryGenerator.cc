#include "MyPrimaryGenerator.hh"

MyPrimaryGenerator::MyPrimaryGenerator(){
	
	G4int nofParticles = 1; //# of primary particle per event
	fParticleGun = new G4ParticleGun(nofParticles); 
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	
	fElectron = particleTable->FindParticle("e-");
	fPositron = particleTable->FindParticle("e+");
	fKaon = particleTable->FindParticle("kaon+");
	fNeutron = particleTable->FindParticle("neutron");
	fProton = particleTable->FindParticle("proton");

	fParticleGun->SetParticlePosition(G4ThreeVector(0., Y_BeamPosition, -2.*cm));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
	//fParticleGun->SetParticleMomentum(fMomentum);

	// default particle: electron, p = 10 MeV along Z
	auto electronMass = fElectron->GetPDGMass();
	auto electronKinEnergy = std::sqrt(fMomentum * fMomentum + electronMass * electronMass) - electronMass;
	fParticleGun->SetParticleEnergy(electronKinEnergy);
	fParticleGun->SetParticleDefinition(fElectron);

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
				particle = fElectron;
				break;
			case 1:
				particle = fPositron;
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
		fParticleGun->SetParticlePosition(G4ThreeVector(0., Y_BeamPosition, -2.*cm));
		auto pp = fMomentum + (G4UniformRand() - 0.5) * fSigmaMomentum;
		//fParticleGun->SetParticleMomentum(pp);
		auto mass = particle->GetPDGMass();
		auto ekin = std::sqrt(pp * pp + mass * mass) - mass;
		fParticleGun->SetParticleEnergy(ekin);
		auto angle = (G4UniformRand() - 0.5) * fSigmaAngle;
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(std::sin(angle), 0., std::cos(angle)));
	} else {
		particle = fParticleGun->GetParticleDefinition();
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
		//fParticleGun->SetParticleMomentum(fMomentum);
		auto Mass = particle->GetPDGMass();
		auto KinEnergy = std::sqrt(fMomentum * fMomentum + Mass * Mass) - Mass;
		fParticleGun->SetParticleEnergy(KinEnergy);	
		fParticleGun->SetParticlePosition(G4ThreeVector(0., Y_BeamPosition, -2.*cm));
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
	
	// beamPosition command
	auto& beamPositionCmd = fMessenger->DeclarePropertyWithUnit("beamPosition", "mm", Y_BeamPosition, "Y coordinate of the beam in mm");
	beamPositionCmd.SetParameterName("bp", true);
	//beamPositionCmd.SetRange("bm>=0.");
	beamPositionCmd.SetDefaultValue("-7.4");
  
}

