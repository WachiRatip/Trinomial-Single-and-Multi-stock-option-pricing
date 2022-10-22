/*
This header file was provided as a part of Individual Project 2
for the C++ Programming with Applications in Finance module.
*/

#include <cmath>
#include "TriModel.h"

using namespace std;

// Set dt and dx according to given
// time maturity (T), number of time steps (N)
void TriModel::Set_dtdx(double T, int N){
    dt = T/N;
    dx = sigma*sqrt(2*dt);
}

// Compute the risk neutral probability that
// the stock price increase
double TriModel::RiskNeutProb_up(){
    return ((sigma*sigma*dt + nu*nu*dt*dt)/dx/dx + nu*dt/dx)/2;
}

// Compute the risk neutral probability that
// the stock price decrease
double TriModel::RiskNeutProb_down(){
    return ((sigma*sigma*dt + nu*nu*dt*dt)/dx/dx - nu*dt/dx)/2;
}

// Compute the stock price at node i-th.
double TriModel::S(int i){
    return S0*exp(i*dx);
}
