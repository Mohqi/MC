#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <algorithm>
//issou
//champ rayon 10mm

void traitement() {
    TFile* f = new TFile("build/Output.root");
    TTree* tr= (TTree*)f->Get("tree");  //ouvre le fichier root;
    TFile* fIn = new TFile("data/input.root");
    TTree* trIn= (TTree*)fIn->Get("tree2");  //ouvre le fichier root;
    double x_profil=0;
    double y_profil=0;
    double vx_profil=0;
    double vy_profil=0;
    double x_root=0;
    double z_root=0;
    double y_root=0;
    double dose=0;
    double edep=0;
    int pixel_x,pixel_y,pixel_z;
    int facteur_z = 10;
    int facteur_y = 100;
    int facteur_x = 100;    //facteur pour passer des mm de root à une autre unité
    int FOVx = 12*facteur_x; // nombre de pixel en z
    int FOVy = 12*facteur_y;  // nombre de pixel en y
    int FOVz = 7*facteur_z;
    int max=0;
    // Taille de l'image = 7mm en z x 1mm en x
    tr->SetBranchAddress("X",&x_root);
    tr->SetBranchAddress("Edep",&edep);
    tr->SetBranchAddress("Y",&y_root);
    tr->SetBranchAddress("Z",&z_root);
    trIn->SetBranchAddress("X", &x_profil);
    trIn->SetBranchAddress("Y", &y_profil);
    trIn->SetBranchAddress("vX", &vx_profil);
    trIn->SetBranchAddress("vY", &vy_profil);
    
    //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//
    //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//
    
    
    // Creation profil de fluence X/Y au niveau du collimateur
    double** Profil = (double**)malloc(FOVx*sizeof(double*));
    for (int i = 0 ; i<FOVx ; i++) {
        Profil[i]= (double*)malloc(FOVy*sizeof(double));
    }
    for (int i = 0 ; i<FOVx ; i++) {
            for (int j = 0 ; j<FOVy ; j++) {
                Profil[i][j]=0;
            }
    }
    
    //Transfert des données , remplir la matrice
    for(int i = 0; i<trIn->GetEntries(); i++) {
        trIn->GetEntry(i);
            pixel_x=round(x_profil*facteur_x)+FOVx/2;
            pixel_y=round(y_profil*facteur_y)+FOVy/2;
            if (pixel_x<FOVx && pixel_x> 0 && pixel_y >0 && pixel_y<FOVy) {
                Profil[pixel_x][pixel_y]++;
        }
    }
    // Ecrire la matrice profil X/Y dans data

    fstream output("data/profilXY.txt",ios::out);
    for (int i = 0 ; i<FOVx ; i++) {
        for (int j = 0 ; j<FOVy ; j++) {
            output <<  Profil[j][i] << " "  ;
        }
        output << std::endl;
    }
    output.close();
    delete Profil;
    
    std::cout << "Fin écriture matrice profil à la sortie de la ligne" << std::endl;
    
    
    //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//
    //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//
    
    
    // Creation dose en profondeur volume élémentaire au niveau du collimateur
    double*** VolumeElem = (double***)malloc(FOVx*sizeof(double**));
    for (int i = 0 ; i<FOVx ; i++) {
        VolumeElem[i]= (double**)malloc(FOVy*sizeof(double*));
        for(int j=0;j<FOVy;j++)
            VolumeElem[i][j]=(double*)malloc(FOVz*sizeof(double));
    }
    for (int i = 0 ; i<FOVx ; i++) {
            for (int j = 0 ; j<FOVy ; j++) {
                for(int k=0;k<FOVz;k++)
                    VolumeElem[i][j][k]=0;
            }
    }
    std::cout << "Début lecture des données root output" << std::endl;
    //Transfert des données , remplir la matrice
    for(int i = 0; i<tr->GetEntries(); i++) {
        tr->GetEntry(i);
        pixel_x=round(x_root*facteur_x)+FOVx/2;
        pixel_y=round(y_root*facteur_y)+FOVy/2;
        pixel_z=round(z_root*facteur_z);
            if (pixel_x> 0 && pixel_x<FOVx
                && pixel_y>0 && pixel_y<FOVy
                && pixel_z>0 && pixel_z<FOVz) {
                VolumeElem[pixel_x][pixel_y][pixel_z]+=edep;
        }
    }
    std::cout << "Fin Lecture des données root" << std::endl;
    fstream vol;
    double taille = 0.050; //taille en minimètre des cotés
    std::string taille_str=std::to_string(int(taille*1000));
    double coteX=taille/2.*facteur_x;
    double coteY=taille/2.*facteur_y;
    int pos_max=coteX;
    for (int a=-4;a<=4;a++){
        int pos = round(2*a*coteX);
        std::cout << "Début pos" << pos << std::endl;
        max=0;
        std::string nb = std::to_string(pos);
        std::string acces ="data/DVH"+taille_str+"/DoseVolumeElem"+nb+".txt";
        vol.open(acces,ios::out);
        std::cout << acces << std::endl;
        std::string name = "data/DVH"+taille_str+"/Volume"+nb+".txt";
        if(!vol)
            break;
        output.open(name,ios::out);
        
        double** projXZ = (double**)malloc(FOVx*sizeof(double*));
        for(int i =0;i<FOVx;i++)
            projXZ[i]=(double*)malloc(FOVz*sizeof(double));
        
        for(int i =0;i<FOVx;i++) {
            for(int k=0;k<FOVz;k++){
                projXZ[i][k]=0;
            }
        }
        for (int i =pos+(FOVx/2); i<pos+(FOVx/2)+2*coteX; i++) {
            for (int j =pos+(FOVy/2); j<pos+(FOVy/2)+2*coteY; j++) {
                for (int k =0 ; k<FOVz; k++) {
                    if(i>FOVx || j> FOVy) {
                        std::cout << "Erreur limite"<< std::endl;
                        break;
                    }
                    if(max<VolumeElem[i][j][k])
                        max=VolumeElem[i][j][k];
                    }
                }
            }
        float DVH[101];
        for(int i=0;i<101;i++)
            DVH[i]=0;
        int cpt=0;
        std::cout << "Début Projection + DVH" << std::endl;
        for (int i = (FOVx/2)+pos ; i<pos+(FOVx/2)+2*coteX; i++) {
            for (int k =0 ; k<FOVz; k++) {
                for (int j = pos+(FOVy/2); j<pos+(FOVy/2)+2*coteY; j++) {
                    VolumeElem[i][j][k]=VolumeElem[i][j][k]/max;
                    vol << i << " " << j <<  " " << k << " ";
                    vol << VolumeElem[i][j][k] << std::endl;
                    projXZ[i][k]+=VolumeElem[i][j][k];
                    cpt++;
                    for(int a=0;a<101;a++) {
                        if(VolumeElem[i][j][k]*100>=a)
                            DVH[a]++;
                    }
                }
                output << projXZ[i][k] << " " ;
            }
            output << std::endl;
        }
        output.close();
        vol.close();
        std::cout << "Fin pos" << pos << std::endl;
        output.open("data/DVH"+taille_str+"/DVH"+nb+".txt",ios::out);
        for(int i=0;i<101;i++)
            output << i << " " << DVH[i] << std::endl;
        output.close();
    }
}


