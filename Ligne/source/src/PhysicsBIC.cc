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
// This is the *BASIC* version of Hadrontherapy, a Geant4-based application
// See more at: http://g4advancedexamples.lngs.infn.it/Examples/hadrontherapy
//
// Visit the Hadrontherapy web site (http://www.lns.infn.it/link/Hadrontherapy) to request
// the *COMPLETE* version of this program, together with its documentation;
// Hadrontherapy (both basic and full version) are supported by the Italian INFN
// Institute in the framework of the MC-INFN Group
//
//
// Hadrontherapy Users are recommended to use the prepared macro files in order to activate the
// most appropriate physics for hadrontherapy applications.
// As one can easily see the physics we suggest is contained in the
// 'QGSP_BIC_EMY' list adding to the decay processes (activated as default).

#include "PhysicsBIC.hh"

#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"
#include "StepMax.hh"
#include "G4VModularPhysicsList.hh"
#include "G4Version.hh"

#if G4VERSION_NUMBER < 1000
#include "G4QStoppingPhysics.hh"
#include "HadronPhysicsQGSP_BIC.hh"
#else
#include "G4StoppingPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#endif


/////////////////////////////////////////////////////////////////////////////
PhysicsBIC::PhysicsBIC() : G4VModularPhysicsList()
{
   G4LossTableManager::Instance();
   
   SetVerboseLevel(0);
   
   // EM physics
    fEmPhysicsList = new G4EmStandardPhysics_option4(1);

   // Decay physics and all particles
   fDecPhysicsList = new G4DecayPhysics();
   
   // Radiative decay
   fRadDecayList = new G4RadioactiveDecayPhysics();

    fStepMaxProcess  = 0;
   
   // hadron physics
#if G4VERSION_NUMBER < 1000
   fHadronPhys.push_back( new HadronPhysicsQGSP_BIC());
   fHadronPhys.push_back( new G4QStoppingPhysics());
#else
   fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC());
   fHadronPhys.push_back( new G4StoppingPhysics());
#endif
   fHadronPhys.push_back( new G4EmExtraPhysics());
   fHadronPhys.push_back( new G4HadronElasticPhysics());
   fHadronPhys.push_back( new G4IonBinaryCascadePhysics());
   fHadronPhys.push_back( new G4NeutronTrackingCut());
}

/////////////////////////////////////////////////////////////////////////////
PhysicsBIC::~PhysicsBIC()
{
   delete fEmPhysicsList;
   delete fDecPhysicsList;
   delete fRadDecayList;
   
   for(size_t i=0; i<fHadronPhys.size(); ++i)
      delete fHadronPhys[i];
}

/////////////////////////////////////////////////////////////////////////////
void PhysicsBIC::ConstructParticle()
{
   fDecPhysicsList->ConstructParticle();
}

/////////////////////////////////////////////////////////////////////////////
void PhysicsBIC::ConstructProcess()
{
   // transportation
   AddTransportation();
   
   // electromagnetic physics list
   fEmPhysicsList->ConstructProcess();
   
   // decay physics list
   fDecPhysicsList->ConstructProcess();
   fRadDecayList->ConstructProcess();
   
   // hadronic physics lists
   for(size_t i=0; i<fHadronPhys.size(); ++i)
      fHadronPhys[i]->ConstructProcess();

    AddStepMax();
}

/////////////////////////////////////////////////////////////////////////////
void PhysicsBIC::AddStepMax()
{
    // Step limitation seen as a process
    fStepMaxProcess = new StepMax();
    
    auto particleIterator=GetParticleIterator();
    particleIterator->reset();
    while ((*particleIterator)()){
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        
        if (fStepMaxProcess->IsApplicable(*particle) && pmanager)
        {
            pmanager ->AddDiscreteProcess(fStepMaxProcess);
        }
    }
}


