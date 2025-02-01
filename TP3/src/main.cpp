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
    char strategy; // Estratégia escolhida pelo usuário
    int V, E; // Número de cidades e estradas
    
    cin >> strategy; // Lendo a estratégia ('b' para força bruta, 'd' para programação dinâmica, 'g' para Nearest Neighbor)
    cin >> V >> E;   // Lendo número de cidades e estradas
    
    vector<string> cities; // Lista de cidades únicas
    unordered_map<string, unordered_map<string, int>> adjMatrix; // Matriz de adjacência
    
    // Leitura das estradas
    for (int i = 0; i < E; i++) {
        string city1, city2;
        int weight;
        cin >> city1 >> city2 >> weight;
        
        adjMatrix[city1][city2] = weight; // Grafo completo, não precisa verificar existência
        adjMatrix[city2][city1] = weight;
        
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
    
    // Se a estratégia escolhida for força bruta, executa o TSP
    if (strategy == 'b') {
        auto result = tspBruteForce(cities, adjMatrix);
        cout << result.first << endl; // Custo total da melhor rota
        for (const auto& city : result.second) {
            cout << city << " "; // Sequência da melhor rota
        }
        cout << endl;
    } 
    // Se a estratégia escolhida for programação dinâmica, executa o TSP
    else if (strategy == 'd') {
        auto result = tspDynamicProgramming(cities, adjMatrix);
        cout << result.first << endl; // Custo total da melhor rota
        for (const auto& city : result.second) {
            cout << city << " "; // Sequência da melhor rota
        }
        cout << endl;
    }
    // Se a estratégia escolhida for Nearest Neighbor, executa o TSP
    else if (strategy == 'g') {
        auto result = tspNearestNeighbor(cities, adjMatrix);
        cout << result.first << endl; // Custo total da melhor rota
        for (const auto& city : result.second) {
            cout << city << " "; // Sequência da melhor rota
        }
        cout << endl;
    }
    
    return 0;
}
