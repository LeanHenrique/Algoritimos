#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "bruteforce.h"
#include "dynamics.h"
#include "heuristic.h"


using namespace std;


int main() {
    char strategy; 
    int V, E; 
    cin >> strategy; 
    cin >> V >> E;   
    
    vector<string> cities; 
    unordered_map<string, unordered_map<string, int>> Graph; 
    
    // Leitura das estradas e construção do grafo
    for (int i = 0; i < E; i++) {
        string city1, city2;
        int weight;
        cin >> city1 >> city2 >> weight;
        
     Graph[city1][city2] = weight; 
     Graph[city2][city1] = weight;
        
        // Adiciona as cidades ao vetor de cidades
        unordered_set<string> citySet(cities.begin(), cities.end());
        if (citySet.find(city1) == citySet.end()) {
            cities.push_back(city1);
            citySet.insert(city1);
        }
        if (citySet.find(city2) == citySet.end()) {
            cities.push_back(city2);
            citySet.insert(city2);
        }
    }
    
    // Executa o algoritmo de acordo com a estratégia escolhida
    if (strategy == 'b') {
        auto result = tspBruteForce(cities, Graph);
        cout << result.first << endl; 
        for (const auto& city : result.second) {
            cout << city << " "; 
        }
        cout << endl;
    } 

    else if (strategy == 'd') {
        auto result = tspDynamicProgramming(cities, Graph);
        cout << result.first << endl; 
        for (const auto& city : result.second) {
            cout << city << " ";
        }
        cout << endl;
    }

    else if (strategy == 'g') {
        auto result = tspNearestNeighbor(cities, Graph);
        cout << result.first << endl; 
        for (const auto& city : result.second) {
            cout << city << " "; 
        }
        cout << endl;
    }
    
    return 0;
}
