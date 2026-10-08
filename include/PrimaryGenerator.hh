#ifndef PRIMARYGENERATOR_HH
#define PRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4Event;
class G4ParticleGun;
class PrimaryGeneratorMessenger;


class PrimaryGenerator : public G4VUserPrimaryGeneratorAction {

 public:
   PrimaryGenerator();
   ~PrimaryGenerator();

   void GeneratePrimaries(G4Event*);

   void SetPrimaryKineticEnergy(G4double);
   void SetSigmaKineticEnergy(G4double);
   void SetIncidentAngle(G4double);

   G4double GetPrimaryKineticEnergy();
   G4double GetSigmaKineticEnergy();
   G4double GetIncidentAngle();

 private:
   G4ParticleGun* particleGun;
   PrimaryGeneratorMessenger* messenger;

   G4double primaryKineticEnergy;
   G4double sigmaKineticEnergy;
   G4double incidentAngle;
};

#endif // PRIMARYGENERATOR_HH
