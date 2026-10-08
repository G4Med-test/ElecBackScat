
#include "EmStepLimiter.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4StepLimiter.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Gamma.hh"


EmStepLimiter::EmStepLimiter(const G4String& name): 
    G4VPhysicsConstructor(name) {
}


EmStepLimiter::~EmStepLimiter() { 

}


void EmStepLimiter::ConstructProcess() {

  G4ParticleDefinition* particle = G4Electron::Electron(); 
  G4ProcessManager* processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(new G4StepLimiter);

  particle = G4Gamma::Gamma(); 
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(new G4StepLimiter);

  particle = G4Positron::Positron(); 
  processManager = particle -> GetProcessManager();
  processManager -> AddDiscreteProcess(new G4StepLimiter);
}
