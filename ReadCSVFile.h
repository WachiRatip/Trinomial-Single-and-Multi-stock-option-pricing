#ifndef READCSVFILE_H_INCLUDED
#define READCSVFILE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// A function to display the contents of any double vector.
template<typename Type> void DisplayDoubleVector(vector<vector<Type>> dataframe){
    int num_row = dataframe.size();
    int num_col = dataframe[0].size();
    for(int row = 0; row < num_row; row++){
        for(int col = 0; col < num_col; col++)
            cout << dataframe[row][col] << " "; // display each cell
        cout << endl;
    }
}

// A class to read a csv (comma-separated values) file into a double vector.
class ReadCSVFile{
    private:
        // double vector to store data in the csv file.
        vector<vector<string>> dataframe;

    public:
        // constructor receives filename
        ReadCSVFile(string filename);
        // get function to return the dataframe
        vector<vector<string>> get() {return dataframe;}
        // get function to return only the values in the dataframe,
        // the header (1st row) and the index (1st column) will be
        // removed.
        vector<vector<double>> get_values();
        // get function to return a value in the dataframe
        // corresponds to a given stock name and column data
        double get_value(string row_name, string col_name);
};

#endif // READCSVFILE_H_INCLUDED
