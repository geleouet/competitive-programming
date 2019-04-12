#include <iostream>
#include <limits>
#include <sstream>
#include "exercise.hpp"

ContestExerciseImpl::ContestExerciseImpl() : Exercise() {}

void ContestExerciseImpl::main() 
{
    int pos, bonus, malus;                  // La position, le nombre de places gagnées et le nombre de places perdues
    cin >> pos;                             // On note la position initiale
    
    for(int i=1; i<=42; i++) {              // A chaque kilomètre parcouru
        cin >> malus >> bonus;              // on relève les valeurs de bonus et malus
        pos += malus - bonus;               // et on ajoute la différence à la position "actuelle"
    }
        
    if(pos <= 100) {cout << 1000;}          // on gagne 1000euros si on est au plus 100ème
    else {
        if(pos <= 10000) {cout << 100;}     // on gagne 100euros si on est au plus 10000ème
        else {cout << "KO";}                // sinon rien
    }
}
