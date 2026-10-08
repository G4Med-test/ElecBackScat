#ifndef DETECTORSV_HH
#define DETECTORSV_HH

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class G4Electron;
class G4Gamma;
class DetectorScore;


class DetectorSV : public G4VSensitiveDetector {

 public:
   DetectorSV(const G4String& name); 
   virtual ~DetectorSV();

   virtual void Initialize(G4HCofThisEvent*) { }
   virtual void EndOfEvent(G4HCofThisEvent*) { }

   void Print(std::ostream& os, G4int primEvents); // Prints all records
   void PrintUnformatted(std::ostream& os, G4int primEvents);
   void ResetForRun(); // Clears all records for new run
   void CloseEvent(); // Perform error calculations for event

   void SetTestEnergyAlbedo(G4double en) { testReflEnFrac = en; }
   void SetTestChargeAlbedo(G4double no) { testReflNoFrac = no; }

   void SetAlbedoCut(G4double cut);

 protected:
   virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*);

 private:
   G4Electron* elec;
   G4Gamma* gam;

   DetectorScore* elecScore;
   DetectorScore* gamScore;
   DetectorScore* othScore;

   G4double testReflEnFrac;
   G4double testReflNoFrac;
}; 

#endif // DETECTORSV_HH
