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
    int N; cin >> N; // On récupère la taille de la grille
    int K = int(pow(N,2));
    char grille[K]; for(int k=0; k<N; k++) {for(int l=0; l<N; l++) {cin >> grille[N*k+l];} } // On commence par modéliser la grille par une chîne de caractères
    
    string sequence; // La séquence de déplacements et actions que l'on aura en sortie
    
    // On va avoir besoin d'enregistrer les positions des multiplicateurs
    vector<int> Pos_i; vector<int> Pos_j;
    
    int i = 0; int j= 0; // On se place sur la case en haut à gauche de la grille
   
    // Dans un premier temps on va ramasser toutes les pièces et enregistrer les positions des multiplicateurs en scannant toutes les cases de la grille 
    while(i<N) // Tant que l'on est sur la grille
    { 
        char symb = grille[N*i+j]; // on regarde ce qu'il y a sur la case
        
        if(symb == 'o') {sequence += 'x';} // si c'est une pièce on la ramasse
        if(symb == '*') {Pos_i.insert(Pos_i.end(), i); Pos_j.insert(Pos_j.end(), j);} // si c'est un multiplicateur on enregistre sa position
        
        if(i%2 == 0) { // si on est sur une ligne "paire" (on se déplace de gauche à droite)
            if(j < N-1) { // si on est pas sur le bord droit
                sequence += '>'; // on se déplace vers la droite
                j++; 
            }
            else { // si on est sur le bord droit
                if(i < N-1) {sequence += 'v';} // et si on est pas à la dernière ligne, on descend d'une ligne
                i++;
            }
        }
        
        else { // si on est sur une ligne "impaire" (on se déplace de droite à gauche)
            if(j > 0) { // si on est pas sur le bord gauche
                sequence += '<'; // on se déplace vers la gauche
                j--;
            }
            else { // si on est sur le bord gauche 
                if(i < N-1) {sequence += 'v';} // et si on est pas à la dernière ligne, on descend d'une ligne
                i++;
            }
        }
   }
   
   // On va maintenant récupérer tous les multiplicateurs
   i = N-1; // On se remet sur la dernière ligne
   int S = Pos_i.size(); // Le nombre de multiplicateurs
   int s = S-1; // On va ramasser les multiplicateurs dans l'ordre inverse d'apparition
   
    while(s>=0) // Tant qu'on a pas ramassé tous les multiplicateurs
    { 
        int m_i = Pos_i[s]; int m_j = Pos_j[s]; // on note la position du multiplicateur n°s
        int diff_i = i - m_i; int diff_j = j - m_j; // on vérifie le chemin à parcoourir (on aura toujours diff_i positif ou nul)
        
        if(diff_i > 0) { // si il y a un déplacement vertical à faire
            for(int k=0; k<diff_i; k++ ) {sequence += '^';} // on monte diff_i lignes
        }
        
        if(diff_j > 0) { // si il y a un déplacement horizontal de droite à gauche à faire
            for(int l=0; l<diff_j; l++ ) {sequence += '<';} // on décale de diff_j colonnes vers la gauche
        }
        if(diff_j < 0) { // si il y a un déplacement horizontal de gauche à droite à faire
            for(int l=0; l<abs(diff_j); l++) {sequence += '>';} // on décale de diff_j colonnes vers la droite
        }
        
        i = m_i; 
        j = m_j;
        
        sequence += 'x'; // On ramasse le multiplicateur
        s--; // on passe au prochain multiplicateur à ramasser
   }
   
   cout << sequence;
}
