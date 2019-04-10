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

int compter(int L, int R, vector<int> Pos) 
{
    int nb_L = 1; int nb_R = 1; // Les outputs
    int S = Pos.size(); // Le nombre d'éléments dans le vecteur
    
    // Cas particuliers
    if(L==-1) {nb_L = 0;}
    if(R==S) {nb_R = 0;}
    
    int ind_L = L; int ind_R = R;
    
    while((ind_L >= 1)&&(Pos[ind_L-1] == Pos[ind_L]-1)) {nb_L++; ind_L--;}
    while((ind_R <= S-2)&&(Pos[ind_R+1] == Pos[ind_R]+1)) {nb_R++; ind_R++;}
    
    return nb_L, nb_R;
}

void ContestExerciseImpl::main() 
{
    int N; cin >> N; // On récupère la taille du couloir
    
    int pos; // La position du joueur
    vector<int> Coin; // Pour les positions des pièces
    vector<int> Mult; // Pour les positions des multiplicateurs
    
    char couloir[N]; // On commence par modéliser le couloir par une chaîne de caractères
    for(int k=0; k<N; k++) {
        cin >> couloir[k]; // On vérifie quel est le symbole à la position k
        if(couloir[k] == 'o') {Coin.insert(Coin.end(), k);} // si c'est une pièce on enregistre sa position
        if(couloir[k] == '*') {Mult.insert(Mult.end(), k);} // si c'est un multiplicateur on enregistre sa position
        if(couloir[k] == 'X') {pos = k;} // si c'est la croix il s'agit de la position du joueur
    } 
    
    int NC = Coin.size(); // Le nombre de pièces
    int NM = Mult.size(); // Le nombre de multiplicateurs
    
    int cL = -1; int cR = NC; // Pour connaître les indices des position des pièces les plus proches à droite et à gauche dans le vecteur Coin
    int mL = -1; int mR = NM; // Pour connaître les indices des position des multiplicateurs les plus proches à droite et à gauche dans le vecteur Mult
    
    for(int c=0; c<NC; c++) {
        if((Coin[c] < pos)&&(c > cL)) {cL = c;}
        if((Coin[c] > pos)&&(c < cR)) {cR = c;}
    }
    for(int m=0; m<NM; m++) {
        if((Mult[m] < pos)&&(m > mL)) {mL = m;}
        if((Mult[m] > pos)&&(m < mR)) {mR = m;}
    }
    
    int R = 0; // Nombre d'item ramassés
    string sequence; // La séquence d'item ramassés
    
    while(R<N-1) // Tant qu'on a pas ramassé tous les items
    { 
        // Tant que la pièce la plus à gauche (existe et) est plus proche que le multiplicateur le plus à gauche (qui existe ou non)
        while((cL >= 0)&&(((mL >= 0)&&(Coin[cL] > Mult[mL]))||(mL == -1))) { 
            sequence += 'o'; R++; // on la ramasse
            cL--; // la pièce la plus proche à gauche est alors la précédente (si elle existe)
        }
        
        // Tant que la pièce la plus à droite (existe et) est plus proche que le multiplicateur le plus à droite (qui existe ou non)
        while((cR < NC)&&(((mR < NM)&&(Coin[cR] < Mult[mR]))||(mR == NM))) {
            sequence += 'o'; R++; // on la ramasse
            cR++; // la pièce la plus proche à droite est alors la suivante (si elle existe)
        }
        
        // Tant que pièces et multiplicateurs existent à droite et à gauche, les multiplicateurs étant plus proches
        while((cL >= 0)&&(mL >= 0)&&(Coin[cL] < Mult[mL])&&(cR < NC)&&(mR < NM)&&(Coin[cR] > Mult[mR])) 
        { 
            // Initialisation du calcul
            int left = 0; int right = 0;
            int indM_left = mL; int indM_right = mR;
            int indC_left = cL; int indC_right = cR;
            vector<int> Positions = Mult;
            
            while(left == right) {
                if(Positions == Mult) {
                    left, right = compter(indM_left, indM_right, Positions);
                    indM_left -= left; indM_right += right;
                    Positions = Coin;
                }
                if(Positions == Coin) {
                    left, right = compter(indC_left, indC_right, Positions);
                    indC_left -= left; indC_right += right;
                    Positions = Mult;
                }
            }
            
            if(left < right) { // Si il y a moins de multiplicateurs à gauche
                sequence += '*'; R++; // on ramasse le premier multiplicateur à gauche
                mL--; // le multiplicateur le plus proche à gauche est alors le précédent (si il existe)
            }
            if(left > right) { // Si il y a moins de multiplicateurs à droite
                sequence += '*'; R++; // on ramasse le premier multiplicateur à droite
                mR++; // le multiplicateur le plus proche à droite est alors le suivant (si il existe)
            }
            /*if(nb_left == nb_right) { 
                int coin_left; int coin_right; 
                coin_left, coin_right = compter(cL, cR, Coin);
                
                // Et maintenant on ramasse le premier multiplicateur du coté où il y a le plus de pièces 
                sequence += '*'; R++; // dans tous les cas on ramasse un multiplicateur
                if(coin_left < coin_right) {mR++;} // si c'est à droite, le multiplicateur le plus proche à droite est alors le suivant (si il existe)
                if(coin_left > coin_right) {mL--;} // si c'est à gauche, le multiplicateur le plus proche à gauche est alors le précédent (si il existe)
                if(coin_left == coin_right) {
                    int mult_left; int mult_right;
            }*/
        }
        
        // Si il n'y a plus de pièces à ramasser à gauche mais qu'il y en a à droite
        if((cL == -1)&&(cR < NC)) {
            sequence += '*'; R++; // on ramasse l'item le plus proche à droite, qui est forcément un multiplicateur
            mR++; // le multiplicateur le plus proche à droite est alors le suivante (si il existe)
        }
        
        // Si il n'y a plus de pièces à ramasser à droite mais qu'il y en a à gauche
        if((cR == NC)&&(cL >= 0)) {
            sequence += '*'; R++; // on ramasse l'item le plus proche à gauche, qui est forcément un multiplicateur
            mL--; // le multiplicateur le plus proche à gauche est alors le précédent (si il existe)
        }
        
        // Si il n'y a plus de pièces à ramasser
        if((cL == -1)&&(cR == NC)) {
            int remaining = (mL+1) + (NM-mR); // Le nombre de multiplicateurs restants
            for(int s=0; s<remaining; s++) {sequence += '*';} R += remaining; // on termine en les ramassant
        }
    }
    
    cout << sequence;
}










   
