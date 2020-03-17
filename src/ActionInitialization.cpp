#include "ActionInitialization.hh"
#include "GeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization()
{
}

ActionInitialization::~ActionInitialization()
{
}

// Three actions to set up
// - generating particles
// - controlling the whole run
// - controlling a single event
void ActionInitialization::Build() const
{
  this->SetUserAction( new GeneratorAction() );
  this->SetUserAction( new RunAction() );
  this->SetUserAction( new EventAction() );
}  
