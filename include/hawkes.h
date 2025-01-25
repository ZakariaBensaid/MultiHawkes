#include <iostream>
#include <vector>

using namespace std;

// needed function for main.cpp
static pair<vector<vector<int>>, vector<vector<vector<double>>>>  SimulateHawkes(int nbSimulations, int nbThreads, const vector<double> mu, const vector<vector<double>> alpha, const vector<vector<double>> beta, double T) {
    vector<vector<int>> result(nbSimulations, vector<int>(mu.size()));
    vector<vector<vector<double>>> jumpTimes(nbSimulations, vector<vector<double>>(mu.size()));
        };
