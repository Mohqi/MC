//
//  profil.cpp
//  
//
//  Created by anthony richert on 23/04/2020.
//

#include <stdio.h>
#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <algorithm>

void profil() {
    const double PI =  3.1415926;
    TFile* fIn = new TFile("data/input.root");
    TTree* trIn= (TTree*)fIn->Get("tree2");  //ouvre le fichier root;
    double rvx,rvy;
    double x_profil=0;
    double y_profil=0;
    double vx_profil=0;
    double vy_profil=0;
    double vz_profil=0;
    double x_root=0;
    double z_root=0;
    double y_root=0;
    int pixel_x,pixel_y,pixel_z;
    int facteur_z = 10;
    int facteur_y = 100;
    int facteur_x = 100;
    int FOVx = 12*facteur_x; // nombre de pixel en z
    int FOVy = 12*facteur_y;  // nombre de pixel en y
    int FOVz = 7*facteur_z;
    double theta,phi;
    int FOVtheta = 500;
    int FOVphi = 500;
    int pixel_theta;
    int pixel_phi;
    trIn->SetBranchAddress("X", &x_profil);
    trIn->SetBranchAddress("Y", &y_profil);
    trIn->SetBranchAddress("vX", &vx_profil);
    trIn->SetBranchAddress("vY", &vy_profil);
    trIn->SetBranchAddress("vZ", &vz_profil);
    
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

    double** EmiX = (double**)malloc(FOVx*sizeof(double*));
    for (int i = 0 ; i<FOVx ; i++) {
        EmiX[i]= (double*)malloc(FOVtheta*sizeof(double));
    }
    for (int i = 0 ; i<FOVx ; i++) {
            for (int j = 0 ; j<FOVtheta ; j++) {
                EmiX[i][j]=0;
            }
    }
    
    double** EmiY = (double**)malloc(FOVy*sizeof(double*));
    for (int i = 0 ; i<FOVy ; i++) {
        EmiY[i]= (double*)malloc(FOVphi*sizeof(double));
    }
    for (int i = 0 ; i<FOVy ; i++) {
            for (int j = 0 ; j<FOVphi ; j++) {
                EmiY[i][j]=0;
            }
    }
    //Transfert des données , remplir la matrice
    for(int i = 0; i<trIn->GetEntries(); i++) {
        trIn->GetEntry(i);
        rvx=sqrt(vx_profil*vx_profil+vz_profil*vz_profil);
        rvy=sqrt(vy_profil*vy_profil+vz_profil*vz_profil);
        theta=round((asin(vx_profil/rvx)*180/PI)*100);
        phi=round((asin(vy_profil/rvy)*180/PI)*100);
        pixel_x=round(x_profil*facteur_x)+FOVx/2;
        pixel_y=round(y_profil*facteur_y)+FOVy/2;
        if (pixel_x<FOVx && pixel_x> 0 && pixel_y >0 && pixel_y<FOVy) {
            Profil[pixel_x][pixel_y]++;
        }
        pixel_theta=int(FOVtheta/2+theta);
        pixel_phi=int(FOVtheta/2+phi);
        if(pixel_theta<FOVtheta && pixel_theta>0 &&
           pixel_x<FOVx && pixel_x>0 ) {
            EmiX[pixel_x][pixel_theta]++;
        }
        if( pixel_phi<FOVphi && pixel_phi>0 &&
            pixel_y >0 && pixel_y<FOVy) {
            EmiY[pixel_y][pixel_phi]++;
        }
    }
    // Ecrire la matrice profil X/Y dans data
    fstream femiX("data/emiX.txt",ios::out);
    fstream femiY("data/emiY.txt",ios::out);
    fstream output("data/profilXY.txt",ios::out);
    for (int i = 0 ; i<FOVx ; i++) {
        for (int j = 0 ; j<FOVy ; j++) {
            output <<  Profil[j][i] << " "  ;
        }
        output << std::endl;
    }
    std::cout << "Début émitance X " << std::endl;
    for(int j=0;j<FOVtheta;j++){
        for(int i=0;i<FOVx;i++ )
            femiX << EmiX[i][j] <<  " ";
        femiX << std::endl;
    }
    std::cout << "Début émitance Y " << std::endl;

    for(int i=0;i<FOVy;i++ ){
        for(int j=0;j<FOVphi;j++)
            femiY << EmiY[i][j] <<  " ";
        femiY << std::endl;
    }
    
    output.close();
    delete Profil;

    
    std::cout << "Fin écriture matrice profil à la sortie de la ligne" << std::endl;
    
    
    //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//
    //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//
      
}
