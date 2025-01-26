#include "hawkes.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main() {
    using namespace std;
    using namespace std::chrono;

    // Set the parameters of the Hawkes process
    double T = 2;
    int d = 10;
    int nbThreads = 1;
    int nbSimulations = 10000;

    // mu
    vector<double> mu = {5.0, 1.5, 0.01, 0.1, 6.8, 2.0, 0.3, 0.2, 2.5, 0.01};

    // alpha
    vector<vector<double>> alpha = {
        {0.5, 0.1, 3.0, 2.0, 0.4, 2.4, 0.1, 1.5, 0.1, 0.1},
        {0.2, 0.6, 3.0, 0.1, 0.2, 0.1, 0.7, 1.2, 0.1, 0.5},
        {3.5, 3.0, 4.0, 3.0, 0.1, 2.0, 0.2, 1.3, 0.1, 2.0},
        {0.1, 0.2, 0.2, 0.5, 0.1, 0.1, 0.1, 0.2, 0.1, 2.0},
        {0.3, 0.1, 1.1, 1.0, 0.6, 0.8, 0.1, 1.5, 0.1, 0.1},
        {0.1, 0.2, 0.1, 0.1, 0.1, 0.4, 0.2, 0.1, 0.1, 3.0},
        {0.1, 0.2, 2.0, 3.0, 0.5, 0.1, 0.3, 0.1, 0.5, 0.1},
        {3.0, 0.1, 0.3, 0.2, 0.4, 0.1, 0.1, 0.3, 0.6, 0.1},
        {0.1, 0.1, 0.1, 2.3, 0.1, 0.1, 3.0, 0.1, 0.1, 0.1},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0}
    };

    // beta 
    vector<vector<double>> beta = {
        {10.0, 10.0, 10.0, 15.0, 8.0, 10.0, 1.0, 10.0, 10.0, 10.0},
        {9.0, 12.0, 15.0, 8.0, 10.0, 11.0, 10.0, 6.0, 10.0, 10.0},
        {10.0, 11.0, 12.0, 9.0, 13.0, 14.0, 8.0, 4.0, 10.0, 10.0},
        {2.0, 10.0, 5.0, 6.0, 9.0, 3.0, 2.0, 6.0, 10.0, 10.0},
        {1.0, 10.0, 4.0, 3.0, 10.0, 2.0, 3.0, 4.0, 10.0, 10.0},
        {9.0, 14.0, 15.0, 6.0, 12.0, 10.0, 13.0, 1.0, 10.0, 10.0},
        {8.0, 13.0, 16.0, 7.0, 10.0, 12.0, 11.0, 1.0, 10.0, 10.0},
        {9.0, 12.0, 17.0, 8.0, 11.0, 13.0, 12.0, 1.0, 10.0, 10.0},
        {10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0},
        {10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0}
    };

    // Seed the random number generator 
    srand(static_cast<unsigned int>(time(0)));

    // Start timing 
    auto start_time = high_resolution_clock::now();

    pair<vector<vector<int>>, vector<vector<vector<double>>>> result = SimulateHawkes(nbSimulations, nbThreads, mu, alpha, beta, T);

    // Stop timing
    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;

    // results
    cout << "Simulation completed in " << elapsed.count() << " seconds." << endl;
};