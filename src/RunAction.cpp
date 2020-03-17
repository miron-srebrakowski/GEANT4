#include "RunAction.hh"

#include "g4csv.hh"

RunAction::RunAction() : G4UserRunAction()
{
  // Set number of layers
  G4int const layerNumber = 8;

  // Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();


  // Add an ntuple for energy deposits (ntuple id 0)
  analysisManager->CreateNtuple( "Energy", "Deposited energy" );
  analysisManager->CreateNtupleDColumn( "Generated" );
  analysisManager->CreateNtupleDColumn( "Particle" );
  for ( unsigned int layerIndex = 1; layerIndex <= layerNumber; ++layerIndex )
  {
    std::string columnName = "Layer" + std::to_string( layerIndex );
    analysisManager->CreateNtupleDColumn( columnName );
  }
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple( "Tracker1_x", "x Position on trackers1" );
  analysisManager->CreateNtupleDColumn( "-" );
  analysisManager->CreateNtupleDColumn( "EventID" );
  analysisManager->CreateNtupleDColumn( "x" );
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple( "Tracker1_y", "y Position on trackers1" );
  analysisManager->CreateNtupleDColumn( "-" );
  analysisManager->CreateNtupleDColumn( "EventID" );
  analysisManager->CreateNtupleDColumn( "y" );
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple( "Tracker2_x", "x Position on trackers2" );
  analysisManager->CreateNtupleDColumn( "-" );
  analysisManager->CreateNtupleDColumn( "EventID" );
  analysisManager->CreateNtupleDColumn( "x" );
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple( "Tracker2_y", "y Position on trackers2" );
  analysisManager->CreateNtupleDColumn( "-" );
  analysisManager->CreateNtupleDColumn( "EventID" );
  analysisManager->CreateNtupleDColumn( "y" );
  analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{
  // Delete analysis manager
  delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction( const G4Run* )
{
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  analysisManager->OpenFile( "data/output.csv" );
}

void RunAction::EndOfRunAction( const G4Run* )
{
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Save output data
  analysisManager->Write();
  analysisManager->CloseFile();
}
