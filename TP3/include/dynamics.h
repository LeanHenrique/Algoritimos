#ifndef DYNAMICS_H
#define DYNAMICS_H

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;


pair<int, vector<string>> tspDynamicProgramming(const vector<string>& cities, const unordered_map<string, unordered_map<string, int>>& Graph);

#endif // DYNAMICS_H
