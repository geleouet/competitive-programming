#include <iostream>
#include <limits>
#include <sstream>
#include "exercise.hpp"

using namespace std;
#include<string>
#include <vector>

ContestExerciseImpl::ContestExerciseImpl() : Exercise() {}

void ContestExerciseImpl::main() 
{
    int N; cin >> N; // Le nombre de mots
    int K = 10*N; // Le nombre de lettres
    
    // On écrit les mots dans une seule chaîne de caractères
    char Mots[K]; 
    for(int k=0; k<K; k++) {cin >> Mots[k];}
    
    vector<vector<int>> Communs[N]; // Pour noter les positions des lettres, qui apparaissent dans tous les mots, dans chaque mot
    
    // On commence par regarder les lettres du premier mots, pour vérifier si elles apparaissent dans les autres mots
    for(int l=0; l<10; l++) { // pour chaque lettre du premier mot 
        // on vérifie que la lettre apparaît dans tous les mots
        int n_mots = 1; // Pour retenir le nombre de mots dans lesquels la lettre étudiée apparaît
        for(int m=1; m<N; m++) { // Pour chaque autre mot
            int memory = n_mots; // on mémorise le nombre de mots dans lesquels la lettre apparaît jusqu'ici
            int app = 0; // et on va compter le nombre de fois où elle apparaît dans ce mot
            
            for(int j=0; j<10; j++) { // Pour chaque lettre de cet autre mot
                if(Mots[l] == Mots[10*m+j]) { // si c'est la lettre que l'on étudie
                    app++; // on note qu'elle est apparue une fois de plus
                }
            }
            
            n_mots += (app!=0); // On note si la lettre est apparue au moins une fois dans cet autre mot
            if(memory == n_mots) {break;} // Si la lettre n'apparaît pas dans cet autre mot, on n'a pas besoin de regarder dans les autres mots
        }
        if(n_mots == N) { // Si la lettre apparaît bien dans tous les mots
            Communs[0].insert(Communs[0].end(), l); // On note la position de la lettre dans le mot
        }
    }
}
