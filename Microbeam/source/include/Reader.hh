//
//  Reader.hpp
//  
//
//  Created by anthony richert on 13/04/2020.
//

#ifndef Reader_hpp
#define Reader_hpp

#include <stdio.h>
#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include <cmath>
#include <string>

class Reader
{
private:

    int i;
    float theta;
    TFile* fTFile;
    TTree* fTTree;
    double x;
    double y;
    double x_rot;
    double y_rot;
    double vx;
    double vy;
    double vx_rot;
    double vy_rot;
    double vz;
    double energy;
    
public:
    Reader();
    ~Reader();
    void SetBranch(const char* acces,const char* tree);
    void GetValue();
    TTree* GetTree() {return fTTree;}
    TFile* GetTFile() {return fTFile;}
    double GetX() {return x_rot;}
    double GetY() {return y_rot;}
    double GetVx() {return vx_rot;}
    double GetVy() {return vy_rot;}
    double GetVz() {return vz;}
    double GetEnergy() {return energy;}
    
    void SetTFile(TFile* aFile) {fTFile=aFile;}
    void SetTree(TTree* aTree) {fTTree=aTree;}
    
};

#endif /* Reader_hpp */
