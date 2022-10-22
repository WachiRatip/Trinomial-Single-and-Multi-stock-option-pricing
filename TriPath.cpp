#include <cmath>
#include "TriPath.h"

using namespace std;

//generates an array of path by number x ranged from 0 to (3^N)-1
// a 0 corresponds to the underlying asset going down in price
// a 1 corresponds to the asset keeping the same price
// a 2 corresponds to the asset going up in price
void TriPath::PathByNumber(int x, int *path){
    //To get the array path from the given x.
    //It is the same as converting x to its ternary (base 3) form.
    //in the path, e.g., (2,1,0) refers the price moved up
    //at step 1, remain the same at step 2 and then moved down at step 3.
    //Note: N is the time step.
    for (int i=0; i<N; i++){
        *(path+i) = x%3;
        x = x/3;
    }
}

//generates an array of prices along the path and
//writes them into the array prices of length N
void TriPath::PriceByPath(int *path, double *prices){
    int current_node, previous_node;
    for (int i=0; i<N; i++){
        current_node = *(path+i)-1;
        if (i==0){
            *(prices+i) = S( current_node );
            previous_node = current_node;
        }
        else{
            *(prices+i) = S( previous_node + current_node);
            previous_node = previous_node + current_node;
        }
    }
}

//calculate the probability of the path
double TriPath::ProbabilityByPath(int *path){
    // get the risk-neutral probability up, down and neutral.
    double prob_up = RiskNeutProb_up();
    double prob_down = RiskNeutProb_down();
    double prob_neutral = 1 - prob_up - prob_down;

    // count the number of times which the evolution of the stock price
    // increase, decrease or remain the same.
    int num_up = 0, num_down = 0, num_neutral = 0;
    for (int i=0; i<N; i++){
        if (*(path+i)==0)
            num_down++;
        else if (*(path+i)==1)
            num_neutral++;
        else
            num_up++;
    }

    //compute and return p_up^{n_up}*p_down^{n_down}*p_neutral^{n_neutral}
    return pow(prob_up, num_up)*pow(prob_down, num_down)*pow(prob_neutral, num_neutral);
}
