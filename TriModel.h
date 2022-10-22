/*
This header file was provided as a part of Individual Project 2
for the C++ Programming with Applications in Finance module.
*/

#ifndef TRIMODEL_H_INCLUDED
#define TRIMODEL_H_INCLUDED

/*
    Class: TriModel
    This class describes the possible evolution of a stock, whose initial value is S0.
    The evolution of a stock can increase, decrease or remain the same, according to the
    risk neutral probability up, down or neutral, respectively. These probabilities are
    defined according to sigma, r, nu, dt and dx.

    The constructor receives an initial stock price (S0), volatility (sigma) and interest rate (r).
*/

class TriModel{

    private:
        double S0;      // Initial stock price
        double sigma;   // Stock volatility
        double r;       // Continuously compounded interest rate
        double nu;      // Constant, used in calculations
        double dt;      // Time interval (time step size)
        double dx;      // Stock interval (stock step size)

    public:
        // Constructor to initialise data members
        TriModel(double S0_, double sigma_,double r_): S0(S0_), sigma(sigma_),r(r_){
            nu = r-sigma*sigma/2;
            dt = 0.0;
            dx = 0.0;
        }

        // member function to set values of dt and dx
        // T maturity of the option, N number of time steps
        void Set_dtdx(double T, int N);

        // calculate the risk neutual probability of going up
        double RiskNeutProb_up();

        // calculate the risk neutual probability of going down
        double RiskNeutProb_down();

        // calculate the stock price at time step n and node i
        double S(int i);

        // return the risk free interest rate R
        double Get_r() { return r;}

        // return time interval dt
        double Get_dt() { return dt;}

};

#endif // TRIMODEL_H_INCLUDED
