
#include "DetectorSV.hh"
#include "DetectorScore.hh"
#include "UserTrackInformation.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4DynamicParticle.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
 


DetectorSV::DetectorSV(const G4String& name) :
  G4VSensitiveDetector( name ) {

  elec = G4Electron::Definition();
  gam = G4Gamma::Definition();

  elecScore = new DetectorScore();
  gamScore = new DetectorScore();
  othScore = new DetectorScore();
}


DetectorSV::~DetectorSV() {

  delete elecScore;
  delete gamScore;
  delete othScore;
}


G4bool DetectorSV::ProcessHits(G4Step* step, 
                               G4TouchableHistory*) {

  if(step == 0) return false;

  G4Track* track = step -> GetTrack();
  const G4DynamicParticle* dynParticle = track -> GetDynamicParticle();
  G4ParticleDefinition* particle = dynParticle -> GetDefinition();

  if( particle == elec ) elecScore -> ProcessStep( step );
  else if( particle == gam ) gamScore -> ProcessStep( step );
  else othScore -> ProcessStep( step );

  return true;
}


void DetectorSV::Print(std::ostream& os, G4int) {

  os << "Fraction of energy reflected = "  
     << (elecScore -> GetEnExitActual())/(elecScore -> GetEnEnterActual())
     << " +- "
     << (elecScore -> GetEnExitActualError())/(elecScore -> GetEnEnterActual())
     << G4endl;

  if(testReflEnFrac>0) {
    os << "Expected value/ simulation value = "  
       << testReflEnFrac / ((elecScore -> GetEnExitActual())/(elecScore -> GetEnEnterActual()))
       << " +- "
       << (elecScore -> GetEnExitActualError())/(elecScore -> GetEnExitActual())
       << G4endl;
  }

  os << "Fraction of electrons reflected = " 
     <<  ((G4double)(elecScore -> GetNoExitActual())) /
	  ((G4double)(elecScore -> GetNoEnterActual()))
     << " +- "
     << (elecScore -> GetNoExitActualError())/
          ((G4double)(elecScore -> GetNoEnterActual()))
     << G4endl;

  if(testReflNoFrac>0) {
    os << "Expected value/ simulation value = "  
       << testReflNoFrac / (((G4double)(elecScore -> GetNoExitActual())) /
			    ((G4double)(elecScore -> GetNoEnterActual())))
       << G4endl;
  }
  os << G4endl;
}


void DetectorSV::PrintUnformatted(std::ostream& os, G4int) {

  os << (elecScore -> GetEnExitActual())/(elecScore -> GetEnEnterActual())
     << "  "
     << (elecScore -> GetEnExitActualError())/(elecScore -> GetEnEnterActual())
     << "   "
     <<  ((G4double)(elecScore -> GetNoExitActual())) /
	  ((G4double)(elecScore -> GetNoEnterActual()))
     << "  "
     << (elecScore -> GetNoExitActualError())/
          ((G4double)(elecScore -> GetNoEnterActual()));
}


void DetectorSV::SetAlbedoCut(G4double cut) {

  elecScore -> SetEnergyCut( cut );
}


void DetectorSV::ResetForRun() {

  elecScore -> ResetForRun();
  gamScore -> ResetForRun();
  othScore -> ResetForRun();
}


void DetectorSV::CloseEvent() {

  elecScore -> CloseEvent();
  gamScore -> CloseEvent();
  othScore -> CloseEvent();
}
