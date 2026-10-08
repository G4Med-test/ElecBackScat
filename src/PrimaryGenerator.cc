
#include "PrimaryGenerator.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4Electron.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"

PrimaryGenerator::PrimaryGenerator() {

  primaryKineticEnergy = 1.0 * MeV;
  sigmaKineticEnergy = 0 * keV;
  incidentAngle = 0.0 * deg;

  particleGun = new G4ParticleGun( G4Electron::Electron(), 1 );  
  messenger = new PrimaryGeneratorMessenger( this );
}


PrimaryGenerator::~PrimaryGenerator() {

  delete particleGun;
  delete messenger;
}


void PrimaryGenerator::GeneratePrimaries(G4Event* event) {

  G4double kineticEnergy = primaryKineticEnergy;

  if(sigmaKineticEnergy > 0.0)
     kineticEnergy = 
         G4RandGauss::shoot(primaryKineticEnergy, 
                            primaryKineticEnergy * sigmaKineticEnergy);

  particleGun -> SetParticleEnergy(kineticEnergy);
  particleGun -> SetParticlePosition(
         G4ThreeVector(0.0 * mm, 0.0 * mm, -1.0 * mm).rotateX(incidentAngle));
  particleGun -> SetParticleMomentumDirection(
         G4ThreeVector(0.0 * mm, 0.0 * mm, 1.0 * mm).rotateX(incidentAngle));
  particleGun -> GeneratePrimaryVertex(event);
}


void PrimaryGenerator::SetPrimaryKineticEnergy(G4double kinEnergy) {

  if(kinEnergy > 0.0 * MeV) {
     primaryKineticEnergy = kinEnergy;
  }
}


void PrimaryGenerator::SetSigmaKineticEnergy(G4double sigma) {

  if(sigma >= 0.0 && sigma < 100.0) {
     sigmaKineticEnergy = sigma / 100.;
  }
}


void PrimaryGenerator::SetIncidentAngle(G4double angle) {

  if(angle >= 0.0 * deg && angle < 90.0 * deg) {
     incidentAngle = angle;
  }
}


G4double PrimaryGenerator::GetPrimaryKineticEnergy() { 

  return primaryKineticEnergy;
}


G4double PrimaryGenerator::GetSigmaKineticEnergy() {
 
  return sigmaKineticEnergy;
}


G4double PrimaryGenerator::GetIncidentAngle() {

  return incidentAngle;
}
