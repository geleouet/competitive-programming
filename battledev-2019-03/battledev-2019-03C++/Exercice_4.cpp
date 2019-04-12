#include <iostream>
#include <limits>
#include <sstream>
#include "exercise.hpp"

#include <fstream>

using namespace std;

#include<string>
#include <vector>

#include <stdio.h>
#include <math.h> 

ContestExerciseImpl::ContestExerciseImpl() : Exercise() {}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

// FONTION FACTORIELLE
int fact(int n) {
    if(n==0) {return 1;}
    else {return n*fact(n-1);}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

// FONCTION BINOMIALE
int bin(int a, int b){
    if(a>b) {return 0;}
    else{return int(fact(b)/(fact(a)*fact(b-a)));}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

// FONCTION GENERATION DE COMBINAISONS D'ENTIERS DE TAILLE k
vector<vector<int> > generer(int min, int max, int k) 
{
    int nb = max - min + 1;                                                     // Le nombre d'entiers entre min et max
    int size = bin(k, nb);                                                      // Le nombre de combinaisons de taille k possibles entre min et max
    vector<vector<int> > comb(size);                                            // On les enregistrera dans ce vecteur
    for(int i=0; i<size; i++) {comb[i] = vector<int>(k);}                       // On a donc des sous-vecteurs de tailles k
    
    if(k==1) {                                                                  // Si k vaut 1
        for(int i=min; i<=max; i++) {                                           // chaque sous_vecteur
            comb[i-min] = vector<int>(1);                                       // est de taille 1
            comb[i-min][0] = i;                                                    // et contient un entier entre min et max
        } 
    } 
    else { 
        int n_comb = 0;                                                         // Le nombre de combinaisons de taille k étudiées jusqu'à présent
        for(int i=min; i<=max-k+1; i++) {                                       // Une chaîne de taille k commence avant max-k+1
            vector<vector<int> > sub = generer(i+1, max, k-1);                  // On récupère toutes les combinaisons de taille k-1 entre i+1 et max
            int s = bin(k-1, max-i);                                            // Le nombre de combinaisons de taille k commençant par i
            for(int t=0; t<s; t++) {                                            // Pour chaque combinaison de taille k commençant par i
                comb[n_comb+t][0] = i;                                          // Le premier élément est i
                for(int m=0; m<k-1; m++) {comb[n_comb+t][m+1] = sub[t][m];}     // Et on ajoute une combinaison de taille k-1 entre i+1 et max
            }
            n_comb += s;                                                        // On a étudié s combinaisons de plus
        }
    }
    return comb;                                                                // On a toutes les combinaisons de taille k
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

// FONCTION GENERATION DE TOUTES LES COMBINAISONS
vector<vector<int> > generer_all(int min, int max) 
{
    int nb = max - min +1;                                                      // Le nombre d'entiers entre min et max
    int size = 0; for(int k=1; k<=nb; k++) {size += bin(k, nb);}                // Le nombre total de combinaisons
    vector<vector<int> > all_comb(size);                                        // Le vecteur dans lequel on va enregistrer toutes les combinaisons 

    // Récupérer les combinaisons pour les insérer dans le vecteur all_comb
    int n_comb = 0;
    for(int k=1; k<=nb; k++) {                                                  // Pour chaque longueur de combinaison k possible
        vector<vector<int> > sub = generer(min, max, k);                        // On récupère les combinaisons de taille k dans un vecteur sub
        int sk = bin(k, nb);                                                    // Le nombre de combinaisons de taille k
        for(int i=0; i<sk; i++) {                                               // Pour chaque combinaison de taille k
            all_comb[n_comb+i] = vector<int>(k);                                // On a des sous-vecteurs de taille k               
            for(int j=0; j<k; j++) {all_comb[n_comb+i][j] = sub[i][j];}         // On récupère toutes les combinaisons générées dans sub
        }     
        n_comb += sk;                                                           // On a rajouté sk combinaisons dans le vecteur all_comb
    }
    return all_comb;                                                            // On a toutes les combinaisons possibles
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

// FONCTION MAIN
void ContestExerciseImpl::main() 
{
    int N; cin >> N;                                                    // Le nombre de mots
    vector<vector<int> > Comb = generer_all(0, 9);                      // Les combinaisons croissantes des lettres (indexées par leur position)
    
    // CREATION DE TOUS LES SOUS-MOTS POSSIBLES ISSUS DES N MOTS INITIAUX
    vector<vector<string> > Var(N);                                     // On va y stocker tous les mots possibles
    for(int n=0; n<N; n++)                                              // Pour chaque mot initial
    { 
        Var[n] = vector<string>(1023)  ;                                // On peur créer 1023 sous-mots
        char mot_n[10]; for(int k=0; k<10; k++) {cin >> mot_n[k];}      // On écrit le mot initial sous forme de chaîne de caractères
        
        int nb_comb = 0;                                                // Le nombre de combinaisons issues de ce mot jusqu'à présent
        for(int k=1; k<=10; k++) {                                      // On peut écrire des mots de taille 1 à 10
            int sk = bin(k,10);                                         // Il y a sk mots de taille k
            for(int i=0; i<sk; i++) {                                   // Pour chaque combinaison de taille k
                for(int j=0; j<k; j++) {                                // Pour chaque entier de cette combinaison
                    Var[n][nb_comb+i] += mot_n[Comb[nb_comb+i][j]];     // On récupère la lettre correspondante et on l'ajoute au string 
                }
            } 
            nb_comb += sk;                                              // On a ajouté sk combinaisons
        }
    }
    
    //..........................................................................................................................................................
    
    // RECHERCHE DU PLUS LONG MOT QUI APPARAIT DANS TOUS LES VECTEURS DE string
    int m=1022;                                             // On commence en regardant le mot le plus long dans le premier vecteur
    string mot;                                             // Le mot que l'on recherche, le plus long
    int owned = 1;                                          // Le nombre de vecteurs dans lequels le mot n°m du premier vecteur apparaît
    
    while(owned != N)                                       // Tant que le mot étudié n'apparaît pas dans tous les vecteurs
    {
        mot = Var[0][m];                                    // On enregistre le mot n°m du premier vecteur
        for(int n=1; n<N; n++) {                            // Pour chaque vecteur autre que le premier vecteur
            for(int i=1022; i>=0; i--) {                    // On va regarder les mots que le vecteur n°n possède dans l'ordre inverse
                string mot2 = Var[n][i];                    // On enregistre son mot n°i
                if(mot == mot2) {owned++; break;}           // S'il est égal au mot qu'on étudie, on le note et on peut passer au vecteur suivant
            }
            if(owned != n+1) {                              // Si le mot n'apparaît pas dans le vecteur n°n
                m--;                                        // On passe à un autre mot, plus court, dans le premier vecteur
                owned = 1;                                  // Et owned reprend la valeur 1
            }
        }
    }
    
    cout << mot;
}

