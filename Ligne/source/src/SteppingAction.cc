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
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"
#include "RunAction.hh"
#include "TrackingAction.hh"

#include "Randomize.hh"

#include "G4ClassificationOfNewTrack.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4UserLimits.hh"
#include "G4VProcess.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
:G4UserSteppingAction(),
    fEventAction(eventAction),
    fScoringVolume(0),
    fTrack(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  
    const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
    
//    get volume of the current step
    
  G4LogicalVolume* logicVolume
    = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    std::string volumeName =
        step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
    std::string str = "cible" ;
    std::size_t found = volumeName.find(str);
    if(found!=std::string::npos) {
        int cibleID;
        std::string nombre = volumeName.substr(str.size());
        cibleID = stoi(nombre);
        fEventAction->GetRunAction()->SetCible(cibleID);
        fEventAction->GetRunAction()->SetBool(false);
    }
    if(fEventAction->GetRunAction()->GetBool()){
        fEventAction->GetRunAction()->SetCible(0);
    }
    if(logicVolume==fScoringVolume) {
        auto* runAction_h =  fEventAction->GetRunAction();
        fTrack = step->GetTrack();
        G4double ID =  fTrack->GetTrackID();
        G4StepPoint* prePoint = step->GetPreStepPoint();
        G4StepPoint* postPoint = step->GetPostStepPoint();
        G4double Edep = prePoint->GetKineticEnergy() - postPoint->GetKineticEnergy();
        G4double TotalEdep = step->GetTotalEnergyDeposit();
        G4double kinEnergy = prePoint->GetKineticEnergy();
        G4double deltaLength = (postPoint->GetPosition().getZ() - prePoint->GetPosition().getZ());
        G4double depth = (prePoint->GetPosition().getZ() + CLHEP::RandFlat::shoot(deltaLength)) ;
        G4double x_pre = prePoint->GetPosition().getX();
        G4double x_post = postPoint->GetPosition().getX();
        G4double x = CLHEP::RandFlat::shoot(x_pre,x_post);
        G4double y = prePoint->GetPosition().getY();
        const G4VProcess* CurrentProcess=prePoint->GetProcessDefinedStep();
        if (CurrentProcess != 0) {
            const G4String & StepProcessName = CurrentProcess->GetProcessName();
            if(StepProcessName== "Transportation") {
                // processing hit when entering the volume
                G4double spectrumEnergy = step->GetTrack()->GetKineticEnergy();
                runAction_h->SetSpectrum(spectrumEnergy);
            }
        }
        else
            runAction_h->SetSpectrum(0);
        runAction_h->SetDepth(depth); //ici cest pour la profondeur
        runAction_h->SetParticleName(fTrack->GetDefinition()->GetParticleName());
        runAction_h->SetKineticEnergy(kinEnergy);
        runAction_h->SetEdep(TotalEdep);
        runAction_h->SetDelta(deltaLength);
        runAction_h->SetDose(Edep);
        runAction_h->SetTrackID(ID);
        runAction_h->SetParentID(fTrack->GetParentID() );
        runAction_h->SetX(x);
        runAction_h->SetY(y);
        runAction_h->GetTree().Fill();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

