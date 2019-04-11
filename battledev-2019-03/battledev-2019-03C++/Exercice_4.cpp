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

// FONTION FACTORIELLE
int fact(int n) {
    if(n==0) {return 1;}
    else {return n*fact(n-1);}
}

// FONCTION BINOMIALE
int bin(int a, int b){
    if(a>b) {return 0;}
    else{return fact(b)/(fact(a)*fact(b-a));}
}

// FONCTION GENERATION DE COMBINAISONS D'ENTIERS DE TAILLE k
vector< vector<int> > generer(int min, int max, int k) 
{
    int nb = max - min + 1; // Le nombre d'entiers
    int size = bin(k, nb); // Le nombre de combinaisons possibles entre min et max
    vector< vector<int> > comb(size); // on les enregistrera dans ce vecteur
    
    for(int i=min; i<= max-k+1; i++) {
        int s = bin(k-1, max-i); // Le nombre de combinaisons de taille k commençant par i
        
        // Le nombre de combinaisons avant de s'intéresser à celles commençant par i
        int n_comb = 0; 
        for(int j=min; j<i; j++) {n_comb += bin(k-1, max-j);}
        
        // On va utiliser la récursivité
        for(int t=0; t<s; t++) {
            comb[n_comb+t][0] = i;
            vector<int> extension[k-1] = generer(i+1, max, k-1)[t];
            comb[n_comb+t].push_back(extension);
            //for(int m=0; m<k-1; m++) {comb[n_comb+t].insert(comb[n_comb+t].end(), extension[m]);}
        }
    return comb;
    }
}

/// FONCTION GENERATION DE TOUTES LES COMBINAISONS
vector< vector<int> > generer_all(int min, int max) {
    int nb = max - min +1; // Le nombre d'entiers
    
    // Calcul du nombre total de combinaisons
    int size = 0; 
    for(int k=1; k<=nb; k++) {size += bin(k, nb);}
    vector< vector<int> > all_comb(size);
    
    // Récupérer les combinaisons pour les insérer dans le vecteur all_comb
    int n_comb = 0;
    for(int k=1; k<=nb; k++) { // Pour chaque longueur de combinaison possible
        int sk = bin(k, nb); // On récupère le nombre de combinaisons de cette taile
        for(int i=0; i<bin(k, nb); i++) {all_comb[n_comb+i] = generer(min, max, k)[i];} // On récupère toutes les combinaisons
        n_comb += bin(k, nb); // On a rajouté bin(k, nb) combinaisons dans le vecteur all_comb
    }
    return all_comb;
}

void ContestExerciseImpl::main() 
{
    int N; cin >> N; // Le nombre de mots
    vector< vector<int> > Comb = generer_all(0, 9); // Les combinaisons croissantes des lettres (indexées par leur position)
    vector< vector<string> > Var(N);
    
    for(int n=0; n<N; n++) { // Pour chaque mot
        char mot[10]; for(int k=0; k<10; k++) {cin >> mot[k];} // on crée uune chaîne de caractères comprenant les lettres du mot
        int nb_comb = 0; // Le nombre de combinaisons issues de ce mot jusqu'à présent
        
        for(int k=1; k<10; k++) { // On peut écrire des mots de taille 1 à 10
            int sk = bin(k,10); // Il y a sk mots de taille k
            for(int i=0; i<sk; i++) {for(int j=0; j<k; j++) {Var[n][i] += mot[Comb[nb_comb+i][j]];}} // On les récupère tous à l'aide du vecteur Comb
            nb_comb += sk;
        }
    }
    
    // RECHERCHE DU PLUS LONG MOT QUI APPARAIT DANS TOUS LES VECTEURS DE string
    int m=1022; // On commence en regardant le mot le plus long dans le premier vecteur, puis on regarde des mots de plus en plus courts
    string mot;
    int owned = 1; // Le nombre de vecteurs dans lequels le mot n°m du premier vecteur apparaît (il apparaît au moins une fois)
    
    while(owned != N) // Tant que le mot étudié n'apparît pas dans tous les vecteurs
    {
        mot = Var[0][m]; // On enregistre le mot n°m du premier vecteur
        for(int n=1; n<N; n++) { // Pour chaque vecteur autre que le premier vecteur
            int memory = owned; // On retient le nombre de vecteurs dans lequel le mot est apparu jusqu'à présent
            for(int i=1022; i<=0; i--) { // On va regarder les mots que le vecteur n°n possède dans l'ordre inverse
                string mot2 = Var[n][i]; // On enregistre son mot n°i
                if(mot == mot2) {owned++; break;} // S'il est égal au mot qu'on étudie, on le note et on peut passer au vecteur suivant
            }
            if(memory == owned) { // Si le mot n'apparaît pas dans le vecteur n°n
                m--; // On passe à un autre mot dans le premier vecteur
                owned = 1; // et owned reprend la valeur 1
            }
        }
    }
    
    cout << mot;
}

