#ifndef PATRULHA_H
#define PATRULHA_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <stack>

// Função para verificar se um vértice está no componente
bool estaNoComponente(const std::vector<std::string>& componente, const std::string& vertice);

// Função para construir o subgrafo a partir do grafo original e o componente
std::unordered_map<std::string, std::vector<std::string>> construirSubgrafo(
    const std::unordered_map<std::string, std::vector<std::string>>& grafoOriginal,
    const std::vector<std::string>& componente
);

// Função para verificar se todos os vértices de um componente têm graus de entrada == saída
bool verificaGrauEuleriano(const std::unordered_map<std::string, std::vector<std::string>>& componente);

// Algoritmo de Hierholzer para encontrar ciclo euleriano em um grafo direcionado
std::vector<std::string> encontraCicloEuleriano(std::unordered_map<std::string, std::vector<std::string>>& componente, const std::string& inicio);

// Função para calcular ciclo euleriano para todos os componentes
std::vector<std::vector<std::string>> calculaCiclosEulerianosParaComponentes(
    const std::unordered_map<std::string, std::vector<std::string>>& grafoOriginal,
    const std::vector<std::vector<std::string>>& componentes
);

#endif //PATRULHA_H
