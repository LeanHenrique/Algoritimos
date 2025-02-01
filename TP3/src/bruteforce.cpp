#include <iostream>
#include "bruteforce.h"

using namespace std;

// Função auxiliar para gerar permutações manualmente
void permute(vector<string>& arr, int l, int r, vector<vector<string>>& permutations) {
    if (l == r) {
        permutations.push_back(arr);
        return;
    }
    for (int i = l; i <= r; i++) {
        swap(arr[l], arr[i]);
        permute(arr, l + 1, r, permutations);
        swap(arr[l], arr[i]); // Volta ao estado original
    }
}

// Função que resolve o problema do Caixeiro Viajante por força bruta
pair<int, vector<string>> tspBruteForce(const vector<string>& cities, const unordered_map<string, unordered_map<string, int>>& adjMatrix) {
    vector<vector<string>> permutations;
    vector<string> perm = cities;
    permute(perm, 0, static_cast<int>(perm.size()) - 1, permutations);

    
    int minCost = 1e9; // Valor alto arbitrário para representar infinito
    vector<string> bestRoute;
    
    // Testa todas as permutações possíveis das cidades
    for (const auto& perm : permutations) {
        int cost = 0;
        for (size_t i = 0; i < perm.size() - 1; i++) {
            cost += adjMatrix.at(perm[i]).at(perm[i + 1]);
        }
        // Adiciona o custo de retornar à cidade inicial
        cost += adjMatrix.at(perm.back()).at(perm.front());
        
        // Se encontrou um custo menor, armazena a melhor rota
        if (cost < minCost) {
            minCost = cost;
            bestRoute = perm;
        }
    }
    
    return {minCost, bestRoute}; // Retorna o menor custo e a melhor rota encontrada
}
