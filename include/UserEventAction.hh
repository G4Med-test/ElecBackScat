#ifndef USEREVENTACTION_HH
#define USEREVENTACTION_HH

#include "G4Timer.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"

class DetectorConstruction;


class UserEventAction : public G4UserEventAction {

 public:
   UserEventAction(DetectorConstruction* det);
   ~UserEventAction();

   virtual void BeginOfEventAction(const G4Event*);
   virtual void EndOfEventAction(const G4Event* event);

   void ResetTimer() { cpuTime = 0.0; }
   void SetRunID(G4int id) { runID = id; }

 private:
   DetectorConstruction* detector;

   G4int runID;

   G4Timer timerEvent;
   G4double cpuTime;
};

#endif // USEREVENTACTION_HH
