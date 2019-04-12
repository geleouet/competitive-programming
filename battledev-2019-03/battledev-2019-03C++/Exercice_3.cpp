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
    int N; cin >> N;                                // On récupère la taille de la grille
    int K = int(pow(N,2));                          // le nombre de cases dans la grille
    
    vector<int> Coin_i; vector<int> Coin_j;         // Pour les positions des pièces
    vector<int> Mult_i; vector<int> Mult_j;         // Pour les positions des multiplicateurs
    
    char grille[K];                                 // On commence par modéliser la grille par une chaîne de caractères
    for(int k=0; k<N; k++) {
        for(int l=0; l<N; l++) {
            cin >> grille[N*k+l];                   // On vérifie quel est le symbole à la position [k,l]
            if(grille[N*k+l] == 'o') {Coin_i.insert(Coin_i.end(), k); Coin_j.insert(Coin_j.end(), l);} // si c'est une pièce on enregistre sa position
            if(grille[N*k+l] == '*') {Mult_i.insert(Mult_i.end(), k); Mult_j.insert(Mult_j.end(), l);} // si c'est un multiplicateur on enregistre sa position
        } 
    } 
    
    string sequence;                                // La séquence de déplacements et actions que l'on aura en sortie
    
    //..................................................................................................................................
    
    // Dans un premier temps on va ramasser toutes les pièces
    int i = 0; int j= 0;                                            // On se place sur la case en haut à gauche de la grille
    int NC = Coin_i.size();                                         // Le nombre de pièces à ramasser
    int c = 0;                                                      // On va ramasser les pièces dans l'ordre d'apparition
    while(c<NC)                                                     // Tant qu'on a pas ramassé toutes les pièces
    { 
        int c_i = Coin_i[c]; int c_j = Coin_j[c];                   // on note la position de la pièce n°c
        int diff_i = c_i - i; int diff_j = c_j - j;                 // on vérifie le chemin à parcourir (on aura toujours diff_i positif ou nul)
        
        if(diff_i > 0) {                                            // si il y a un déplacement vertical à faire
            for(int k=0; k<diff_i; k++ ) {sequence += 'v';}         // on descend diff_i lignes
        }
        
        if(diff_j < 0) {                                            // si il y a un déplacement horizontal de droite à gauche à faire
            for(int l=0; l<abs(diff_j); l++ ) {sequence += '<';}    // on décale de diff_j colonnes vers la gauche
        }
        if(diff_j > 0) {                                            // si il y a un déplacement horizontal de gauche à droite à faire
            for(int l=0; l<diff_j; l++) {sequence += '>';}          // on décale de diff_j colonnes vers la droite
        }
                                                                    // et on est maintenant sur las case [c_i, c_j]
        i = c_i; 
        j = c_j;
        
        sequence += 'x';                                            // On ramasse la pièce
        c++;                                                        // on passe à la  prochaine pièce à ramasser
    }
    
    //..................................................................................................................................
   
    // On va maintenant récupérer tous les multiplicateurs
    int NM = Mult_i.size();                                         // Le nombre de multiplicateurs
    int m = NM-1;                                                   // On va ramasser les multiplicateurs dans l'ordre inverse d'apparition
    while(m>=0)                                                     // Tant qu'on a pas ramassé tous les multiplicateurs
    { 
        int m_i = Mult_i[m]; int m_j = Mult_j[m];                   // on note la position du multiplicateur n°s
        int delta_i = i - m_i; int delta_j = j - m_j;               // on vérifie le chemin à parcourir (on aura toujours delta_i positif ou nul, sauf pour ramasser le premier multiplicateur)
        
        if(delta_i > 0) {                                           // si il y a un déplacement vertical à faire
            for(int k=0; k<delta_i; k++ ) {sequence += '^';}        // on monte delta_i lignes
        }
        if(delta_i < 0) {                                           // si il y a un déplacement vertical à faire
            for(int k=0; k<abs(delta_i); k++ ) {sequence += 'v';}   // on descend delta_i lignes
        }
        
        if(delta_j > 0) {                                           // si il y a un déplacement horizontal de droite à gauche à faire
            for(int l=0; l<delta_j; l++ ) {sequence += '<';}        // on décale de delta_j colonnes vers la gauche
        }
        if(delta_j < 0) {                                           // si il y a un déplacement horizontal de gauche à droite à faire
            for(int l=0; l<abs(delta_j); l++) {sequence += '>';}    // on décale de delta_j colonnes vers la droite
        }
                                                                    // et on est maintenant sur las case [m_i, m_j]
        i = m_i; 
        j = m_j;
        
        sequence += 'x';                                            // On ramasse le multiplicateur
        m--;                                                        // on passe au prochain multiplicateur à ramasser
    }
   
   cout << sequence;
}
