
#include "DetectorScore.hh"
#include "UserTrackInformation.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>
#include <iostream>

DetectorScore::DetectorScore() :
   enCut( 0 ),
   pEnDep( 0 ),
   pEnEnter( 0 ),
   pEnEnterRefl( 0 ),
   pEnExit( 0 ),
   pEnter( 0 ),
   pEnterRefl( 0 ),
   pExit( 0 ),
   pEnDepEvent( 0 ),
   pEnExitActualEvent( 0 ),
   pExitActualEvent( 0 ),
   pEnDepSumSquared( 0 ),
   pEnExitActualSumSquared( 0 ),
   pExitActualSumSquared( 0 ),
   eventsN( 0 ),
   pEnDepRelError( 0 ),
   pEnExitRelError( 0 ), 
   pExitRelError( 0 ) {

}


void DetectorScore::ProcessStep(G4Step* step) {

  G4double enDep = step -> GetTotalEnergyDeposit();
  pEnDep += enDep;
  pEnDepEvent += enDep;

  G4StepPoint* postStepPoint = step -> GetPostStepPoint();
  if(postStepPoint -> GetStepStatus() == fGeomBoundary) { 

     G4double postEn = postStepPoint -> GetKineticEnergy();
     if(postEn > 0.0 && postEn >= enCut) {
        pExit++; 
        pEnExit += postEn;

        pExitActualEvent++;
        pEnExitActualEvent += postEn;
     } 
  }

  G4StepPoint* preStepPoint = step -> GetPreStepPoint();
  if(preStepPoint -> GetStepStatus() == fGeomBoundary) { 

     G4double preEn = preStepPoint -> GetKineticEnergy();
     pEnter++; 
     pEnEnter += preEn;

     G4Track* track = step -> GetTrack();
     G4VUserTrackInformation* info = track -> GetUserInformation();
     UserTrackInformation* tinfo = static_cast<UserTrackInformation*>(info);

     if(tinfo->WasReflected()) {
        G4double enEnterRefl = tinfo -> GetReflectedEnergy();
	  // G4cout << "Was reflected with energy " << enEnterRefl
	  //	    << G4endl;

        if(enEnterRefl >= enCut) {
  	   pEnterRefl++;
           pEnEnterRefl += enEnterRefl; 

           pExitActualEvent--;
           pEnExitActualEvent -= enEnterRefl;
	}
     }
  }
}


void DetectorScore::Print(std::ostream& os, G4int primEvents) {

  G4double ev = (G4double)primEvents;

  size_t di = 12;

  G4double N = (G4double)eventsN;

  CalcErrors();

  os << std::setw(di) << std::right << pEnDep/ev/MeV 
     << std::setw(di) << pEnEnter/ev/MeV
     << std::setw(di) << pEnExit/ev/MeV
     << std::setw(di) << pEnEnterRefl/ev/MeV
     << std::setw(di) << (pEnEnter-pEnEnterRefl)/ev/MeV
     << std::setw(di) << (pEnExit-pEnEnterRefl)/ev/MeV
     << std::setw(di) << pEnter/ev
     << std::setw(di) << pExit/ev
     << std::setw(di) << pEnterRefl/ev
     << std::setw(di) << (pEnter-pEnterRefl)/ev
     << std::setw(di) << (pExit-pEnterRefl)/ev
     << std::setw(di) << N
     << G4endl;

  os << std::setw(2) << std::right << "(" 
     << std::setw(di-3)<< std::right << pEnDepRelError*100. 
     << std::setw(1) << std::right <<")"
     << std::setw(di) << "-"
     << std::setw(di) << "-"
     << std::setw(di) << "-"
     << std::setw(di) << "-"
     << std::setw(2) << std::right << "(" 
     << std::setw(di-3)<< std::right << pEnExitRelError*100. 
     << std::setw(1) << std::right <<")"
     << std::setw(di) << "-"
     << std::setw(di) << "-"
     << std::setw(di) << "-"
     << std::setw(di) << "-"
     << std::setw(2) << std::right << "(" 
     << std::setw(di-3)<< std::right << pExitRelError*100. 
     << std::setw(1) << std::right <<")"

     << G4endl;
}


void DetectorScore::CalcErrors() {

  G4double Nm1 = 1./((G4double)eventsN);

  pEnDepRelError = std::sqrt(pEnDepSumSquared/(pEnDep * pEnDep) - Nm1); 

  G4double pEnExitActual = pEnExit - pEnEnterRefl;
  pEnExitRelError 
      = std::sqrt(pEnExitActualSumSquared/(pEnExitActual*pEnExitActual) - Nm1); 

  G4double pExitActual = pExit - pEnterRefl;
  pExitRelError 
      = std::sqrt(pExitActualSumSquared/(pExitActual*pExitActual) - Nm1); 
}


void DetectorScore::ResetForRun() {

   pEnDep = 0;
   pEnEnter = 0;
   pEnEnterRefl = 0;
   pEnExit = 0;
   pEnter = 0;
   pEnterRefl = 0;
   pExit = 0;

   pEnDepEvent = 0;
   pEnExitActualEvent = 0;
   pExitActualEvent = 0;

   pEnDepSumSquared = 0;
   pEnExitActualSumSquared = 0;
   pExitActualSumSquared = 0;
   eventsN = 0;
   
   pEnDepRelError = 0;
   pEnExitRelError = 0; 
   pExitRelError = 0; 
}


void DetectorScore::CloseEvent() {

   eventsN++;

   pEnDepSumSquared += pEnDepEvent * pEnDepEvent;
   pEnExitActualSumSquared += pEnExitActualEvent * pEnExitActualEvent;
   pExitActualSumSquared += pExitActualEvent * pExitActualEvent;

   pEnDepEvent = 0.0;
   pEnExitActualEvent = 0.0;
   pExitActualEvent = 0;
}
