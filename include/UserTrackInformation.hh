#ifndef USERTRACKINFORMATION_HH
#define USERTRACKINFORMATION_HH

#include "G4VUserTrackInformation.hh"
#include "G4Allocator.hh"
#include "globals.hh"

class G4Step;


class UserTrackInformation : public G4VUserTrackInformation {
 
 public:
   UserTrackInformation();
   ~UserTrackInformation() { }
   inline void *operator new(size_t);
   inline void operator delete(void* trackInfo);

   void Print() const { }

 private:
   G4String currPreVolName; 
   G4String currPostVolName; 
   G4String currVolNameStep;
   G4double currPreZ;
   G4double currPostZ;
   G4double currPreX;
   G4double currPostX;
   G4double currPreEn;
   G4double currPostEn;
   G4bool currBCrossing;

   G4String prevPreVolName; 
   G4String prevPostVolName; 
   G4String prevVolNameStep;
   G4double prevPreZ;
   G4double prevPostZ;
   G4double prevPreX;
   G4double prevPostX;
   G4double prevPreEn;
   G4double prevPostEn;
   G4bool prevBCrossing;

   G4bool reflected;
   G4double reflectedEnergy;

 public:
   void UpdateStep(const G4Step* step);

   inline G4bool WasReflected() {
      return reflected;
   }
   inline G4double GetReflectedEnergy() {
      return reflectedEnergy;
   } 
};

extern G4Allocator<UserTrackInformation> UserTrackInformationAllocator;

inline void* UserTrackInformation::operator new(size_t) { 
void* trackInfo;
  trackInfo = (void*) UserTrackInformationAllocator.MallocSingle();
  return trackInfo;
}

inline void UserTrackInformation::operator delete(void* trackInfo) { 
  UserTrackInformationAllocator.FreeSingle((UserTrackInformation*) trackInfo);
}

#endif // USERTRACKINFORMATION_HH
