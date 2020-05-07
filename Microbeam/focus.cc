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

const double MeV = 1.6*pow(10,-7);

void focus() {
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
    double cote=0.100;  //taille du cote en mm
    std::string taille_str = std::to_string(int(cote*1000));
    
    int i2,j2;
    int distance;
    int nb_pyr=11;// Nombre de pyramide par ligne/nb de colonne.
    int pos_centre = (nb_pyr/2)+1;
    int pyr=(nb_pyr*nb_pyr)+1; // Nombre de pyramide
    
    int pixel_x,pixel_y,pixel_z;
    int facteur_z = 10;
    int facteur_y = 1000;
    int facteur_x = 1000;//facteur pour passer des mm de root à une autre unité
    
    int binX=cote*facteur_x;
    int binY=cote*facteur_y;
    
    float taille_max_x = cote*(nb_pyr); //Taille maximale en X en mm
    float taille_max_y = cote*(nb_pyr); //Taille maximale en Y en mm
    
    int FOVx = round(taille_max_x*facteur_x); // nombre de pixel en z
    int FOVy = round(taille_max_y*facteur_y);  // nombre de pixel en y
    int FOVz = 7*facteur_z;
    double mass_voxel = abs(double(1)/(facteur_x*facteur_y*facteur_z));
    std::cout << mass_voxel << std::endl;
    
    int max=0;
    int ID=0;
    // Taille de l'image = 7mm en z x 1mm en x
    tr->SetBranchAddress("X",&x_root);
    tr->SetBranchAddress("Edep",&edep);
    tr->SetBranchAddress("Y",&y_root);
    tr->SetBranchAddress("Z",&z_root);
    tr->SetBranchAddress("CibleID",&ID);
    trIn->SetBranchAddress("X", &x_profil);
    trIn->SetBranchAddress("Y", &y_profil);
    trIn->SetBranchAddress("vX", &vx_profil);
    trIn->SetBranchAddress("vY", &vy_profil);
    
    //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//
    //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo//
    
     
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
    
    
    double*** VolumeCible = (double***)malloc(FOVx*sizeof(double**));
       for (int i = 0 ; i<FOVx ; i++) {
           VolumeCible[i]= (double**)malloc(FOVy*sizeof(double*));
           for(int j=0;j<FOVy;j++)
               VolumeCible[i][j]=(double*)malloc((pyr)*sizeof(double));
       }
    
    for (int i = 0 ; i<FOVx ; i++) {
            for (int j = 0 ; j<FOVy ; j++) {
                for(int k=0;k<pyr;k++)
                    VolumeCible[i][j][k]=0;
            }
    }
    
    double VolumeDistance[pyr];
    for(int i=0;i<pyr;i++){
        VolumeDistance[i]=0;
    }
    
    std::cout << "Début lecture des données root output" << std::endl;
    //Transfert des données , remplir la matrice
    for(int i = 0; i<tr->GetEntries(); i++) {
        tr->GetEntry(i);
        pixel_x=round(x_root*facteur_x)+FOVx/2;
        pixel_y=round(y_root*facteur_y)+FOVy/2;
        pixel_z=round(z_root*facteur_z);
        if(ID!=0) {
            j2 = ID%nb_pyr;
            i2= ID/nb_pyr;
            distance =abs(j2-pos_centre)+abs(i2-pos_centre);
            /*std::cout << "Début" << std::endl;
            std::cout << " ID : " << ID ;
            std::cout << " j2 : " << j2 ;
            std::cout << " i2 : " << i2 ;
            std::cout << " Distance : " << i2 << std::endl;
            std::cout << "Fin" << std::endl;
             */
        }
        
        if(pixel_x>FOVx/2-binX && pixel_x<FOVx/2+binX
           && pixel_y>FOVy/2-binY && pixel_y<FOVy/2+binY) {
            VolumeDistance[distance]+=edep;
        }
        if (pixel_x> 0 && pixel_x<FOVx
                && pixel_y>0 && pixel_y<FOVy
                && pixel_z>0 && pixel_z<FOVz) {
            VolumeElem[pixel_x][pixel_y][pixel_z]+=edep;
                
        }
        if (pixel_x> 0 && pixel_x<FOVx
                       && pixel_y>0 && pixel_y<FOVy
                       && ID>0 && ID<pyr) {
            VolumeCible[pixel_x][pixel_y][ID]+=edep;
        }
    }
    fstream volume_output("data/histo/dose_distance.txt",ios::out);
    
    if(volume_output) {
        std::cout << "Bon chemin d'acces" << std::endl;
    }
    
    for(int i=0;i<2*pos_centre;i++) {
        volume_output << i << " " << VolumeDistance[i] << std::endl;
    }
    
    std::cout << "Fin Lecture des données root" << std::endl;
    fstream output;
    std::string name_pre = "data/cube/cube";
    std::string name_suf = ".txt";
    std::string name_cible_pre = "data/cible/cible";
    std::string name_cible_ext = ".txt";
    std::string name_cible;
    fstream cible_output;
    
    float v;
    int cube_x;
    int cube_y;
    
    for(int k=0;k<pyr;k++){
        std::string cible_num = to_string(k);
        name_cible=name_cible_pre+cible_num+name_cible_ext;
        cible_output.open(name_cible,ios::out);
        for (int i=0;i<FOVx;i++){
            for(int j=0;j<FOVy;j++){
                cible_output << VolumeCible[i][j][k] << " " ;
            }
            cible_output << std::endl;
        }
        cible_output.close();
    }
    std::cout << "Cible Ok" << std::endl;
    delete VolumeCible;
    std::cout << "Debut Cube" << std::endl;
    
    double** projXZ = (double**)malloc(FOVx*sizeof(double*));
    for(int i =0;i<FOVx;i++)
        projXZ[i]=(double*)malloc(FOVz*sizeof(double));
    
    for(int i =0;i<FOVx;i++) {
        for(int k=0;k<FOVz;k++){
            projXZ[i][k]=0;
        }
    }
    
    for(int i=0;i<nb_pyr;i++){
        for(int j=0;j<nb_pyr;j++) {
            cube_x = 2*i*cote;
            cube_y = 2*j*cote;
            std::string i_str = to_string(i);
            std::string j_str = to_string(j);
            std::string output_name = name_pre + i_str + j_str + name_suf;
            output.open(output_name,ios::out);
            for(int k=0;k<binX;k++) {
                for(int l=0;l<binY;l++) {
                    v=0;
                    for(int z=0;z<FOVz;z++){
                        if(cube_x+k<0 || cube_x+k>FOVx || cube_y+l<0 || cube_y+l>FOVy) {
                            std::cout << "Erreur de segmentation" << std::endl;
                            break;
                        }
                        v+=VolumeElem[cube_x+k][cube_y+l][z];
                    }
                    output << v << " " ;
                }
                output << std::endl;
            }
            output.close();
        }
    }
    fstream vol;
    std::string acces ="data/DVH"+taille_str+"/DoseVolumeElem.txt";
    vol.open(acces,ios::out);
    std::cout << acces << std::endl;
    std::string name = "data/DVH"+taille_str+"/Volumetxt";
    if(vol)
        std::cout << "Bon emplacement" << std::endl;
    max=0;
    for (int i =(FOVx/2)-binX; i<(FOVx/2)+binX; i++) {
        for (int j =(FOVy/2)-binY; j<(FOVy/2)+binY; j++) {
            for (int k =0 ; k<FOVz; k++) {
                if(i>FOVx || j> FOVy) {
                    std::cout << "Erreur limite"<< std::endl;
                    break;
                    }
                VolumeElem[i][j][k]=(VolumeElem[i][j][k]*MeV)/mass_voxel;
                if(max<VolumeElem[i][j][k])
                    max=VolumeElem[i][j][k];
                }
            }
        }
    
    std::cout << max << std::endl;
    int DVH_taille=max;
    std::cout << DVH_taille*100 << std::endl;
    float DVH[DVH_taille*100];
    for(int i=0;i<DVH_taille*100;i++)
        DVH[i]=0;
    int cpt=0;
    output.open("data/projXZ.txt",ios::out);
    std::cout << "Début Projection + DVH" << std::endl;
    for (int i =(FOVx/2)-binX; i<(FOVx/2)+binX; i++) {
        for (int k =0 ; k<FOVz; k++) {
            for (int j =(FOVy/2)-binY; j<(FOVy/2)+binY; j++) {
                vol << i << " " << j <<  " " << k << " ";
                vol << VolumeElem[i][j][k] << std::endl;
                projXZ[i][k]+=VolumeElem[i][j][k];
                cpt++;
                for(int a=0;a<DVH_taille*100;a++) {
                    if(VolumeElem[i][j][k]*100>=a)
                        DVH[a]++;
                }
            }
            output << projXZ[i][k] << " " ;
        }
        output << std::endl;
    }
    output.close();
    std::cout << "Fin Cube" << std::endl;
    vol.close();
    output.open("data/DVH"+taille_str+"/DVH.txt",ios::out);
    std::cout << "data/DVH"+taille_str+"/DVH.txt" << std::endl;
    if(output)
        std::cout << "ok"<< std::endl;
    for(int i=0;i<DVH_taille*100;i++)
        output << i << " " << DVH[i] << std::endl;
    output.close();
}


