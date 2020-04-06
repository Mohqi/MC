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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include <iostream>
#include <string>

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"     //maximum step size
#include "G4PVReplica.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
    :G4VUserDetectorConstruction(),
    logicColl(0),
    fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
//  G4double env_sizeXY = 50*cm, env_sizeZ = 5*m;
//  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
    G4double d=150*um;
    G4double cote =(d/2.);
    G4double world_sizeXY = 5*cm;
    G4double world_sizeZ  = 3*cm;
    G4double void_density = 0.000001*g/m3;
    G4double a_void = 1*g/mole;
    G4Material* G4_Void=
        new G4Material("G4_Void",1.,a_void,void_density);
  
  G4Box* solidWorld =
    new G4Box("World",                       //its name
       1*world_sizeXY, 1*world_sizeXY, 1 *world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        G4_Void,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     

//
//    WaterBox
//
    G4double pos_waterbox = 1*cm;
    G4Material* waterbox_mat = nist->FindOrBuildMaterial("G4_WATER");
    G4ThreeVector waterbox_pos = G4ThreeVector(0,0,pos_waterbox);
    
    G4double waterbox_x = 8*mm ;
    G4double waterbox_y = 8*mm ;
    G4double waterbox_z = 1*cm;
    
    G4Box* waterbox=
        new G4Box("waterbox",
                  waterbox_x,
                  waterbox_y,
                  waterbox_z);
    
    G4LogicalVolume* logicWaterbox =
        new G4LogicalVolume(waterbox,
                            waterbox_mat,
                            "waterbox");
    
   new G4PVPlacement(0,
                  waterbox_pos,
                  logicWaterbox,
                  "waterbox",
                  logicWorld,
                  false,
                  0,
                  checkOverlaps);
    
    
    // Embout FLASH carre
    
    //load data

    std::ifstream data("../source/data/data.txt");
    double a=0;
    double b=0;
    int nb_epai=20;
    double* coef=(double*)malloc((nb_epai+1)*sizeof(double));
    double* epaisseur=(double*)malloc(nb_epai*sizeof(double));
    for (int i=0;i<20;i++)
    {
        if (data) {
        data >> a >> b ;
        epaisseur[i] = a;
        coef[i] = b;
        }
    }
    coef[nb_epai+1]=0;
    
    //
    // zone irradiation Champ 6mm rayon gaussien
    //
    G4double zone_xy =8*mm;
    G4double zone_z = 3*mm;
    G4ThreeVector zone_pos=G4ThreeVector(0,0,-3*mm);
    
    G4Box* zone =
        new G4Box("zone",
                  zone_xy,
                  zone_xy,
                  zone_z);
    
    G4LogicalVolume* logicZone =
        new G4LogicalVolume(zone,
                            G4_Void,
                            "zone") ;
    G4VPhysicalVolume* physicZone =
    new G4PVPlacement(0,
                      zone_pos,
                      logicZone,
                      "zone",
                      logicWorld,
                      false,
                      0,
                      checkOverlaps);
    
    
    //
    // enveloppe cible
    //
    
     G4double pos_env_z = -5*mm;
     G4Material* env_mat = nist->FindOrBuildMaterial("G4_Void");
     G4ThreeVector env_pos = G4ThreeVector(0,0,pos_env_z);
     
     G4double box_xy = cote ;
     G4double box_z = 3*mm;
     
     G4Box* env=
         new G4Box("env",
                   box_xy,
                   box_xy,
                   box_z);
     
     G4LogicalVolume* logicEnv=
         new G4LogicalVolume(env,
                             env_mat,
                             "env");
     
    //
    // cible
    //
    
    double tot=0;
    std::vector<double> aire(nb_epai,0);
    std::vector<double> xy(nb_epai+1,0);
    for (int i=0; i<20;i++) {
        tot+=coef[i];
    }
    aire[0]=(cote*cote)/tot;
    xy[20]=0;

    G4double cible_xy;
    G4double cible_z;
    G4double pos_x=0;
    G4double pos_y=0;
    G4double pos_z;
    std::vector<G4Box*> cible(20);
    std::vector<G4LogicalVolume*> logicCible(20);
    std::string cible_string= "cible";
    G4Material* cible_mat = nist->FindOrBuildMaterial("G4_Al");
    G4ThreeVector cible_pos;
    for (int i=19; i>=0 ; i--) {
        if(i!=0) {
        aire[i]=aire[0]*coef[i];
        xy[i]=sqrt(aire[i]+xy[i+1]*xy[i+1]);
        std::string i_string = std::to_string(i);
        std::string name = cible_string+i_string;
        cible_xy = xy[i];
        cible_z = (epaisseur[i]-epaisseur[i-1])/2.;
        pos_z = (-box_z/2.+epaisseur[i]-cible_z);
        cible_pos=G4ThreeVector(pos_x,pos_y,pos_z);
        
        cible[i]=
             new G4Box(name,
                       cible_xy,
                       cible_xy,
                       cible_z);
         
         logicCible[i] =
             new G4LogicalVolume(cible[i],
                                 cible_mat,
                                 name);
         
        new G4PVPlacement(0,
                          cible_pos,
                          logicCible[i],
                          name,
                          logicEnv,
                          false,
                          0,
                          checkOverlaps);
        }
        else if(i==0) {
            xy[i]=sqrt(aire[i]+xy[i+1]*xy[i+1]);
            std::string i_string = std::to_string(i);
            std::string name = cible_string+i_string;
            cible_xy = xy[i];
            cible_z = (epaisseur[i])/2.;
            pos_z = (-box_z/2.+epaisseur[i]-cible_z);
            cible_pos=G4ThreeVector(pos_x,pos_y,pos_z);
            
            cible[i]=
                 new G4Box(name,
                           cible_xy,
                           cible_xy,
                           cible_z);
             
             logicCible[i] =
                 new G4LogicalVolume(cible[i],
                                     cible_mat,
                                     name);
             
            new G4PVPlacement(0,
                              cible_pos,
                              logicCible[i],
                              name,
                              logicEnv,
                              false,
                              0,
                              checkOverlaps);
            
        }
    }
    for (double pos_cible_x=-zone_xy+cote; pos_cible_x <zone_xy ; pos_cible_x+=2*cote){
        for (double pos_cible_y=-zone_xy+cote; pos_cible_y <zone_xy ; pos_cible_y+=2*cote){
            G4ThreeVector repeat = G4ThreeVector(pos_cible_x,pos_cible_y,0);
            new G4PVPlacement(0,
                              repeat,
                              logicEnv,
                              "env",
                              logicZone,
                              false,
                              0,
                              checkOverlaps);
            }
        }
    fScoringVolume = logicWaterbox;
  //
  //always return the physical World
  //
  return physWorld;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
