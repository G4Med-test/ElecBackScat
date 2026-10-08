
#include "UserEventAction.hh"
#include "DetectorConstruction.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include <sstream>
#include <fstream>


UserEventAction::UserEventAction(DetectorConstruction* det) :
   detector( det ),
   cpuTime(0) {

}


UserEventAction::~UserEventAction() {

}


void UserEventAction::BeginOfEventAction(const G4Event*) {

  timerEvent.Start();
}


void UserEventAction::EndOfEventAction(const G4Event* event) {

  timerEvent.Stop();

  G4double cpuTimeLastEvent = 
               timerEvent.GetUserElapsed() + timerEvent.GetSystemElapsed();

  cpuTime += cpuTimeLastEvent;

  G4int nmbEvents = event -> GetEventID() + 1;

  if(!(nmbEvents % 100000)) {
     G4cout << "INFORMATION: Total CPU time last event = " 
            << cpuTimeLastEvent << " sec"
            << G4endl 
            << "INFORMATION: " << nmbEvents << " events processed." 
            << G4endl
            << "INFORMATION: Average CPU time per event "
            << "(user + system elapsed) = " 
            << cpuTime/(G4double(nmbEvents)) 
            << " sec"
            << G4endl;
  }

  detector -> CloseEvent();

  if(!(nmbEvents % 100000)) {

     std::stringstream ss;
     ss << nmbEvents;
     std::stringstream r;
     r << (runID + 1);
     G4String fileName = "tmp_" + ss.str() + "events_" + "runNo" + r.str();
     
     std::ofstream ofilestream( (fileName + ".dat").c_str() );
     if( !ofilestream ) {
        G4cerr << "ERROR: Cannot open file " 
               << fileName << " for writing."  
               << G4endl;
     }
     else {
        detector -> Print( ofilestream, 1 );  
        ofilestream.close();  
     }
  }
}
