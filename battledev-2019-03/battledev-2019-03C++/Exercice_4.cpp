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
    int K = 10*N; // Le nombre de caractères
    
    // On écrit les mots dans une seule chaîne de caractères
    char Mots[K]; 
    for(int i=0; i<K; i++) {cin >> Mots[i];}
}
