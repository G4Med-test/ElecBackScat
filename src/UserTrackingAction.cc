
#include "UserTrackingAction.hh"
#include "UserTrackInformation.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4Electron.hh"
#include "G4VPhysicalVolume.hh"

//#define PRINT_CSDA

G4Allocator<UserTrackInformation> UserTrackInformationAllocator;


UserTrackingAction::UserTrackingAction(const G4String& detectorName) :
  detName( detectorName ),
  elecBorninWorld( 0 ),
  elecDiedinWorld( 0 ),
  elecBorninDet( 0 ),
  elecDiedinDet( 0 ) {

}


UserTrackingAction::~UserTrackingAction() {

}


void UserTrackingAction::PreUserTrackingAction(const G4Track* track) {

  fpTrackingManager -> SetUserTrackInformation(new UserTrackInformation);

  G4ParticleDefinition* particle = track -> GetDefinition();

  if( particle == G4Electron::Definition() ) {
 
      G4VPhysicalVolume* vol = track -> GetVolume();
      G4String name = vol -> GetName();

      if(name == detName) elecBorninDet++;
      else elecBorninWorld++;
  }  

}


void UserTrackingAction::PostUserTrackingAction(const G4Track* track) {

  G4ParticleDefinition* particle = track -> GetDefinition();

  if( particle == G4Electron::Definition() ) {
 
      G4VPhysicalVolume* vol = track -> GetVolume();
      G4String name = vol -> GetName();

      if(name == detName) elecDiedinDet++;
      else elecDiedinWorld++;
  }  

#ifdef PRINT_CSDA

  if( track -> GetTrackID() ==  1) {
  
     G4cout << "Primary stopped at " << track -> GetPosition() << G4endl;
  }

#endif

}


void UserTrackingAction::Print() {

  G4cout << "INFORMATION: Tracking: " 
         << elecBorninWorld << "/" << elecDiedinWorld 
         << " e- created/stopped in world, "
         << elecBorninDet << "/" << elecDiedinDet 
         << " e- created/stopped in detector"
	 << G4endl;
}

