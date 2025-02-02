#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

pair<int, vector<string>> tspBruteForce(const vector<string>& cities, const unordered_map<string, unordered_map<string, int>>& Graph);
void permute(vector<string>& arr, int l, int r, vector<vector<string>>& permutations);

#endif // BRUTEFORCE_H
