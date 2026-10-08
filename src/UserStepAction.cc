
#include "UserStepAction.hh"
#include "UserTrackInformation.hh"
#include "G4Step.hh"

UserStepAction::UserStepAction() {}

UserStepAction::~UserStepAction() {}

void UserStepAction::UserSteppingAction(const G4Step* step) {

  G4Track* track = step -> GetTrack();

  if(track -> GetTrackStatus() != fAlive) return;
 
  UserTrackInformation* trackInfo = 
                     (UserTrackInformation*) (track -> GetUserInformation());
  
  trackInfo -> UpdateStep( step );
}


