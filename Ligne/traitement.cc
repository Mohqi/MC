#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <algorithm>


void traitement() {
    TFile* f = new TFile("build/output.root");
    TTree* tr1= (TTree*)f->Get("tree1");  //ouvre le fichier root;
    TTree* tr2=(TTree*)f->Get("tree2");     //ouvre le root à la fin
    double x1,x2,y1,y2;
    
    tr1->SetBranchAddress("X",&x1);
    tr1->SetBranchAddress("Y",&y1);
    tr2->SetBranchAddress("X",&x2);
    tr2->SetBranchAddress("Y",&y2);
    int taille_x = 20;
    int taille_y = 20;
    int facteur_xy = 5;
    int demi_x = (facteur_xy*taille_x)/2.;
    int demi_y = (facteur_xy*taille_y)/2.;
    
    std::vector<int> profil_X1 (taille_x*facteur_xy,0);
    std::vector<int> profil_X2 (taille_x*facteur_xy,0);
    std::vector<int> profil_Y1 (taille_y*facteur_xy,0);
    std::vector<int> profil_Y2 (taille_y*facteur_xy,0);

    //Transfert des données , remplir la matrice
    for(int i = 0; i<tr1->GetEntries(); i++) {
        tr1->GetEntry(i);
        x1=round(x1*facteur_xy);  y1=round(y1*facteur_xy);
        if((x1>-demi_x && x1<demi_x) &&
           (y1>-demi_y && y1<demi_y))
            {
                profil_X1[x1+demi_x]++;
                profil_Y1[y1+demi_y]++;
        }
    }
    for(int i=0;i<tr2->GetEntries();i++){
            tr2->GetEntry(i);
            x2=round(x2*facteur_xy);  y2=round(y2*facteur_xy);
            if((x2>-demi_x && x2<demi_x) &&
               (y2>-demi_y && y2<demi_y))
                {
                    profil_X2[x2+demi_x]++;
                    profil_Y2[y2+demi_y]++;
            }
        }

    fstream outputx1,outputx2,outputy1,outputy2;
    outputx1.open("data/profilx1.txt",ios::out);
    outputx2.open("data/profilx2.txt",ios::out);
    outputy1.open("data/profily1.txt",ios::out);
    outputy2.open("data/profily2.txt",ios::out);
    
    for(int i=0;i<profil_X1.size();i++) {
        outputx1 << i << " " << profil_X1[i] << endl;
    }
    
    for(int i=0;i<profil_X2.size();i++) {
        outputx2 << i << " " << profil_X2[i] << endl;
    }
    
    for(int i=0;i<profil_Y1.size();i++) {
        outputy1 << i << " " << profil_Y1[i] << endl;
    }
    
    for(int i=0;i<profil_Y2.size();i++) {
        outputy2 << i << " " << profil_Y2[i] << endl;
    }
}

