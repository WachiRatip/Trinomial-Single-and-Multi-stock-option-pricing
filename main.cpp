#include <iostream>
#include "ReadCSVFile.h"
#include "TriPath.h"
#include "PathDependentOptions.h"

using namespace std;

int main()
{
    // Read the CSV file
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Read CSV file" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    string filename = "StockDataMar2022.csv";
    ReadCSVFile df(filename); // read csv file
    DisplayDoubleVector(df.get()); // display the content
    cout << endl;


    // Perform the Path-dependent options pricing
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Path-dependent options pricing" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    // Constants
    double T = 1; // time maturity of the option
    int N = 6;    // number of time steps
    // Variables
    double stock_price;     // stock price
    double interest_rate;   // interest rate (in decimal not percent)
    double volatility;      // volatility (in decimal not percent)
    double strike_price;    // strike price used in the knockout and Parisian options
    double barrier_level;   // barrier level used in the knockout and Parisian options
    int period_limit;       // period-limit used in the Parisian option
    double asian_option;    // placeholder for the fixed price Asian option
    double lookback_option; // placeholder for the lookback option
    double knockout_option; // placeholder for the knockout option
    double parisian_option; // placeholder for the Parisian option

    // Tesla stock
    stock_price = df.get_value("Tesla", "Price");
    interest_rate = df.get_value("Tesla", "R");
    volatility = df.get_value("Tesla", "sigma");
    strike_price = 130;
    barrier_level = 160;
    period_limit = 2;
    cout << "Tesla stock option::"
         << " S0=" << stock_price
         << ", r=" << interest_rate
         << ", sigma=" << volatility
         << ", T=" << T
         << ", N=" << N
         << ",\n" << "                    "
         << " K=" << strike_price
         << ", B=" << barrier_level
         << ", M=" << period_limit
         << endl;

    // construct the trinomial tree model
    TriPath tesla(stock_price, volatility, interest_rate, T, N);

    // construct the option pricers
    FixedPriceAsianOptions tesla_option1;
    LookbackOptions tesla_option2(stock_price);
    KnockoutOptions tesla_option3(stock_price, strike_price, barrier_level);
    ClassicParisianOptions tesla_option4(stock_price, strike_price, barrier_level, period_limit);

    // compute and  display the option prices
    asian_option = tesla_option1.PriceByExpectation(tesla);
    lookback_option = tesla_option2.PriceByExpectation(tesla);
    knockout_option = tesla_option3.PriceByExpectation(tesla);
    parisian_option = tesla_option4.PriceByExpectation(tesla);
    cout << "-- Fixed price Asian option: " << asian_option << endl;
    cout << "-- Lookback option: " << lookback_option << endl;
    cout << "-- Knockout option: " << knockout_option << endl;
    cout << "-- Parisian option: " << parisian_option << endl;
    cout << endl;

    // Ford stock
    stock_price = df.get_value("Ford", "Price");
    interest_rate = df.get_value("Ford", "R");
    volatility = df.get_value("Ford", "sigma");
    strike_price = 160;
    barrier_level = 200;
    period_limit = 2;
    cout << "Ford stock option::"
         << " S0=" << stock_price
         << ", r=" << interest_rate
         << ", sigma=" << volatility
         << ", T=" << T
         << ", N=" << N
         << ",\n" << "                   "
         << " K=" << strike_price
         << ", B=" << barrier_level
         << ", M=" << period_limit
         << endl;

    // construct the trinomial tree model
    TriPath ford(stock_price, volatility, interest_rate, T, N);

    // construct the option pricers
    FixedPriceAsianOptions ford_option1;
    LookbackOptions ford_option2(stock_price);
    KnockoutOptions ford_option3(stock_price, strike_price, barrier_level);
    ClassicParisianOptions ford_option4(stock_price, strike_price, barrier_level, period_limit);

    // compute and display the option prices
    asian_option = ford_option1.PriceByExpectation(ford);
    lookback_option = ford_option2.PriceByExpectation(ford);
    knockout_option = ford_option3.PriceByExpectation(ford);
    parisian_option = ford_option4.PriceByExpectation(ford);
    cout << "-- Fixed price Asian option: " << asian_option << endl;
    cout << "-- Lookback option: " << lookback_option << endl;
    cout << "-- Knockout option: " << knockout_option << endl;
    cout << "-- Parisian option: " << parisian_option << endl;

    return 0;
}
