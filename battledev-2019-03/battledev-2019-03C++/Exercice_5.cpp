#include <iostream>
#include <limits>
#include <sstream>
#include "exercise.hpp"

#include <iostream>
#include <fstream>
using namespace std;

#include<string>
#include <vector>

#include <stdio.h>
#include <math.h> 

ContestExerciseImpl::ContestExerciseImpl() : Exercise() {}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

// FONCTION COMPTER : PERMET DE COMPTER LE NOMBRE D'OBJET IDENTIQUES COTE A COTE A DROITE ET A GAUCHE
int compter(int L, int R, vector<int> Obj) 
{
    int nb_L = 1; int nb_R = 1;                                 // Les outputs
    int S = Obj.size();                                         // Le nombre d'éléments dans le vecteur
    
    // Cas particuliers
    if(L==-1) {nb_L = 0;}                                       // Si on regarde à partir de l'extrémité gauche, il n'y a pas d'objets à gauche
    if(R==S) {nb_R = 0;}                                        // Si on regarde à partir de l'extrémité droite, il n'y a pas d'objets à droite
    
    int ind_L = L; int ind_R = R;                               // On commence à compter à gauche à partir de l'objet d'indice L, et à droite à partir de l'objet d'indice R
    
    while((ind_L >= 1)&&(Obj[ind_L-1] == Obj[ind_L]-1)) {       // Tant qu'il y a deux objets identiques consécutids à gauche
        nb_L++;                                                 // On ajoute 1 au compte
        ind_L--;                                                // Et on va regarder si le prochain objet à gauche est du même type
        
    }       
    while((ind_R <= S-2)&&(Obj[ind_R+1] == Obj[ind_R]+1)) {     // Tant qu'il y a deux objets identiques consécutids à droite
        nb_R++;                                                 // On ajoute 1 au compte
        ind_R++;                                                // Et on va regarder si le prochain objet à droite est du même type
        
    }
    
    return nb_L, nb_R;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

void ContestExerciseImpl::main() 
{
    int N; cin >> N;                                            // On récupère la taille du couloir
    
    vector<int> Coin;                                           // Pour les positions des pièces
    vector<int> Mult;                                           // Pour les positions des multiplicateurs
    int pos;                                                    // La position du joueur
    
    char couloir[N];                                            // On commence par modéliser le couloir par une chaîne de caractères
    for(int k=0; k<N; k++) {                                    // Pour chaque indice k dans la chaîne de caractères
        cin >> couloir[k];                                      // On enregistre le symbole correspondant
        if(couloir[k] == 'o') {Coin.insert(Coin.end(), k);}     // Si c'est une pièce on enregistre sa position dans Coin
        if(couloir[k] == '*') {Mult.insert(Mult.end(), k);}     // Si c'est un multiplicateur on enregistre sa position dans Mult
        if(couloir[k] == 'X') {pos = k;}                        // Si c'est la croix il s'agit de la position du joueur
    } 
    
    int NC = Coin.size();                                       // Le nombre de pièces dans le couloir
    int NM = Mult.size();                                       // Le nombre de multiplicateurs dans le couloir
    
    int cL = -1; int cR = NC;                                   // Indices dans Coin des position des pièces les plus proches à droite et à gauche
    int mL = -1; int mR = NM;                                   // Indices dans Mult des position des multiplicateurs les plus proches à droite et à gauche
    
    for(int c=0; c<NC; c++) {                                   // Calcul des indices des pièces les plus proches
        if((Coin[c] < pos)&&(c > cL)) {cL = c;}
        if((Coin[c] > pos)&&(c < cR)) {cR = c;}
    }
    for(int m=0; m<NM; m++) {                                   // Calcul des indices des multiplicateurs les plus proches
        if((Mult[m] < pos)&&(m > mL)) {mL = m;}
        if((Mult[m] > pos)&&(m < mR)) {mR = m;}
    }
    
    //.......................................................................................................................................................
    
    int R = 0;          // Nombre d'item ramassés
    int score = 0;      // Score obtenu après le ramassage d'items
    string sequence;    // La séquence d'item ramassés
    
    while(R<N-1)        // Tant qu'on a pas ramassé tous les items
    { 
        // CAS SIMPLES ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
        
        while((cL >= 0)&&(((mL >= 0)&&(Coin[cL] > Mult[mL]))||(mL == -1))) {    // Tant que la pièce la plus à gauche (existe et) est plus proche que le multiplicateur le plus à gauche
            sequence += 'o'; R++; score++;                                      // on la ramasse
            cL--;                                                               // la pièce la plus proche à gauche est alors la précédente (si elle existe)
        }
        
        while((cR < NC)&&(((mR < NM)&&(Coin[cR] < Mult[mR]))||(mR == NM))) {    // Tant que la pièce la plus à droite (existe et) est plus proche que le multiplicateur le plus à droite
            sequence += 'o'; R++; score++;                                      // on la ramasse
            cR++;                                                               // la pièce la plus proche à droite est alors la suivante (si elle existe)
        }
        
        // CAS COMPLIQUES ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
        
        // Tant que pièces et multiplicateurs existent à droite et à gauche, les multiplicateurs étant plus proches
        while((cL >= 0)&&(mL >= 0)&&(Coin[cL] < Mult[mL])&&(cR < NC)&&(mR < NM)&&(Coin[cR] > Mult[mR])) 
        { 
            sequence += '*'; R++; score *= 2;                                   // Dans tous les cas on ramasse un multiplicateur
            
            // Ramasse-t-on à droite ou à gauche?
            int left_mult = 0; int right_mult = 0;                              // Nombre de multiplicateurs à droite et à gauche
            int left_coin = 0; int right_coin = 0;                              // Nombre de pièces à droite et à gauche
            int indM_left = mL; int indM_right = mR;                            // Pour compter les multiplicateurs
            int indC_left = cL; int indC_right = cR;                            // Pour compter les pièces
            int res_left; int res_right;
            
            while((left_mult == right_mult)&&(left_coin == right_coin))         // Tant que le nombre d'items identiques consécutifs comptés à droite et à gauche est le même
            { 
                // On utilise la fonction "compter" définie plus haut
                left_mult, right_mult = compter(indM_left, indM_right, Mult); 
                left_coin, right_coin = compter(indM_left, indM_right, Coin); 
                indM_left -= left_mult; indM_right += right_mult;               // Si on a besoin de recompter des multipplicateurs dans une nouvelle itération, on s'intéressera à ceux plus aux bords
                indC_left -= left_coin; indC_right += right_coin;               // Si on a besoin de recompter des pièces dans une nouvelle itération, on s'intéressera à celles plus aux bords
                res_left = (score * pow(2, left_mult) + left_coin) * pow(2, right_mult); 
                res_right = (score  * pow(2, right_mult) + right_coin) * pow(2, left_mult); 
            }
            
            if(res_left >= res_right) {mL--;}
            else {mR++;}
        }
        
        // CAS SIMPLES (FIN DU RAMASSAGE) ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
        
        if((cL == -1)&&(cR < NC)) {                                     // Si il n'y a plus de pièces à ramasser à gauche mais qu'il y en a à droite
            sequence += '*'; R++; score *= 2;                           // on ramasse l'item le plus proche à droite, qui est forcément un multiplicateur
            mR++;                                                       // le multiplicateur le plus proche à droite est alors le suivante (si il existe)
        }
        
        if((cR == NC)&&(cL >= 0)) {                                     // Si il n'y a plus de pièces à ramasser à droite mais qu'il y en a à gauche
            sequence += '*'; R++; score *= 2;                           // on ramasse l'item le plus proche à gauche, qui est forcément un multiplicateur
            mL--;                                                       // le multiplicateur le plus proche à gauche est alors le précédent (si il existe)
        }
        
        if((cL == -1)&&(cR == NC)) {                                    // Si il n'y a plus de pièces à ramasser
            int remaining = (mL+1) + (NM-mR);                           // Le nombre de multiplicateurs restants
            for(int s=0; s<remaining; s++) {sequence += '*';}           // On termine en les ramassant
             R += remaining;                                            // On a ramassé remaining items
        }
    }
    
    cout << sequence;
}










   
