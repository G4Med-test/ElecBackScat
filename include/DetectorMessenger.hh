#ifndef DETECTORMESSENGER_HH
#define DETECTORMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;


class DetectorMessenger : public G4UImessenger {

 public:
   DetectorMessenger(DetectorConstruction*);
   ~DetectorMessenger();

   void SetNewValue(G4UIcommand*, G4String);

 private:
   DetectorConstruction* detectorConstruction;

   G4UIdirectory* detDirectory;
   G4UIcmdWithADoubleAndUnit* detMaxStepSizeCmd;
   G4UIcmdWithADoubleAndUnit* detLengthCmd;
   G4UIcmdWithADoubleAndUnit* detRadiusCmd;
   G4UIcmdWithAString* detMaterialCmd;
   G4UIcmdWithADoubleAndUnit* detCutCmd;
   G4UIcmdWithADoubleAndUnit* deteScoreCutCmd;
   G4UIcmdWithADouble* detEnAlbTestCmd;
   G4UIcmdWithADouble* detChAlbTestCmd;
};

#endif // DETECTORMESSENGER_HH
