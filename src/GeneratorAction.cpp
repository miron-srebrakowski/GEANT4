#include "GeneratorAction.hh"

#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4csv.hh"

GeneratorAction::GeneratorAction() : G4VUserPrimaryGeneratorAction()
{
  G4int nofParticles = 1;
  m_particleGun = new G4ParticleGun( nofParticles );

  // Default particle
  G4ParticleDefinition * particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle( "e-" );
  m_particleGun->SetParticleDefinition( particleDefinition );
  m_particleGun->SetParticlePosition( G4ThreeVector( 0.0, 0.0, -250.0*cm ) ); // right in the middle
  m_particleGun->SetParticleMomentumDirection( G4ThreeVector( 0.0, 0.0, 1.0 ) ); // along z axis
  m_particleGun->SetParticleEnergy( 300.0*MeV );
}

GeneratorAction::~GeneratorAction()
{
  delete m_particleGun;
}

// This function is called at the begining of event
void GeneratorAction::GeneratePrimaries( G4Event* anEvent )
{
  // Fire a particle
  m_particleGun->GeneratePrimaryVertex( anEvent );

  // Store truth information
  auto analysisManager = G4AnalysisManager::Instance();
  G4double particleEnergy = m_particleGun->GetParticleEnergy();
  analysisManager->FillNtupleDColumn( 0, 0, particleEnergy );

  std::string particleName = m_particleGun->GetParticleDefinition()->GetParticleName();

  if(particleName == "e-"){
      analysisManager->FillNtupleDColumn( 0, 1, 1 );
  }
  else if(particleName == "mu+"){
      analysisManager->FillNtupleDColumn( 0, 1, 2 );
  }
  else if(particleName == "mu-"){
    analysisManager->FillNtupleDColumn( 0, 1, 3 );
  }
  else if(particleName == "proton"){
    analysisManager->FillNtupleDColumn( 0, 1, 4 );
  }
  else {
    analysisManager->FillNtupleDColumn( 0, 1, 0 );
  }

  //Increase particle energy
  //G4double nextEnergy = particleEnergy + 100.0*MeV;
  //m_particleGun->SetParticleEnergy( nextEnergy );
}
