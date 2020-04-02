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
TTree* tr= (TTree*)f->Get("tree");  //ouvre le fichier root;
    int cibleID=0;
    double x_root=0;
    double z_root=0;
    double y_root=0;
    double dose=0;
    double edep=0;
    int pixel_x,pixel_y,pixel_z;
    int facteur_z = 100;
    int facteur_y = 100;//facteur pour passer des mm de root à une autre unité
    int FOVz = 7*facteur_z; // nombre de pixel en z
    int FOVy = 2*facteur_y;  // nombre de pixel en x
    // Taille de l'image = 7mm en z x 1mm en x
    int nb_cible = 20;
    
    tr->SetBranchAddress("Edep",&edep);
    tr->SetBranchAddress("X",&x_root);
    tr->SetBranchAddress("Y",&y_root);
    tr->SetBranchAddress("Z",&z_root);
    tr->SetBranchAddress("CibleID", &cibleID);
    
    
    // Mise en place de la matrice FOVy x FOVz x 1
    double*** FOV = (double***)malloc(FOVz*sizeof(double**));
    for (int i = 0 ; i<FOVz ; i++) {
        FOV[i]= (double**)malloc(FOVy*sizeof(double*));
        for (int j = 0; j<FOVy ;j++)
            FOV[i][j]=(double*)malloc(nb_cible*sizeof(double));
    }
    for (int i = 0 ; i<FOVz ; i++) {
            for (int j = 0 ; j<FOVy ; j++) {
                for (int k=0 ; k<nb_cible;k++)
                FOV[i][j][k]=0;
            }
    }
    
    //Transfert des données , remplir la matrice
    for(int i = 0; i<tr->GetEntries(); i++) {
        tr->GetEntry(i);
            pixel_y=round(y_root*facteur_y)+FOVy/2;
            pixel_z=round(z_root*facteur_z);
            if (pixel_z<FOVz && pixel_z> 0 && pixel_y >0 && pixel_y<FOVy) {
                FOV[pixel_z][pixel_y][cibleID]+=edep;
        }
    }
    for (int nom=0;nom<20;nom++) {
        // Ecrire la matrice dans un fichier text
        std::string nb = std::to_string(nom);
        std::string debut = "data/Matrice";
        std::string fin = ".txt";
        std::string chemin = debut+nb+fin;
        fstream output(chemin,ios::out);
        for (int i = 0 ; i<FOVy ; i++) {
            for (int j = 0 ; j<FOVz ; j++) {
                output <<  FOV[j][i][nom] << " "  ;
            }
            output << std::endl;
    }
    output.close();
    }
    fstream output("data/MatriceTot.txt",ios::out);
    double proj_cible;
    for (int i = 0 ; i<FOVy ; i++) {
        for (int j = 0 ; j<FOVz ; j++) {
            proj_cible=0;
            for (int k =0 ; k<20; k++) {
                proj_cible+=FOV[j][i][k];
            }
            output << proj_cible << " " ;
        }
        output << std::endl;
    }
    output.close();
    delete FOV;
}

