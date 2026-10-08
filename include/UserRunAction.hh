#ifndef USERRUNACTION_HH
#define USERRUNACTION_HH

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"

class DetectorConstruction;
class PrimaryGenerator;
class UserEventAction;
class UserTrackingAction;


class UserRunAction : public G4UserRunAction {

 public:
   UserRunAction(const G4String& fileName,
                 DetectorConstruction* det, 
                 PrimaryGenerator* bm,
                 UserEventAction* evAction,
                 UserTrackingAction* trAction);
   ~UserRunAction() { }

   virtual void BeginOfRunAction(const G4Run* run);
   virtual void EndOfRunAction(const G4Run* run);

 private:
   G4String fileNameBase;

   DetectorConstruction* detector;
   PrimaryGenerator* beam;
   UserEventAction* eventAction;
   UserTrackingAction* trackAction;
};

#endif // USERRUNACTION_HH
