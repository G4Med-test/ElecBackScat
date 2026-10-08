#ifndef PARTICLES_HH
#define PARTICLES_HH

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"


class Particles : public G4VPhysicsConstructor {

 public: 
   Particles(const G4String& name = "Particles");
   virtual ~Particles();
 
 protected: 
   void ConstructParticle();
   void ConstructProcess() {}; 
};

#endif // PARTICLES_HH








