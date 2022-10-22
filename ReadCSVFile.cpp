#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ReadCSVFile.h"

using namespace std;

// File reader
ReadCSVFile::ReadCSVFile(string filename){
    string row, col;
    // read a file
    ifstream csvfile(filename);
    // open file
    if (csvfile.is_open()){
        // read each row in the file
        while (getline(csvfile, row)){
            stringstream lineStream(row);
            vector<string> line;
            // read each column in the row (separated by comma)
            while (getline(lineStream,col,',')){
                // stored into the vector of string
                line.push_back(col);
            }
            // stored into the double vector
            dataframe.push_back(line);
        }
        // close file
        csvfile.close();
    }
    else{
        // informs user if the file not exists or
        // cannot open the file
        cout << "Cannot open the csv file" << endl;
    }
}

// a get function to return only values (type double)
// of the dataframe, the first row and column will be
// removed.
vector<vector<double>> ReadCSVFile::get_values(){
    vector<vector<double>> values;
    int num_row = dataframe.size();
    int num_col = dataframe[0].size();
    for(int row = 1; row < num_row; row++){
        vector<double> tempo_values;
        for(int col = 1; col < num_col; col++)
            tempo_values.push_back(stod(dataframe[row][col]));
        values.push_back(tempo_values);
    }
    return values;
}

// a get function to return a single value that matches the given
// row name (stock name) and column name (data)
double ReadCSVFile::get_value(string row_name, string col_name){
    int num_row = dataframe.size();
    int num_col = dataframe[0].size();
    for (int row = 1; row < num_row; row++){
        if (dataframe[row][0]==row_name){
            for (int col = 1; col < num_col; col++){
                if (dataframe[0][col]==col_name){
                    return stod(dataframe[row][col]);
                }
            }
        }
    }
    // Show this if no cells in the dataframe are found
    // matching the given name or data, then return 0.0
    cout << "Cannot find any matched cell:\n"
         << "check if the name <" << row_name
         << "> and data <" << col_name
         << "> exist."
         << endl;
    return 0.0;
}
