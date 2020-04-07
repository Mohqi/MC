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
    G4double world_sizeXY = 1*m;
    G4double world_sizeZ  = 10*m;
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
  // Diffuseur 1 aluminium 100um
  //
    
    G4double position_diff1 = -(2500-744)*mm;
  G4Material* diff1_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector diff1_pos = G4ThreeVector(0, 0, position_diff1);
        
    G4double diff1_x = 5*cm;
    G4double diff1_y = 5*cm;
    G4double diff1_z = 50*um;
    G4Box* diff1 =
        new G4Box("Diff1",                                //its name
                  1*diff1_x, 1*diff1_y, 1 *diff1_z);     //its size
                      
  G4LogicalVolume* logicDiff1 =
    new G4LogicalVolume(diff1,         //its solid
                        diff1_mat,          //its material
                        "Diff1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    diff1_pos,                    //at position
                    logicDiff1,             //its logical volume
                    "Diff1",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
    
    
    //
    //Diffuseur 2 sorti d'air 50um al
    //
      
      G4double position_diff2 = -(2500-4200)*mm;
    G4Material* diff2_mat = nist->FindOrBuildMaterial("G4_Al");
    G4ThreeVector diff2_pos = G4ThreeVector(0, 0, position_diff2);
          
      G4double diff2_x = 10*cm;
      G4double diff2_y = 10*cm;
      G4double diff2_z = 25*um;
      G4Box* diff2 =
          new G4Box("Diff2",                                //its name
                    1*diff2_x, 1*diff2_y, 1*diff2_z);     //its size
                        
    G4LogicalVolume* logicDiff2 =
      new G4LogicalVolume(diff2,         //its solid
                          diff2_mat,          //its material
                          "Diff2");           //its name
                 
    new G4PVPlacement(0,                       //no rotation
                      diff2_pos,                    //at position
                      logicDiff2,             //its logical volume
                      "Diff2",                //its name
                      logicWorld,                //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking
    
    //     Collimateur 1 5mm
    
    G4RotationMatrix* xRot = new G4RotationMatrix;
    xRot->rotateX(M_PI/2.*rad);
    
    G4double r_min_coll1 = 2.5*mm;
    G4double r_max_coll1 = 20*cm;
    G4double mi_haut_coll1 = 5*mm;
    
    G4Tubs* coll1 =
    new G4Tubs("coll1",// name
           r_min_coll1,  // inner radius
           r_max_coll1,  // outer radius
           mi_haut_coll1,    // Z half length
           0,  // starting Phi
           2*M_PI); // segment angle
    
    G4double position_coll1 = -(2500-723)*mm;
    G4Material* coll1_mat = nist->FindOrBuildMaterial("G4_Al");
    G4ThreeVector coll1_pos = G4ThreeVector(0, 0, position_coll1);
    
    G4LogicalVolume* logicColl1 =
        new G4LogicalVolume(coll1 ,
                            coll1_mat,
                            "coll1");
    
    new G4PVPlacement(0,
                      coll1_pos,
                      logicColl1,
                      "coll1",
                      logicWorld,
                      false,
                      0,
                      checkOverlaps);
    
    //
    // Collimateur 2 10mm
    //
    
        G4double position_coll2 = -(2500-3519)*mm;
        G4Material* coll2_mat = nist->FindOrBuildMaterial("G4_Al");
        G4ThreeVector coll2_pos = G4ThreeVector(0, 0, position_coll2);
            
       G4double r_min_coll2  = 5*mm;
       G4double r_max_coll2  = 20*cm;
       G4double mi_haut_coll2 = 5*mm;
    
           G4Tubs* coll2 =
           new G4Tubs("coll2",// name
                r_min_coll2, // inner radius
                r_max_coll2,  // outer radius
                mi_haut_coll2,    // Z half length
                0,  // starting Phi
                2*M_PI); // segment angle
                         
       G4LogicalVolume* logicColl2 =
       new G4LogicalVolume(coll2,         //its solid
                           coll2_mat,          //its material
                           "coll2");           //its name
                  
     new G4PVPlacement(0,                       //no rotation
                       coll2_pos,                    //at position
                       logicColl2,             //its logical volume
                       "coll2",                //its name
                       logicWorld,                //its mother  volume
                       false,                   //no boolean operation
                       0,                       //copy number
                       checkOverlaps);          //overlaps checking


    //
    // Collimateur 3 30mm sortie air
    //
       
        G4double position_coll3 = -(2500-4189)*mm;
        G4Material* coll3_mat = nist->FindOrBuildMaterial("G4_Al");
        G4ThreeVector coll3_pos = G4ThreeVector(0, 0, position_coll3);
            
       G4double r_min_coll3 = 15*mm;
       G4double r_max_coll3 = 20*cm;
       G4double mi_haut_coll3 = 5*mm;
    
           G4Tubs* coll3 =
           new G4Tubs("coll3",// name
                  r_min_coll3,  // inner radius
                  r_max_coll3,  // outer radius
                  mi_haut_coll3,    // Z half length
                  0,  // starting Phi
                  2*M_PI); // segment angle
                         
       G4LogicalVolume* logicColl3 =
       new G4LogicalVolume(coll3,         //its solid
                           coll3_mat,          //its material
                           "coll3");           //its name
                  
     new G4PVPlacement(0,                       //no rotation
                       coll3_pos,                    //at position
                       logicColl3,             //its logical volume
                       "coll3",                //its name
                       logicWorld,                //its mother  volume
                       false,                   //no boolean operation
                       0,                       //copy number
                       checkOverlaps);          //overlaps checking
    
    
    //
    // Collimateur Adaptable Aluminium
    //;
    /*
        G4double position_coll_alu = -(2500-4209)*mm;
        G4Material* coll_alu_mat = nist->FindOrBuildMaterial("G4_Al");
        G4ThreeVector coll_alu_pos = G4ThreeVector(0, 0, position_coll_alu);
            
       G4double r_min_coll_alu = 5*mm;
       G4double r_max_coll_alu = 20*cm;
       G4double mi_haut_coll_alu = 5*mm;
    
           G4Tubs* coll_alu =
           new G4Tubs("coll_alu",// name
                  r_min_coll_alu,  // inner radius
                  r_max_coll_alu,  // outer radius
                  mi_haut_coll_alu,    // Z half length
                  0,  // starting Phi
                  2*M_PI); // segment angle
                         
        logicColl =
       new G4LogicalVolume(coll_alu,         //its solid
                           coll_alu_mat,          //its material
                           "coll_alu");           //its name
                  
     new G4PVPlacement(0,                       //no rotation
                       coll_alu_pos,                    //at position
                       logicColl,             //its logical volume
                       "coll_alu",                //its name
                       logicWorld,                //its mother  volume
                       false,                   //no boolean operation
                       0,                       //copy number
                       checkOverlaps);          //overlaps checking
 */
    
    //
    // Collimateur Adaptable Tantale
    //
        G4Material* Tantale_mat = nist->FindOrBuildMaterial("G4_Ta");
        G4double position_coll_ta = -(2500-4209)*mm;
        G4ThreeVector coll_ta_pos = G4ThreeVector(0, 0, position_coll_ta);
            
       G4double r_min_coll_ta = 5*mm;
       G4double r_max_coll_ta = 20*cm;
       G4double mi_haut_coll_ta = 0.5*mm;
    
           G4Tubs* coll_ta =
           new G4Tubs("coll_ta",// name
                  r_min_coll_ta,  // inner radius
                  r_max_coll_ta,  // outer radius
                  mi_haut_coll_ta,    // Z half length
                  0,  // starting Phi
                  2*M_PI); // segment angle
                         
        logicColl =
       new G4LogicalVolume(coll_ta,         //its solid
                           Tantale_mat,          //its material
                           "coll_ta");           //its name
                  
     new G4PVPlacement(0,                       //no rotation
                       coll_ta_pos,                    //at position
                       logicColl,             //its logical volume
                       "coll_ta",                //its name
                       logicWorld,                //its mother  volume
                       false,                   //no boolean operation
                       0,                       //copy number
                       checkOverlaps);          //overlaps checking

//
//    Volume de détection water derriere le 2eme diffuseur
//
    G4double position_detec = -(2500 - 4225)*mm;
    G4Material* detec_mat = nist->FindOrBuildMaterial("G4_WATER");
    G4ThreeVector detec_pos = G4ThreeVector(0,0,position_detec);
    
    G4double detec_x = 10*cm ;
    G4double detec_y = 10*cm ;
    G4double detec_z = 1*cm;
    
    G4Box* detec=
        new G4Box("detect",
                  detec_x,
                  detec_y,
                  detec_z);
    
    G4LogicalVolume* logicDetec =
        new G4LogicalVolume(detec,
                            detec_mat,
                            "detect");
    
   new G4PVPlacement(0,
                  detec_pos,
                  logicDetec,
                  "detect",
                  logicWorld,
                  false,
                  0,
                  checkOverlaps);
    
    //
    //    Volume de détection après le premier collimateur
    //
        G4double position_detec_debut = -(2500-735)*mm;
        G4Material* detec_debut_mat = nist->FindOrBuildMaterial("G4_WATER");
        G4ThreeVector detec_debut_pos = G4ThreeVector(0,0,position_detec_debut);
        
        G4double detec_debut_x = 10*cm ;
        G4double detec_debut_y = 10*cm ;
        G4double detec_debut_z = 1*um;
        
        G4Box* detec_debut=
            new G4Box("detectDebut",
                      detec_debut_x,
                      detec_debut_y,
                      detec_debut_z);
        
        G4LogicalVolume* logicDetecDebut =
            new G4LogicalVolume(detec_debut,
                                detec_debut_mat,
                                "detectDebut");
        
       new G4PVPlacement(0,
                      detec_debut_pos,
                      logicDetecDebut,
                      "detectDebut",
                      logicWorld,
                      false,
                      0,
                      checkOverlaps);
    
 fScoringVolume = logicDetec;
    
  //
  //always return the physical World
  //
  return physWorld;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
