#ifndef DYNAMICS_H
#define DYNAMICS_H

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// Declaração da função
pair<int, vector<string>> tspDynamicProgramming(const vector<string>& cities, const unordered_map<string, unordered_map<string, int>>& adjMatrix);

#endif // DYNAMICS_H
