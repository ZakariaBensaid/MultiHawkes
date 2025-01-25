#ifndef HAWKES_H
#define HAWKES_H

#pragma once
#include <vector>
#include <utility>

using namespace std;

pair<vector<vector<int>>, vector<vector<vector<double>>>> SimulateHawkes(int nbSimulations, int nbThreads, const vector<double> mu, const vector<vector<double>> alpha, const vector<vector<double>> beta, double T);

#endif // HAWKES_H
