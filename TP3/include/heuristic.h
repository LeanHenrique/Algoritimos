#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

pair<int, vector<string>> tspNearestNeighbor(const vector<string>& cities, const unordered_map<string, unordered_map<string, int>>& Graph);

#endif // HEURISTIC_H
