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
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "Reader.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>


#include "Randomize.hh"




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
    fParticleGun(0),
    fReader()
{
    fReader.SetBranch("../data/input.root","tree2");
    G4int n_particle = 1;
    fParticleGun  = new G4ParticleGun(n_particle);
    G4ParticleTable* particleTable =  G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="proton");
    fParticleGun->SetParticleDefinition(particle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4double cote=100*um;
    int nb_pyr=11;
    G4double x0,y0;
    do{ fReader.GetValue();
        x0=fReader.GetX()*mm;
        y0=fReader.GetY()*mm;
       }
    while( (x0>(nb_pyr/2.)*cote || x0<(-nb_pyr/2.)*cote) || (y0>(nb_pyr/2.)*cote || y0<(-nb_pyr/2.)*cote) );
    
    G4double z0=-3*cm;
    G4double vx0=fReader.GetVx()*mm;
    G4double vy0=fReader.GetVy()*mm;
    G4double vz0=fReader.GetVz()*mm;
    G4double kinEnergy=fReader.GetEnergy()*MeV;
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(vx0,vy0,vz0));
    fParticleGun->SetParticleEnergy(kinEnergy);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

