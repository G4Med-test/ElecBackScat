
#include "UserRunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGenerator.hh"
#include "UserEventAction.hh"
#include "UserTrackingAction.hh"
#include "G4Run.hh"


#include "G4SystemOfUnits.hh"

#include <fstream>
#include <sstream>
#include <iomanip>

UserRunAction::UserRunAction(const G4String& /*fileName*/,
                             DetectorConstruction* det,
                             PrimaryGenerator* bm,
			     UserEventAction* evAction,
			     UserTrackingAction* trAction) :
  fileNameBase("res"),
  detector( det ),
  beam( bm ),
  eventAction( evAction ),
  trackAction( trAction ) 
{}

void UserRunAction::BeginOfRunAction(const G4Run* run) 
{
  G4cout << "INFORMATION: Run No " << run -> GetRunID() 
         << " starts." << G4endl;

  eventAction -> SetRunID( run -> GetRunID() );
  eventAction -> ResetTimer();
  trackAction -> ResetCounter();

  // Open an output file
  std::ostringstream strs, strs2, strs3;
  strs << beam -> GetPrimaryKineticEnergy()/MeV;
  strs2 << detector->GetMaterial()->GetName();
  strs3 << beam -> GetIncidentAngle()/degree;

  G4String physlist;
  G4String fileName2 = "physlist.info";
  std::ifstream ifile_physlist( fileName2.c_str() );
  ifile_physlist >> physlist;
  ifile_physlist.close();

}

void UserRunAction::EndOfRunAction(const G4Run* run) 
{

  // Write summary
  G4String fileName = fileNameBase + "_summary";
  // Use if individual files should be written for each run
  //std::stringstream ss;
  // ss << (run -> GetRunID() + 1);
  // G4String fileName = "res_runNo" + ss.str();
  
  std::ofstream ofilestream;
  ofilestream.open( (fileName + ".dat").c_str(), 
                    std::ios::out | std::ios::app );
  if( !ofilestream ) {
    G4cout << "ERROR: Cannot open file " 
	   << fileName << ".dat for writing."  
	   << G4endl;
  } else {

    G4cout << "File " <<  fileName + ".dat" << " is opened" << G4endl;

    ofilestream << "=== Run No " << (run -> GetRunID() + 1) 
		<< "  " << detector->GetMaterial()->GetName() 
		<< "   === "  
		<< G4endl;

    ofilestream << "Beam energy: " 
		<< beam -> GetPrimaryKineticEnergy()/MeV << " MeV "
		<< G4endl;
    ofilestream << "Incident angle: " 
		<< beam -> GetIncidentAngle()/degree << " deg "
		<< std::endl;
    detector -> Print( ofilestream, run -> GetNumberOfEvent() );  
    ofilestream.close();  
  }
 
  // Write data file for printing
  // Use if individual files should be written for each run
  //   std::stringstream s;
  //   s << (run -> GetRunID() + 1);
  //   G4String fileName = "res_runNo" + s.str();

  /*
  // get the physics list name and save in the output file
  G4String physlist;
  G4String fileName2 = "physlist.info";
  std::ifstream ifile_physlist( fileName2.c_str() );
  ifile_physlist >> physlist;
  ifile_physlist.close();
  */

  ofilestream.open( (fileNameBase + ".dat").c_str(), 
                    std::ios::out | std::ios::app );
  if( !ofilestream ) {
     G4cout << "ERROR: Cannot open file " 
            << fileNameBase << ".dat for writing."  
            << G4endl;
  } else {
    G4cout << "File " <<  fileNameBase + ".dat" << " is opened" << G4endl;
    ofilestream << detector->GetMaterial()->GetName() << "  " 
		<< beam -> GetPrimaryKineticEnergy()/MeV << "  "
		<< beam -> GetIncidentAngle()/degree << "  ";
    detector -> PrintUnformatted( ofilestream, run -> GetNumberOfEvent() );  
    ofilestream << std::endl;     
    ofilestream.close(); 
  
  }

  trackAction -> Print();
  
  G4cout << "INFORMATION: Run No " << run -> GetRunID() 
         << " ends (Number of events = " 
         << run -> GetNumberOfEvent() << ")." << G4endl;

  detector -> ResetForRun();
}
