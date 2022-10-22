/*
This header file was provided as a part of Individual Project 2
for the C++ Programming with Applications in Finance module.
*/

#ifndef TRIPATH_H_INCLUDED
#define TRIPATH_H_INCLUDED

#include "TriModel.h"

/*
    Class: TriPath
    This class is a subclass of TriModel. The use of this class is to encode
    all possible paths in a trinomial tree, their associated prices, and their associated probabilities.

    The constructor receives an initial stock price (S0), volatility (sigma), interest rate (r),
    time maturity of the option (T) and number of time steps (N)
*/
class TriPath : public TriModel{

    private:
        double T;   // time maturity of the option
        int N;      // number of time steps

    public:
        // constructor
        TriPath(double S0_, double sigma_, double r_, double T_, int N_): TriModel(S0_,sigma_,r_), T(T_), N(N_){
            Set_dtdx(T_, N_);
        }
        // function to generate path by the given number between 0 and 3^{N}-1
        void PathByNumber(int x, int *path);
        // function to generate an array of prices along the path
        void PriceByPath(int *path, double *prices);
        // function to calculate the probability of the path
        double ProbabilityByPath(int *path);
        // get function to return time maturity of the option (T)
        double Get_T(){return T;}
        // get function to return number of time steps (N)
        int Get_N(){return N;}

};


#endif // TRIPATH_H_INCLUDED
