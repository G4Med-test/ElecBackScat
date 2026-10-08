
#include "UserTrackInformation.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"

//#define PRINT_DEB_TRACK


UserTrackInformation::UserTrackInformation() :
  currPreVolName( "" ), 
  currPostVolName( "" ), 
  currVolNameStep( "" ),
  currPreZ( 0 ),
  currPostZ( 0 ),
  currPreX( 0 ),
  currPostX( 0 ),
  currPreEn( 0 ),
  currPostEn( 0 ),
  currBCrossing( false ),
  prevPreVolName( "" ), 
  prevPostVolName( "" ), 
  prevVolNameStep( "" ), 
  prevPreZ( 0 ),
  prevPostZ( 0 ),
  prevPreX( 0 ),
  prevPostX( 0 ),
  prevPreEn( 0 ),
  prevPostEn( 0 ),
  prevBCrossing( false ),
  reflected( false ),
  reflectedEnergy( 0 ) { 

}


void UserTrackInformation::UpdateStep(const G4Step* step) {

  G4StepPoint* postStepPoint = step -> GetPostStepPoint();
  G4StepPoint* preStepPoint = step -> GetPreStepPoint();

  prevPreVolName =  currPreVolName;   
  prevPostVolName = currPostVolName;   
  prevVolNameStep = currVolNameStep;
#ifdef PRINT_DEB_TRACK
  prevPreZ = 	    currPreZ; 	 
  prevPostZ = 	    currPostZ; 	 
  prevPreX = 	    currPreX; 	 
  prevPostX = 	    currPostX; 	 
#endif
  prevPreEn = 	    currPreEn; 	 
  prevPostEn = 	    currPostEn; 	 
  prevBCrossing =   currBCrossing; 

  currPreVolName = preStepPoint -> GetPhysicalVolume() -> GetName();
  currPostVolName = postStepPoint -> GetPhysicalVolume() -> GetName();
  currVolNameStep = currPreVolName;
  currPostEn = postStepPoint -> GetKineticEnergy();  
  currPreEn = preStepPoint -> GetKineticEnergy();  
#ifdef PRINT_DEB_TRACK
  G4ThreeVector posPost(postStepPoint -> GetPosition());
  currPostZ = posPost.z();
  currPostX = posPost.x();
  G4ThreeVector posPre(preStepPoint -> GetPosition());
  currPreZ = posPre.z();
  currPreX = posPre.x();
#endif

  if(postStepPoint -> GetStepStatus() == fGeomBoundary) currBCrossing = true;
  else currBCrossing = false;
  if(preStepPoint -> GetStepStatus() == fGeomBoundary) 
     currVolNameStep = postStepPoint -> GetPhysicalVolume() -> GetName();


  if(prevBCrossing && prevVolNameStep == currVolNameStep) {

     reflected = true;
     reflectedEnergy = prevPostEn;

#ifdef PRINT_DEB_TRACK

     G4String particle = 
           step -> GetTrack() -> GetDefinition() -> GetParticleName();

     G4cout << "Reflected at boundary: p = " << particle
	    << G4endl
            << "  prev step: vol = " << prevVolNameStep
            << ", vol_pre = " << prevPreVolName
            << ", vol_post = " << prevPostVolName
            << " z_pre(mm) = " <<  prevPreZ/mm 
            << ", z_post(mm) = " << prevPostZ/mm
            << " x_pre(mm) = " <<  prevPreX/mm 
            << ", x_post(mm) = " << prevPostX/mm
            << ",  E_pre(MeV) = " <<  prevPreEn/MeV
            << ", E_post(MeV) = " << prevPostEn/MeV
	    << G4endl
            << "  curr step: vol = " << currVolNameStep
            << ", vol_pre = " << currPreVolName
            << ", vol_post = " << currPostVolName
            << " z_pre(mm) = " <<  currPreZ/mm 
            << ", z_post(mm) = " << currPostZ/mm
            << " x_pre(mm) = " <<  currPreX/mm 
            << ", x_post(mm) = " << currPostX/mm
            << ", E_pre(MeV) = " <<  currPreEn/MeV
            << ", E_post(MeV) = " << currPostEn/MeV
            << G4endl
	    << "  ** Energy corr(MeV) = " << reflectedEnergy 
	    << G4endl;

#endif

  }
  else {

     reflected = false;
     reflectedEnergy = 0.0;
  }

}
