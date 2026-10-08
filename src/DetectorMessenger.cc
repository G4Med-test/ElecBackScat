
#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"


DetectorMessenger::DetectorMessenger(DetectorConstruction* detConstr) :
    detectorConstruction(detConstr) {

  detDirectory = new G4UIdirectory("/detector/");
  detDirectory -> SetGuidance("Detector related commands");

  detMaxStepSizeCmd = 
                  new G4UIcmdWithADoubleAndUnit("/detector/maxStepSize",this);
  detMaxStepSizeCmd -> SetGuidance("Maximum step size in detector");
  detMaxStepSizeCmd -> SetParameterName("maxstepsize", false);
  detMaxStepSizeCmd -> SetRange("maxstepsize>0.");
  detMaxStepSizeCmd -> SetUnitCategory("Length");
  detMaxStepSizeCmd -> AvailableForStates(G4State_Idle);

  detLengthCmd = new G4UIcmdWithADoubleAndUnit("/detector/length",this);
  detLengthCmd -> SetGuidance("Detector Length");
  detLengthCmd -> SetParameterName("length", false);
  detLengthCmd -> SetRange("length>0.");
  detLengthCmd -> SetUnitCategory("Length");
  detLengthCmd -> AvailableForStates(G4State_Idle);

  detRadiusCmd = new G4UIcmdWithADoubleAndUnit("/detector/radius",this);
  detRadiusCmd -> SetGuidance("Detector Radius");
  detRadiusCmd -> SetParameterName("radius", false);
  detRadiusCmd -> SetRange("radius>0.");
  detRadiusCmd -> SetUnitCategory("Length");
  detRadiusCmd -> AvailableForStates(G4State_Idle);

  detMaterialCmd = new G4UIcmdWithAString("/detector/material",this);
  detMaterialCmd -> SetGuidance("Detector material");
  detMaterialCmd -> SetParameterName("material", false);
  detMaterialCmd -> AvailableForStates(G4State_Idle);

  detCutCmd = new G4UIcmdWithADoubleAndUnit("/detector/prodCut",this);
  detCutCmd -> SetGuidance("Production cut in detector");
  detCutCmd -> SetParameterName("prodcut", false);
  detCutCmd -> SetRange("prodcut>0.");
  detCutCmd -> SetUnitCategory("Length");
  detCutCmd -> AvailableForStates(G4State_Idle);

  deteScoreCutCmd = new G4UIcmdWithADoubleAndUnit("/detector/albedoElecCutEnergy",this);
  deteScoreCutCmd -> SetGuidance("Lower cut for scoring albedos");
  deteScoreCutCmd -> SetParameterName("albcut", false);
  deteScoreCutCmd -> SetRange("albcut>=0.");
  deteScoreCutCmd -> SetUnitCategory("Energy");
  deteScoreCutCmd -> AvailableForStates(G4State_Idle);

  detEnAlbTestCmd = new G4UIcmdWithADouble("/detector/energyAlbedoTestValue",this);
  detEnAlbTestCmd -> SetGuidance("Testing energy albedo value");
  detEnAlbTestCmd -> SetParameterName("alben", false);
  detEnAlbTestCmd -> SetRange("alben>=0.");
  detEnAlbTestCmd -> AvailableForStates(G4State_Idle);

  detChAlbTestCmd = new G4UIcmdWithADouble("/detector/chargeAlbedoTestValue",this);
  detChAlbTestCmd -> SetGuidance("Testing charge albedo value");
  detChAlbTestCmd -> SetParameterName("albch", false);
  detChAlbTestCmd -> SetRange("albch>=0.");
  detChAlbTestCmd -> AvailableForStates(G4State_Idle);
}


DetectorMessenger::~DetectorMessenger() {
 
  delete detMaxStepSizeCmd;
  delete detEnAlbTestCmd;
  delete detChAlbTestCmd;
  delete deteScoreCutCmd;
  delete detCutCmd;
  delete detLengthCmd;
  delete detRadiusCmd;
  delete detMaterialCmd;
  delete detDirectory;
}


void DetectorMessenger::SetNewValue(G4UIcommand* cmd, G4String val) {

  if(cmd == detMaxStepSizeCmd) {
     detectorConstruction -> SetMaxStepSize(
                               detMaxStepSizeCmd -> GetNewDoubleValue(val));
  }
  if(cmd == detLengthCmd) {
     detectorConstruction -> SetThickness(
                               detLengthCmd -> GetNewDoubleValue(val));
  }
  if(cmd == detRadiusCmd) {
     detectorConstruction -> SetRadius(
                               detRadiusCmd -> GetNewDoubleValue(val));
  }
  if(cmd == detMaterialCmd) {
     detectorConstruction -> SetMaterial(val);
  } 
  if(cmd == detCutCmd) {
     detectorConstruction -> SetProductionCut(
                               detCutCmd -> GetNewDoubleValue(val));
  }
  if(cmd == deteScoreCutCmd) {
     detectorConstruction -> SetAlbedoCut(
                               deteScoreCutCmd -> GetNewDoubleValue(val));
  }
  if(cmd == detEnAlbTestCmd) {
     detectorConstruction -> SetTestEnergyAlbedo(
                               detEnAlbTestCmd -> GetNewDoubleValue(val));
  }
  if(cmd == detChAlbTestCmd) {
     detectorConstruction -> SetTestChargeAlbedo(
                               detChAlbTestCmd -> GetNewDoubleValue(val));
  }
}
