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

void ContestExerciseImpl::main() 
{
    int N; cin >> N; // On récupère la taille du couloir
    
    int pos; // La position du joueur
    vector<int> Coin; // Pour les positions des pièces
    vector<int> Mult; // Pour les positions des multiplicateurs
    
    char couloir[N]; // On commence par modéliser le couloir par une chaîne de caractères
    for(int k=0; k<N; k++) {
        cin >> couloir[k]; // On vérifie quel est le symbole à la position [k,l]
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
    string sequence; // La séquence de déplacements et actions que l'on aura en sortie
    
    while(R<N-1) // Tant qu'on a pas ramassé tous les items
    { 
        // Tant que la pièce la plus à gauche (existe et) est plus proche que le multiplicateur le plus à gauche
        while((cL >= 0)&&(((mL >= 0)&&(Coin[cL] > Mult[mL]))||(mL == -1))) { 
            pos = Coin[cL]; // on se déplace vers la pièce
            sequence += 'o'; R++; // on la ramasse
            cL--; // la pièce la plus proche à gauche est alors la précédente (si elle existe)
        }
        
        // Tant que la pièce la plus à droite (existe et) est plus proche que le multiplicateur le plus à droite
        while((cR < NC)&&(((mR < NM)&&(Coin[cR] < Mult[mR]))||(mR == NM))) {
            pos = Coin[cR]; // on se déplace vers la pièce
            sequence += 'o'; R++; // on la ramasse
            cR++; // la pièce la plus proche à droite est alors la suivante (si elle existe)
        }
        
        // Tant que pièces et multiplicateurs existent à droite et à gauche, les multiplicateurs étant plus proches
        while((cL >= 0)&&(mL >= 0)&&(Coin[cL] < Mult[mL])&&(cR < NC)&&(mR < NM)&&(Coin[cR] > Mult[mR])) 
        { 
            int nb_left = Mult[mL] - Coin[cL]; // Nombre de multiplicateurs devant la pièce la plus à gauche
            int nb_right = Coin[cR] - Mult[mR]; // Nombre de multiplicateurs devant la pièce la plus à droite
            
            if(nb_left <= nb_right) { // Si il y a moins de multiplicateurs à gauche
                pos = Mult[mL]; // on se déplace vers le multiplicateur
                sequence += '*'; R++; // on le ramasse
                mL--; // le multiplicateur le plus proche à gauche est alors le précédent (si il existe)
            }
            else { // Si il y a moins de multiplicateurs à droite
                pos = Mult[mR]; // on se déplace vers le multiplicateur
                sequence += '*'; R++; // on le ramasse
                mR++; // le multiplicateur le plus proche à droite est alors le suivante (si il existe)
            }
        }
        
        // Si il n'y a plus de pièces à ramasser à gauche mais qu'il y en a à droite
        if((cL == -1)&&(cR < NC)) {
            pos = Mult[mR]; // on se déplace jusqu'à l'item le plus proche
            sequence += '*'; R++; //et on le ramasse
            mR++; // le multiplicateur le plus proche à droite est alors le suivante (si il existe)
        }
        
        // Si il n'y a plus de pièces à ramasser à droite mais qu'il y en a à gauche
        if((cR == NC)&&(cL >= 0)) {
            pos = Mult[mL]; // on se déplace jusqu'à l'item le plus proche 
            sequence += '*'; R++; // et on le ramasse
            mL--; // le multiplicateur le plus proche à gauche est alors le précédent (si il existe)
        }
        
        // Si il n'y a plus de pièces à ramasser
        if((cL == -1)&&(cR == NC)) {
            int remaining = (mL+1) + (NM-mR); // Le nombre de multiplicateurs restants
            for(int s=0; s<remaining; s++) {sequence += '*';} // on termine en les ramassant
            R += remaining;
        }
    }
    
    cout << sequence;
}
   
