#include "hawkes.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>
#include <tuple>


using namespace std::chrono;
using namespace std;

// Function to generate a uniform random number between 0 and 1
static double uniform() {
    return rand() / static_cast<double>(RAND_MAX);
}

// Function to generate an exponential random number with rate parameter lambda (inverse function method)
static double exponential(double lambda) {
    return -log(uniform()) / lambda;
}

class HawkesProcess {
public:
    HawkesProcess(const vector<double>& mu, const vector<vector<double>>& alpha, const vector<vector<double>>& beta, double T)
        : mu(mu), alpha(alpha), beta(beta), T(T), M(mu.size()), t(0), nm(M, 0), Tm(M), cumLambda(M, 0.0) {
        srand(time(nullptr));  
    }
    // Ogata's thinning method
    void simulate() {
        // Time loop
        while (t < T) {
            // Track intensities
            cumLambda.assign(M, 0.0);
            // Compute intensity at time t
            double lambdaOld = calculateLambda(t, false);
            // Generate next "potential" jump time
            double jumpTime = exponential(lambdaOld);
            t += jumpTime;
            if (t > T) {
                break; 
            }
            // Compute the intensity at time t+jump (Phi decreasing -> smaller)
            double lambdaNew = calculateLambda(t, true);
            // Accept the jump time with probability lambdaNew/lambdaOld
            double U = lambdaOld * uniform();
            if (U >= lambdaOld - lambdaNew) {
                int k = determineDimension(U, lambdaOld);
                updateProcess(k);
            }
        }
    }

    void printResults() const {
        for (int m = 0; m < M; ++m) {
            cout << "T" << m + 1 << " = {";
            for (auto jumpTime : Tm[m]) {
                cout << jumpTime << " ";
            }
            cout << "}" << endl;
        }
    }

    vector <int> jumps() {
        vector <int> n(M);
        for (int m = 0; m < M; ++m) {
            n[m] = Tm[m].size();
        }
        return n;
    }

    vector <vector<double>> jumpTimes() {
        return Tm;
    }

    void reset() {
        // Clear internal state or data structures
        t = 0;
        nm.assign(M, 0);
        Tm.assign(M, {});
    }
private:
    vector<double> mu;
    vector<vector<double>> alpha;
    vector<vector<double>> beta;
    double T;
    int M;
    double t;
    vector<int> nm;
    vector<vector<double>> Tm;
    vector<double> cumLambda;

    // Compute intensity at time s (discrete convolution)
    double calculateLambda(double s, bool track) {
        double lambda = 0;
        for (int k = 0; k < M; ++k) {
            double lambda_k = mu[k];
            for (int n = 0; n < M; ++n) {
                for (auto tau : Tm[n]) {
                    lambda_k += alpha[k][n] * exp(-beta[k][n] * (s - tau));
                }
            }
            lambda += lambda_k;
            if (track){
                cumLambda[k] = lambda;
                }
        }
        return lambda;
    }

    // Determine first dimension where the jump is accepted
    int determineDimension(double threshold, double lambdaOld) {
        for (int k = 0; k < M; ++k) {
            if (threshold >= lambdaOld - cumLambda[k]) {
                return k;
            }
        }
        return M - 1; 
    }

    // Add new jump and new jump time
    void updateProcess(int k) {
        nm[k]++;
        Tm[k].push_back(t);
    }
};

// Function to run simulations in parallel
pair<vector<vector<int>>, vector<vector<vector<double>>>>  SimulateHawkes(int nbSimulations, int nbThreads, const vector<double> mu, const vector<vector<double>> alpha, const vector<vector<double>> beta, double T, bool logSimulations) {
    vector<vector<int>> result(nbSimulations, vector<int>(mu.size()));
    vector<vector<vector<double>>> jumpTimes(nbSimulations, vector<vector<double>>(mu.size()));
    auto simulateThread = [&](int start, int end) {
        srand(time(nullptr) + hash<thread::id>{}(this_thread::get_id()));
        // Create and simulate the Hawkes process
        HawkesProcess  hawkes(mu, alpha, beta, T);
        for (int i = start; i < end; ++i) {
            hawkes.reset();
            hawkes.simulate();
            vector <int> N = hawkes.jumps();
            //hawkes.printResults();
            result[i] = N;
            jumpTimes[i] = hawkes.jumpTimes();
        }
        };

    // Divide the work among threads
    int simulationsPerThread = nbSimulations / nbThreads;
    vector<std::thread> threads;
    for (int i = 0; i < nbThreads; ++i) {
        int start = i * simulationsPerThread;
        int end = (i == nbThreads - 1) ? nbSimulations : (i + 1) * simulationsPerThread;
        threads.emplace_back(simulateThread, start, end);
    };

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    };

    // Output the results
    if (logSimulations){for (int i = 0; i < nbSimulations; ++i) {
        std::cout << "Simulation " << i + 1 << ": ";
        for (int j = 0; j < mu.size(); ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
    };
    

    return {result, jumpTimes};
}





