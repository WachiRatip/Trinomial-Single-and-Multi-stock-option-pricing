#include <cmath>
#include "PathDependentOptions.h"


//function to compute arithmetic average of the array of prices
double ArAverage(double* Prices, int N){
    double sum = 0.0;
    for (int i = 0; i < N; i++){
        sum += *(Prices+i);
    }

    return sum/N;
}

//function to compute the discounted expected option price
//according to Trinomial model and the option type.
double PathDependentOptions::PriceByExpectation(TriPath Model){
    //The placeholders for the expected payoff.
    double optionPrice=0.0, prob, payoff;

    //Mutable path and prices.
    int N = Model.Get_N();
    int* path = new int[N];
    double* prices = new double[N];

    //Get the total number of paths
    int total = pow(3, N);

    //Iterate over the paths x from 0 to 2^{N}-1
    for (int x=0; x<total; x++){
        //Get the path corresponding to the given paths number
        Model.PathByNumber(x, path);
        //Get the price's scenario corresponding to the path
        Model.PriceByPath(path, prices);
        //Compute probability p corresponding to the path
        prob = Model.ProbabilityByPath(path);
        //Calculate the payoff
        payoff = Payoff(prices, N);
        //Calculate the expected value of the payoff: SUM(p_x*payoff_x)
        optionPrice += prob*payoff;
    }

    //Deallocate the memory
    delete[] path;
    delete[] prices;
    
    //Return the discounted expected payoff
    //which is E(payoff)/(1+R)^{N}
    return optionPrice/pow(1+Model.Get_r(), N);
}

//Payoff function for the fixed price Asian option
//return max{S(1)-Avg, S(2)-Avg, ..., S(N)-Avg, 0}
//when Avg is the arithmetic mean of the stock prices
double FixedPriceAsianOptions::Payoff(double *prices, int N){
    double max_price = 0.0;
    double avg = ArAverage(prices, N);
    double payoff;

    //find max value
    for (int i=0; i<N; i++){
        payoff = *(prices+i)-avg;
        if (payoff>max_price)
            max_price = payoff;
    }

    return max_price;
}

//Payoff function for the lookback option
//return max{S(N)-S(0), S(N)-S(1), ..., S(N)-S(N), 0.0}
//note: S(N)-S(N) = 0.
double LookbackOptions::Payoff(double *prices, int N){
    double max_price = prices[N-1] - S0;
    double payoff;

    //find max value
    for (int i=0; i<N; i++){
        payoff = prices[N-1] - prices[i];
        if (payoff>max_price)
            max_price = payoff;
    }

    return max_price;
}

//Payoff function for the knockout option
//if max{S(0), S(1), ..., S(N)}<=B,
//then payoff = max{ S(N)-K, 0 },
//otherwise payoff = 0.
double KnockoutOptions::Payoff(double *prices, int N){
    double max_price = S0;
    double price;

    //find max value
    for (int i=0; i<N; i++){
        price = *(prices+i);
        if (price > max_price)
            max_price = price;
    }

    //check if the max value exceeds specified price level
    if (max_price>B)
        return 0.0;
    else
        return fmax(prices[N-1]-K, 0.0);
}

//Payoff function for the classic Parisian option
//if the asset price exceeds the barrier level (B) for a
//predefined period of time (M), then the derivative expires
//worthless and return 0.0, otherwise return max{S(N)-K, 0.0}.
//if the price below the bar, the clock is reset.
double ClassicParisianOptions::Payoff(double *prices, int N){
   int count=0;
   double price;

   // check if S(t=0) >= B
   if (S0>=B){
       count++;
       if (count>M) return 0.0; //the condition met
   }

   // iterate over S(t) for each t=1,...,N.
   for (int i=0; i<N; i++){
        price = *(prices+i);
        // check if S(t) >= B
        if (price>=B){
            count++;
            if (count>M) return 0.0; //the condition met
        }
        else{
            // When dips down below the barrier,
            // the clock is reset.
            count=0;
        }
    }

    //the condition has never met return max{S(N)-K, 0.0}.
    return fmax(price-K, 0.0);
}
