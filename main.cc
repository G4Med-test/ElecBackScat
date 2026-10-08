#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGenerator.hh"
#include "UserRunAction.hh"
#include "UserEventAction.hh"
#include "UserTrackingAction.hh"
#include "UserStepAction.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "Materials.hh"
#include "globals.hh"


int main(int argc, char** argv) {

  if(argc != 2) {
     G4cerr << "Error. Wrong number of arguments." << G4endl;
     G4cout << "INFORMATION: Usage " << argv[0] 
            << " macrofile " << G4endl; 
  }

  G4String fileName = argv[1];
  G4String detectorName = "Detector"; 
 	
  G4RunManager* runManager = new G4RunManager;

  Materials::Instance();

  DetectorConstruction* detector = 
                         new DetectorConstruction( detectorName );
  runManager -> SetUserInitialization( detector );  

  PhysicsList* physics = new PhysicsList();
  runManager -> SetUserInitialization( physics );

  PrimaryGenerator* beam = new PrimaryGenerator(); 
  runManager -> SetUserAction( beam );

  UserStepAction* steppingAction = new UserStepAction();
  runManager -> SetUserAction( steppingAction );

  UserTrackingAction* trackingAction = new UserTrackingAction( detectorName );
  runManager -> SetUserAction( trackingAction );

  UserEventAction* eventAction = new UserEventAction( detector );
  runManager -> SetUserAction( eventAction );
     
  UserRunAction* runAction = new UserRunAction( fileName, detector, 
                                                beam, eventAction, 
                                                trackingAction ); 
  runManager -> SetUserAction( runAction );  

  G4UImanager * UI = G4UImanager::GetUIpointer();  
   
  G4cout << "INFORMATION:  Commands in file " << fileName 
         << " used to control simulation" 
         << G4endl; 
  UI -> ApplyCommand("/control/execute " + fileName);

  delete runManager;

  Materials::Destroy();

  return 0;
}
