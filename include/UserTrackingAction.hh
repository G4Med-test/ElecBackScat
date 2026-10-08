#ifndef USERTRACKINGACTION_HH
#define USERTRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "globals.hh"


class UserTrackingAction : public G4UserTrackingAction {

 public:
   UserTrackingAction(const G4String& detectorName);
   ~UserTrackingAction();

   void PreUserTrackingAction(const G4Track*);
   void PostUserTrackingAction(const G4Track*);

   void Print();
   void ResetCounter() { elecBorninWorld = 0; elecDiedinWorld = 0; 
                         elecBorninDet = 0; elecDiedinDet = 0; }

 private:
   G4String detName;

   G4int elecBorninWorld;
   G4int elecDiedinWorld;
   G4int elecBorninDet;
   G4int elecDiedinDet;
};

#endif // USERTRACKINGACTION_HH
