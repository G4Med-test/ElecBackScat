
#include "Materials.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"


Materials* Materials::instance = 0;


Materials* Materials::Instance () {

  if(instance == 0) {
     instance = new Materials;
  }
  return instance;
}


void Materials::Destroy() {

  if(!instance == 0) {

     delete instance;
     instance = 0;
  }
}


Materials::Materials() {

  G4Material* water = 
               G4NistManager::Instance() -> FindOrBuildMaterial("G4_WATER");
  materials.push_back( water );
   
  G4Material* aluminum = 
               G4NistManager::Instance() -> FindOrBuildMaterial("G4_Al");
  materials.push_back( aluminum );

  G4Material* beryllium = 
               G4NistManager::Instance() -> FindOrBuildMaterial("G4_Be");
  materials.push_back( beryllium );

  G4Material* carbon = new G4Material("G4_C", 1.7 * g/cm3, 1);
  G4Element* elmC = G4NistManager::Instance() -> FindOrBuildElement( 6 );
  carbon -> AddElement( elmC, 1 );
  carbon -> GetIonisation() -> SetMeanExcitationEnergy(78.0 * eV);
  materials.push_back( carbon );

  G4Material* molybd = 
               G4NistManager::Instance() -> FindOrBuildMaterial("G4_Mo");
  materials.push_back( molybd );

  G4Material* titanium = 
               G4NistManager::Instance() -> FindOrBuildMaterial("G4_Ti");
  materials.push_back( titanium );

  G4Material* tantalum = 
               G4NistManager::Instance() -> FindOrBuildMaterial("G4_Ta");
  materials.push_back( tantalum );

  G4Material* uranium = 
               G4NistManager::Instance() -> FindOrBuildMaterial("G4_U");
  materials.push_back( uranium );

  G4String name;
  G4double density = universe_mean_density;
  G4double moleMass = 1.01 * g/mole;
  G4double pressure = 3.e-18*pascal;
  G4double temperature = 2.73*kelvin;
  G4double atomicNumber = 1;
  G4Material* vacuum = new G4Material(name="VACUUM", atomicNumber, moleMass,
			  density, kStateGas, temperature, pressure);
  materials.push_back( vacuum );
}


Materials::~Materials() {


  std::vector<G4Material*>::iterator iter = materials.begin();
  std::vector<G4Material*>::iterator iter_end = materials.end();

  for(;iter != iter_end; iter++) delete *iter;
}


G4Material* Materials::GetMaterial(G4String matName) {

  return G4Material::GetMaterial(matName);
}

