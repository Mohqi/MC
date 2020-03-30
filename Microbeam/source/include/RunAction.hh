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
/// \file RunAction.hh
/// \brief Definition of the RunAction class

#ifndef RunAction_h
#define RunAction_h 1

#include<string>

#include "TFile.h"
#include "TTree.h"

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    
  public:
    
    void SetEdep (double aEdep) { fEdep=aEdep; }
    void SetDepth (double aDepth) { fDepth=aDepth; }
    void SetX (double aX ) {fX = aX ; }
    void SetY (double aY ) {fY = aY ; }
    void SetKineticEnergy(double aKinEnergy) {fKinEnergy = aKinEnergy;}
    void SetDelta (double aDelta) {fDelta = aDelta; }
    void SetDose (double aDose) {fDose =  aDose;}
    void SetParticleName    ( G4String aPartName ) { fPartName  = aPartName.data() ;  }
    void SetTrackID    ( int    aID  ) { fTrackID = aID    ;  }
    void SetParentID    ( int    aID  ) { fParentID = aID     ;  }
    void SetSpectrum    ( double   aSpectrum  ) { fSpectrum = aSpectrum     ;  }
    
    TTree& GetTree(){ return fTree; }
    int& GetEvents(){ return fEvents; }
    
private:
    TTree fTree;
    int fEvents;
    double fEdep;
    double fDepth;
    double fX;
    double fY;
    double fSpectrum;
    double fDelta;
    double fKinEnergy;
    double fDose; 
    std::string fPartName;
    int fTrackID;
    int fParentID;
};

#endif

