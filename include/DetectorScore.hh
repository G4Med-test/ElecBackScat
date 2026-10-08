#ifndef DETECTORSCORE_HH
#define DETECTORSCORE_HH

#include "globals.hh"

class G4Step;


class DetectorScore {

 public:
   DetectorScore();
   ~DetectorScore() { }

   void ProcessStep(G4Step* step);
   void Print(std::ostream& os, G4int primEvents);

   inline void SetEnergyCut(G4double cut) { if(cut >= 0) enCut = cut; }
   inline G4double GetEnergyCut() { return enCut; }

   inline G4double GetEnDep() { return pEnDep; }
   inline G4double GetEnEnter() { return pEnEnter; }
   inline G4double GetEnExit() { return pEnExit; }
   inline G4double GetEnCorr() { return pEnEnterRefl; }
   inline G4double GetEnEnterActual() { return pEnEnter-pEnEnterRefl; }
   inline G4double GetEnExitActual() { return pEnExit-pEnEnterRefl; }
   inline G4int GetNoEnter() { return pEnter; }
   inline G4int GetNoExit() { return pExit; }
   inline G4int GetNoCorr() { return pEnterRefl; }
   inline G4int GetNoEnterActual() { return pEnter-pEnterRefl; }
   inline G4int GetNoExitActual() { return pExit-pEnterRefl; }

   G4double GetEnDepError() { CalcErrors(); return pEnDepRelError*pEnDep; }
   G4double GetEnExitActualError() { CalcErrors(); 
                             return pEnExitRelError*(pEnExit-pEnEnterRefl); }
   G4double GetNoExitActualError() { CalcErrors(); 
                             return pExitRelError*(pExit-pEnterRefl); }

   void ResetForRun();
   void CloseEvent();

   void CalcErrors();

 private:
   // Energy threshold above which quantities are scored
   G4double enCut;
 
   // Quantities scored
   G4double pEnDep;
   G4double pEnEnter;
   G4double pEnEnterRefl;
   G4double pEnExit;
   G4int pEnter;
   G4int pEnterRefl;
   G4int pExit;

   // Variables for error calculation
   G4double pEnDepEvent;
   G4double pEnExitActualEvent;
   G4int pExitActualEvent;

   G4double pEnDepSumSquared;
   G4double pEnExitActualSumSquared;
   G4int pExitActualSumSquared;

   G4int eventsN;

   // Errors
   G4double pEnDepRelError;
   G4double pEnExitRelError; 
   G4double pExitRelError; 
};

#endif // DETCTORSCORE_HH
