#ifndef EMSTEPLIMITER_HH
#define EMSTEPLIMITER_HH 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"


class EmStepLimiter : public G4VPhysicsConstructor {

 public: 
   EmStepLimiter(const G4String& name = "EM-StepLimiter"); 
   virtual ~EmStepLimiter();
  
 protected:
   void ConstructParticle() {}; 
   void ConstructProcess();
};

#endif // EMSTEPLIMITER_HH








