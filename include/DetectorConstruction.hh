#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "globals.hh"

class DetectorMessenger;
class DetectorSV;
class G4VPhysicalVolume;
class G4Box;
class G4Tubs;
class G4UserLimits;
class G4ProductionCuts;


class DetectorConstruction : public G4VUserDetectorConstruction {
      
public:
  DetectorConstruction(const G4String& detectorName);
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume* Construct();   

  void SetMaxStepSize(G4double max);
  void SetRadius(G4double length);
  void SetThickness(G4double thickn);
  void SetMaterial(G4String name);
  void SetProductionCut(G4double cut);
  void SetAlbedoCut(G4double cut);
  void SetTestEnergyAlbedo(G4double en);
  void SetTestChargeAlbedo(G4double no);

  inline const G4Material* GetMaterial() const;

  void ResetForRun();
  void CloseEvent();
  void Print(std::ostream& os, G4int primEvents);
  void PrintUnformatted(std::ostream& os, G4int primEvents);

private:
  DetectorMessenger* messenger;

  // Offset world volume from detector
  G4double worldOffset;

  // Detector name
  G4String detName;

  // Physical volumes
  G4VPhysicalVolume* worldVolPhys;
  G4VPhysicalVolume* detVolPhys;

  // Logical volumes
  G4LogicalVolume* worldVolLogic; 
  G4LogicalVolume* detVolLogic;

  // Solid volumes
  G4Box* worldVolSolid;
  G4Tubs* detVolSolid;
 
  // SV
  DetectorSV* detSV; 
 
  // Other
  G4UserLimits* detVolUserLimits;
  G4ProductionCuts* detProdCuts;
};

inline const G4Material* DetectorConstruction::GetMaterial() const
{
  return detVolLogic->GetMaterial();
}

#endif // DETECTORCONSTRUCTION_HH
