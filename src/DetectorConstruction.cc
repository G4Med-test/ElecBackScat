
#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "DetectorSV.hh"
#include "Materials.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Material.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4ProductionCuts.hh"
#include "G4SystemOfUnits.hh"


DetectorConstruction::DetectorConstruction(const G4String& detectorName) : 
    messenger(0),
    worldOffset( 1.0 * mm ),
    detName(detectorName),
    worldVolPhys(0),
    detVolPhys(0),
    worldVolLogic(0),
    detVolLogic(0),
    worldVolSolid(0),
    detVolSolid(0),
    detSV( 0 ),
    detVolUserLimits(0),
    detProdCuts(0) {

  messenger = new DetectorMessenger( this );
}


DetectorConstruction::~DetectorConstruction() {
 
  delete messenger;

  if(detVolLogic != 0) delete detVolLogic;  // Can be deleted by user
  if(detVolPhys != 0) delete detVolPhys;    // Can be deleted by user
  // Sensitive detector will be deleted by logical volume

  delete detVolUserLimits;
  delete detProdCuts;
}


G4VPhysicalVolume* DetectorConstruction::Construct() {
 
  G4double detThickn = 10.0 * mm; 
  G4double detRadius = 10.0 * mm;

  // **** World volume ***

  G4double worldZHalfSize = detThickn + worldOffset; 
  G4double worldXYHalfSize = detRadius + worldOffset; 

  worldVolSolid = new G4Box("World", 
			    worldXYHalfSize, worldXYHalfSize, worldZHalfSize);
  
  G4Material* vacuum = Materials::Instance() -> GetMaterial("VACUUM");

  worldVolLogic =  new G4LogicalVolume(worldVolSolid, // geometrical object
                                       vacuum,        // material
                                       "World");      // name

  worldVolPhys = new G4PVPlacement(0,               // no rotation
                                   G4ThreeVector(), // no translation
                                   "World",         // name 
                                   worldVolLogic,   // the logical volume
                                   0,               // the world has no mother
                                   false,           // param. for future use
                                   0);              // copy number

  // **** Detector volume ***

  detVolSolid = new G4Tubs(detName, 0.0, detRadius, 
                           detThickn * 0.5, 
                           0. * deg, 360.0 * deg);

  G4Material* water = Materials::Instance() -> GetMaterial("G4_Al");

  detVolLogic = new G4LogicalVolume(detVolSolid,  // geometrical object
                                    water,        // material
                                    detName);  // name

  detVolUserLimits = new G4UserLimits( 0.1 * mm );
  detVolLogic -> SetUserLimits( detVolUserLimits );

  detSV = new DetectorSV( detName );

  detVolLogic -> SetSensitiveDetector( detSV );
  G4SDManager::GetSDMpointer() -> AddNewDetector( detSV );

  detVolPhys = new G4PVPlacement(0,    // no rotation
	             G4ThreeVector(0, 0, detThickn * 0.5), // translation
                     detName,      // name
                     detVolLogic,     // logical volume of the detector
                     worldVolPhys,    // physical volume of mother volume
                     false,           // param. for future use
                     0);              // copy number

  //G4Region* detectorRegion = new G4Region( detName  + "Region" );
  //detectorRegion -> AddRootLogicalVolume( detVolLogic );

  //G4double cut = 1. * mm;

  //detProdCuts = new G4ProductionCuts();
  //detProdCuts -> SetProductionCut( cut );
  //detectorRegion -> SetProductionCuts( detProdCuts );

  return worldVolPhys;
}


void DetectorConstruction::SetMaxStepSize(G4double max) {

  if( detVolUserLimits == 0 ) {
     G4cerr << "ERROR. Cannot set max step size. No user limits defined." 
            << G4endl;
  
     return;   
  }

  if( max > 0.0 * mm ) {
     detVolUserLimits -> SetMaxAllowedStep( max );
  } 
  else {
     G4cout << "WARNING: Illegal detector size. Using default."
            << G4endl;
  }
}


void DetectorConstruction::SetThickness(G4double thickn) {

  if(detVolSolid == 0 || worldVolSolid == 0) {
     G4cerr << "ERROR. Cannot set length. No volumes defined." 
            << G4endl;
  
     return;   
  }

  if( thickn > 0.0 * cm ) {

     detVolSolid -> SetZHalfLength( thickn * 0.5 );

     detVolPhys -> SetTranslation( G4ThreeVector( 0, 0, thickn * 0.5 ) );

     worldVolSolid -> SetZHalfLength( thickn + worldOffset );   

     G4RunManager::GetRunManager() -> DefineWorldVolume( worldVolPhys );
  }
  else {
     G4cout << "WARNING: Illegal detector size. Using default."
            << G4endl;
  }
}


void DetectorConstruction::SetRadius(G4double radius) {

  if( detVolSolid == 0 || worldVolSolid == 0 ) {
     G4cerr << "ERROR. Cannot set radius. No volumes defined." 
            << G4endl;
  
     return;   
  }

  if( radius > 0.0 * cm ) {
     detVolSolid -> SetOuterRadius( radius );

     G4double worldXYLength = radius + worldOffset;
     worldVolSolid -> SetXHalfLength( worldXYLength ); 
     worldVolSolid -> SetYHalfLength( worldXYLength ); 

     G4RunManager::GetRunManager() -> DefineWorldVolume( worldVolPhys );
  }
  else {
     G4cout << "WARNING: Illegal detector radius. Using default."
            << G4endl;
  }
}


void DetectorConstruction::SetMaterial(G4String mat) {

  if( detVolLogic == 0 ) {
     G4cerr << "ERROR. Cannot set material. No volume defined." 
            << G4endl;
  
     return;   
  }

  G4Material* detVolMat = Materials::Instance() -> GetMaterial( mat );   

  if( detVolMat != 0 ) {
     detVolLogic -> SetMaterial( detVolMat );

     G4cout << "INFORMATION: Setting calorimeter material: "
	    << *detVolMat
	    << G4endl;

     G4RunManager::GetRunManager() -> DefineWorldVolume( worldVolPhys );
  }
  else {
     G4cout << "WARNING: Material " << mat << " not found. Using default."
            << G4endl;
  } 
}


void DetectorConstruction::SetProductionCut(G4double cut) {

  if(detProdCuts == 0) {
     G4cerr << "ERROR. Cannot set production cut. No cuts defined." 
            << G4endl;
  
     return;   
  }

  if( cut > 0.0 ) {
    detProdCuts -> SetProductionCut( cut );
  }
  else {
     G4cout << "WARNING: Negative production threshold. Ignoring."
            << G4endl;
  }
}


void DetectorConstruction::SetAlbedoCut(G4double cut) {

  if(detSV == 0) {
     G4cerr << "ERROR. Cannot set albedo cut in SV." 
            << G4endl;
  
     return;   
  }

  detSV -> SetAlbedoCut( cut );
}


void DetectorConstruction::SetTestEnergyAlbedo(G4double en) {

  if(detSV == 0) {
     G4cerr << "ERROR. Cannot set test value in SV." 
            << G4endl;
  
     return;   
  }

  detSV -> SetTestEnergyAlbedo( en );
}


void DetectorConstruction::SetTestChargeAlbedo(G4double no) {

  if(detSV == 0) {
     G4cerr << "ERROR. Cannot set test value in SV." 
            << G4endl;
  
     return;   
  }

  detSV -> SetTestChargeAlbedo( no );
}


void DetectorConstruction::Print(std::ostream& os, G4int primEvents) {

  if(detSV == 0) {
     G4cout << "ERROR. Cannot print SV info." 
            << G4endl;
  
     return;   
  }

  detSV -> Print( os, primEvents );
}


void DetectorConstruction::PrintUnformatted(std::ostream& os, 
                                            G4int primEvents) {

  if(detSV == 0) {
     G4cout << "ERROR. Cannot print SV info." 
            << G4endl;
  
     return;   
  }

  detSV -> PrintUnformatted( os, primEvents );
}


void DetectorConstruction::ResetForRun() {

  if(detSV == 0) {
     G4cerr << "ERROR. Cannot reset SV." 
            << G4endl;
  
     return;   
  }

  detSV -> ResetForRun();
  detSV -> SetTestEnergyAlbedo( -1. );
  detSV -> SetTestChargeAlbedo( -1. );
}


void DetectorConstruction::CloseEvent() {

  if(detSV == 0) {
     G4cerr << "ERROR. Cannot close event in SV." 
            << G4endl;
  
     return;   
  }

  detSV -> CloseEvent();
}
