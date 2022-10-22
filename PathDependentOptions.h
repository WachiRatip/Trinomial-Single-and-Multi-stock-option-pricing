/*
This header file was provided as a part of Individual Project 2
for the C++ Programming with Applications in Finance module.
*/

#ifndef PATHDEPENDENTOPTIONS_H_INCLUDED
#define PATHDEPENDENTOPTIONS_H_INCLUDED

#include "TriPath.h"

/*
    Class: PathDependentOptions
    This class is a pure virtual class which prices path-dependent options.
    Consist of the abstract function Payoff and PriceByExpectation to compute
    call option.
*/
class PathDependentOptions{

   public:
        virtual double Payoff(double *prices, int N){return 0.0;}
        double PriceByExpectation (TriPath Model);

};

/*
    Class: FixedPriceAsianOptions
    This is a subclass of PathDependentOptions. The use of this class is
    to define the payoff function for calculating the fixed price Asian
    option.
*/
class FixedPriceAsianOptions: virtual public PathDependentOptions{

    public:
        double Payoff(double *prices, int N);

};

/*
    Class: LookbackOptions
    This is a subclass of PathDependentOptions. The use of this class is
    to define the payoff function for calculating the Lookback option.

    The constructor receives an initial stock price (S0).
*/
class LookbackOptions: virtual public PathDependentOptions{

    private:
        double S0;  // initial stock price

    public:
        LookbackOptions(double S0_): S0(S0_) {};
        double Payoff(double *prices, int N);

};

/*
    Class: KnockoutOptions
    This is a subclass of PathDependentOptions. The use of this class is
    to define the payoff function for calculating the Knockout option.

    The constructor receives an initial stock price (S0), strick price (K)
    and barrier price level (B)
*/
class KnockoutOptions: virtual public PathDependentOptions{

    private:
        double S0;  // initial stock price
        double K;   // fixed strike price
        double B;   // barrier price level

    public:
        KnockoutOptions(double S0_, double K_, double B_): S0(S0_), K(K_), B(B_) {};
        double Payoff(double *prices, int N);

};

/*
    Class: ClassicParisianOptions
    This is a subclass of PathDependentOptions. The use of this class is
    to define the payoff function for calculating the classic Parisian
    option.

    The constructor receives an initial stock price (S0), strick price (K),
    barrier price level (B) and predefined period of time (M).
*/
class ClassicParisianOptions: virtual public PathDependentOptions{

    private:
        double S0;  // initial stock price
        double K;   // fixed strike price
        double B;   // barrier price level
        int M;      // predefined period of time

    public:
        ClassicParisianOptions(double S0_, double K_, double B_, int M_): S0(S0_), K(K_), B(B_), M(M_) {};
        double Payoff(double *prices, int N);

};


#endif // PATHDEPENDENTOPTIONS_H_INCLUDED
