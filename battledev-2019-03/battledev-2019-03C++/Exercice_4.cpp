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
vector<vector<int>> generer(int min, int max, int k) 
{
    int nb = max - min + 1; // Le nombre d'entiers
    int size = bin(k, nb); // Le nombre de combinaisons de taille k possibles entre min et max
    vector<vector<int>> comb(size); // on les enregistrera dans ce vecteur
    
    if(k==1) {for(int i=min; i<=max; i++) {comb[i-min].insert(comb[i-min].end(), i);}} // Si k vaut 1, on a simlment le vecteurs contenant tou sles entiers (vecteurs de taille 1)
    
    else { // Sinon...
        for(int i=min; i<=max-k+1; i++) // Une combinaison de taille k doit commmencer avant max-k+1
        {
            // Le nombre de combinaisons avant de s'intéresser à celles commençant par i
            int n_comb = 0; 
            for(int j=min; j<i; j++) {n_comb += bin(k-1, max-j);}
            
            int s = bin(k-1, max-i); // Le nombre de combinaisons de taille k commençant par i
            
            // On va utiliser la récursivité
            vector<vector<int>>  sub = generer(i+1, max, k-1); // On récupère toutes les combinaisons de taille k-1 entre i+1 et max
            for(int t=0; t<s; t++) { // Pour chaque combinaison de taille k commençant par i
                vector<int> actu = comb[n_comb+t];
                actu[0] = i; // Le premier élément est i
                for(int m=0; m<k-1; m++) { // On regarde chaque élément de la combinaison de taille k-1
                    int ext = sub[t][m]; // On enregistre sa valeur
                    actu.insert(actu.end(), ext); // Et on l'ajoute à la combinaison de taille k commençant par i
                }
                comb[n_comb+t] = actu;
            }
        return comb;
        }
    }
}



/// FONCTION GENERATION DE TOUTES LES COMBINAISONS
vector<vector<int>> generer_all(int min, int max) 
{
    int nb = max - min +1; // Le nombre d'entiers
    
    // Calcul du nombre total de combinaisons
    int size = 0; 
    for(int k=1; k<=nb; k++) {size += bin(k, nb);}
    vector<vector<int>> all_comb(size);
    
    // Récupérer les combinaisons pour les insérer dans le vecteur all_comb
    int n_comb = 0;
    for(int k=1; k<=nb; k++) { // Pour chaque longueur de combinaison possible
        int sk = bin(k, nb); // On récupère le nombre de combinaisons de cette taile
        for(int i=0; i<sk; i++) {all_comb[n_comb+i] = generer(min, max, k)[i];} // On récupère toutes les combinaisons
        n_comb += sk; // On a rajouté sk combinaisons dans le vecteur all_comb
    }
    return all_comb;
}



void ContestExerciseImpl::main() 
{
    int N; cin >> N; // Le nombre de mots
    vector<vector<int>> Comb = generer_all(0, 9); // Les combinaisons croissantes des lettres (indexées par leur position)
    
    // CREATION DE TOUS LES MOTS POSSIBLES ISSUS DES N MOTS INITIAUX
    vector< vector<string> > Var(N); // on va y stocker tous les mots possibles
    for(int n=0; n<N; n++) // Pour chaque mot initial
    { 
        char mot_n[10]; // on écrit le mot sous forme de chaîne de caractères
        for(int k=0; k<10; k++) {cin >> mot_n[k];} // on met donc les lettres du mot dans la chaîne
        
        int nb_comb = 0; // Le nombre de combinaisons issues de ce mot jusqu'à présent
        
        for(int k=1; k<=10; k++) { // On peut écrire des mots de taille 1 à 10
            int sk = bin(k,10); // Il y a sk mots de taille k
            for(int i=0; i<sk; i++) {
                for(int j=0; j<k; j++) {
                    int pos = nb_comb+i;
                    string provisoire = Var[n][pos];
                    int pos_lettre = Comb[pos][j];
                    char lettre = mot_n[pos_lettre];
                    provisoire += lettre; // On les récupère tous à l'aide du vecteur Comb
                    Var[n][nb_comb+i] = provisoire;
                }
            } 
            nb_comb += sk; // et on a ajouté sk combinaisons
        }
    }
    
    // RECHERCHE DU PLUS LONG MOT QUI APPARAIT DANS TOUS LES VECTEURS DE string
    int m=1022; // On commence en regardant le mot le plus long dans le premier vecteur, puis on regarde des mots de plus en plus courts
    string mot; // Le mot que l'on recherche, le plus long
    int owned = 1; // Le nombre de vecteurs dans lequels le mot n°m du premier vecteur apparaît (il apparaît au moins une fois puisqu'il est dans le premier vecteur)
    
    while(owned != N) // Tant que le mot étudié n'apparaît pas dans tous les vecteurs
    {
        mot = Var[0][m]; // On enregistre le mot n°m du premier vecteur
        for(int n=1; n<N; n++) { // Pour chaque vecteur autre que le premier vecteur
            for(int i=1022; i>=0; i--) { // On va regarder les mots que le vecteur n°n possède dans l'ordre inverse
                string mot2 = Var[n][i]; // On enregistre son mot n°i
                if(mot == mot2) {owned++; break;} // S'il est égal au mot qu'on étudie, on le note et on peut passer au vecteur suivant
            }
            if(owned != n+1) { // Si le mot n'apparaît pas dans le vecteur n°n
                m--; // On passe à un autre mot dans le premier vecteur
                owned = 1; // et owned reprend la valeur 1
            }
        }
    }
    
    cout << "bonjour";
}

