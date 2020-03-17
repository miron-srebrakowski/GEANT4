#include "EnergyCounter.hh"

#include "G4RunManager.hh"
#include "g4csv.hh"

EnergyCounter::EnergyCounter( const G4String& name, const G4int id )
  : G4VSensitiveDetector( name ) // Run the constructor of the parent class
{
  // Set which histogram ID / ntuple column to use
  m_ID = id;
}

EnergyCounter::~EnergyCounter()
{
}

// At the start of the event, zero the energy counter
void EnergyCounter::Initialize( G4HCofThisEvent* )
{
  m_totalEnergy = 0.0;
}

// Analyse anything that hits the detector
G4bool EnergyCounter::ProcessHits( G4Step* step, G4TouchableHistory* )
{
  // Get the energy deposited by this hit
  G4double edep = step->GetTotalEnergyDeposit();

  // Add to the total energy in this object
  m_totalEnergy += edep;

  if(m_ID == 1){
  // Get the analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Fill ntuple with my ID number x and y position.
  analysisManager->FillNtupleDColumn( 1, 2, step->GetTrack()->GetPosition().x()  );                          // Column 1 - phi coordinate of hit
  analysisManager->FillNtupleDColumn( 1, 1, G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()  );
  analysisManager->AddNtupleRow(1); // Row complete

  analysisManager->FillNtupleDColumn( 2, 1, G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()  );                          // Column 1 - phi coordinate of hit
  analysisManager->FillNtupleDColumn( 2, 2, step->GetTrack()->GetPosition().y() );
  analysisManager->AddNtupleRow(2); // Row complete
}

if(m_ID == 2){
// Get the analysis manager
auto analysisManager = G4AnalysisManager::Instance();

analysisManager->FillNtupleDColumn( 3, 2, step->GetTrack()->GetPosition().x()  );                          // Column 1 - phi coordinate of hit
analysisManager->FillNtupleDColumn( 3, 1, G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()  );
analysisManager->AddNtupleRow(3); // Row complete

analysisManager->FillNtupleDColumn( 4, 1, G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()  );                          // Column 1 - phi coordinate of hit
analysisManager->FillNtupleDColumn( 4, 2, step->GetTrack()->GetPosition().y() );
analysisManager->AddNtupleRow(4); // Row complete
}

  return true;
}

// At the end of an event, store the energy collected in this detector
void EnergyCounter::EndOfEvent( G4HCofThisEvent* )
{
  // Display the total
  G4cout << this->GetName() << " total energy = " << m_totalEnergy << G4endl;

  // Get the analysis manager
  auto analysisManager = G4AnalysisManager::Instance();


  // Fill ntuple (ntuple 0, column by layer ID)
  analysisManager->FillNtupleDColumn( 0, m_ID + 1, m_totalEnergy );
}
