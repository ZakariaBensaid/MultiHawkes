#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <thread>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <tuple>

using namespace std::chrono;
using namespace std;
namespace py = pybind11;

// Function to generate a uniform random number between 0 and 1
static double uniform() {
    return rand() / static_cast<double>(RAND_MAX);
}

// Function to generate an exponential random number with rate parameter lambda
static double exponential(double lambda) {
    return -log(uniform()) / lambda;
}

class HawkesProcess {
public:
    HawkesProcess(const vector<double>& mu, const vector<vector<double>>& alpha, const vector<vector<double>>& beta, double T)
        : mu(mu), alpha(alpha), beta(beta), T(T), M(mu.size()), s(0), nm(M, 0), Tm(M) {
        srand(time(nullptr));  
    }

    void simulate() {
        while (s < T) {
            double lambda_bar = calculateLambdaBar();
            double w = exponential(lambda_bar);
            s += w;
            double D = uniform();
            if (D * lambda_bar <= calculateLambdaBar()) {
                int k = determineDimension(D * lambda_bar);
                updateProcess(k);
            }
        }
    }

    void printResults() const {
        for (int m = 0; m < M; ++m) {
            cout << "T" << m + 1 << " = {";
            for (auto t : Tm[m]) {
                cout << t << " ";
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
        s = 0;
        nm.assign(M, 0);
        Tm.assign(M, {});
    }
private:
    vector<double> mu;
    vector<vector<double>> alpha;
    vector<vector<double>> beta;
    double T;
    int M;
    double s;
    vector<int> nm;
    vector<vector<double>> Tm;

    double calculateLambdaBar() {
        double lambda_bar = 0;
        for (int m = 0; m < M; ++m) {
            double lambda_m = mu[m];
            for (int n = 0; n < M; ++n) {
                for (auto tau : Tm[n]) {
                    lambda_m += alpha[m][n] * exp(-beta[m][n] * (s - tau));
                }
            }
            lambda_bar += lambda_m;
        }
        return lambda_bar;
    }


    int determineDimension(double threshold) {
        double cumulative_sum = 0;
        for (int k = 0; k < M; ++k) {
            cumulative_sum += mu[k];
            for (int n = 0; n < M; ++n) {
                for (auto tau : Tm[n]) {
                    cumulative_sum += alpha[k][n] * exp(-beta[k][n] * (s - tau));
                }
            }
            if (threshold <= cumulative_sum) {
                return k;
            }
        }
        return M - 1; // Should not reach here if threshold is correctly calculated
    }

    void updateProcess(int k) {
        nm[k]++;
        Tm[k].push_back(s);
    }
};

// Function to run simulations in parallel
static pair<vector<vector<int>>, vector<vector<vector<double>>>>  SimulateHawkes(int nbSimulations, int nbThreads, const vector<double> mu, const vector<vector<double>> alpha, const vector<vector<double>> beta, double T) {
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
    for (int i = 0; i < nbSimulations; ++i) {
        std::cout << "Simulation " << i + 1 << ": ";
        for (int j = 0; j < mu.size(); ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    };
    return {result, jumpTimes};
}

PYBIND11_MODULE(hawkes, m) {
    m.def("simulate_hawkes", &SimulateHawkes, "Function to simulate Hawkes processes",
        py::arg("nbSimulations"), py::arg("nbThreads"), py::arg("mu"), py::arg("alpha"), py::arg("beta"), py::arg("T"));
}



