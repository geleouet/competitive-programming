#include <iostream>
#include <limits>
#include <sstream>
#include "exercise.hpp"

ContestExerciseImpl::ContestExerciseImpl() : Exercise() {}

void ContestExerciseImpl::main() 
{
    int ARs = 0; int poids = 0; int n = 1;      // Au début on a fait 0 aller-retour, le poids sur le monte-charge est nulle et on s'occupe du carton n°1
    int N, p;                                   // Le nombre total de cartons et le poids du carton "du moment" 
    cin >> N;                                   // On récupère le nombre total de cartons

    while(n <= N) {                             // Tant qu'il reste des cartons
        cin >> p;                               // on récupère le poids du carton "du moment"

        if(p <= 100-poids) {                    // Si on ne dépasse pas les 100kg avec le nouveau carton
            poids += p;                         // on l'ajoute au monte-charge
        }
        else {                                  // Sinon
            ARs++;                              // on fait un aller-retour avec le monte-charge
            poids = p;                          // et quand le monte-charge revient on met le carton dessus
        }
        n++;                                    // Puis on s'occupe du carton suivant
    }
    ARs++;                                      // Pour finir il faut tenir compte du dernier-aller retour, celui avec le dernier carton (n=N)
    cout << ARs;
}
