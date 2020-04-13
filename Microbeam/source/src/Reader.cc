//
//  Reader.cpp
//  
//
//  Created by anthony richert on 13/04/2020.
//

#include "Reader.hh"
#include "Randomize.hh"
#include <cmath>
#include "G4RunManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Reader::Reader()
:   i(0),
    theta(0),
    fTFile(0),
    fTTree(0),
    x(0),
    y(0),
    x_rot(0),
    y_rot(0),
    vx(0),
    vy(0),
    vx_rot(0),
    vy_rot(0),
    vz(0),
    energy(0)
{
}

Reader::~Reader()
{
}

void Reader::SetBranch(const char* acces,const char* tree) {
    fTFile= new TFile(acces);
    fTTree=(TTree*)fTFile->Get(tree);
    fTTree->SetBranchAddress("X",&x);
    fTTree->SetBranchAddress("Y",&y);
    fTTree->SetBranchAddress("vX",&vx);
    fTTree->SetBranchAddress("vY",&vy);
    fTTree->SetBranchAddress("vZ",&vz);
    fTTree->SetBranchAddress("KinEnergy",&energy);
}

void Reader::GetValue() {
    fTTree->GetEntry(i);
    x_rot=x*cos(theta)+y*sin(theta);
    y_rot=-x*sin(theta)+y*cos(theta);
    
    vx_rot=vx*cos(theta)+vy*sin(theta);
    vy_rot=-vx*sin(theta)+vy*cos(theta);
    
    i++;
    if(i%(fTTree->GetEntries())==0){
        i=0;
        theta=G4RandFlat::shoot(0.,2*M_PI);
        G4cout << "All primaries from the original input file has been used" << G4endl;
        G4cout << "Now applying rotation around Z-axis with angle theta = " << theta << G4endl;
    }
}



    
