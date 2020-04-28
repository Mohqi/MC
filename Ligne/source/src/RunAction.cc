//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"
#include "EventAction.hh"
// #include "Run.hh"



#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
: G4UserRunAction(),
    fTree1{"tree1", "tree1"},
    fTree2{"tree2","tree2"},
    fEvents{-1},
    fKinEnergy{0.},
    fX{0.},
    fY{0.},
    fvX{0.},
    fvY{0.},
    fvZ{0.},
    fSpectrum{0.},
    fPartName{"unknown"},
    fTrackID{0},
    fParentID{-1},
    fBool(true)
{
    // Allocution des branches Tree1
    fTree1.Branch("KinEnergy", &fKinEnergy, "KinEnergy /D");
    fTree1.Branch("X", &fX, "X /D");
    fTree1.Branch("Y", &fY, "Y /D");
    fTree1.Branch("vX", &fvX, "vX /D");
    fTree1.Branch("vY", &fvY, "vY /D");
    fTree1.Branch("vZ", &fvZ, "vZ /D");
    fTree1.Branch("spectrumEnergy", &fSpectrum, "Spectrum /D");
    fTree1.Branch("ptclName" , &fPartName);
    fTree1.Branch("trackID"  , &fTrackID  ,"trackID  /I") ;
    fTree1.Branch("parentID"  , &fParentID  ,"parentID  /I") ;
    
    // Allocution des branches Tree2
    
    fTree2.Branch("KinEnergy", &fKinEnergy, "KinEnergy /D");
    fTree2.Branch("X", &fX, "X /D");
    fTree2.Branch("Y", &fY, "Y /D");
    fTree2.Branch("vX", &fvX, "vX /D");
    fTree2.Branch("vY", &fvY, "vY /D");
    fTree2.Branch("vZ", &fvZ, "vZ /D");
    fTree2.Branch("spectrumEnergy", &fSpectrum, "Spectrum /D");
    fTree2.Branch("ptclName" , &fPartName);
    fTree2.Branch("trackID"  , &fTrackID  ,"trackID  /I") ;
    fTree2.Branch("parentID"  , &fParentID  ,"parentID  /I") ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
    ;
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables

  const DetectorConstruction* detectorConstruction
   = static_cast<const DetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  G4AnalysisManager* man = G4AnalysisManager::Instance();
    
  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const PrimaryGeneratorAction* generatorAction
   = static_cast<const PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
  }
        
  // Print
  //  
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition
     << G4endl
     << "------------------------------------------------------------"
     << G4endl
     << G4endl;
    
    TFile outputFile{"Output.root", "recreate"};
    fTree1.Write();
    fTree2.Write();
    outputFile.Close() ;

    delete G4AnalysisManager::Instance();  
    
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

