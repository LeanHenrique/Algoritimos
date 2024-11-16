#ifndef PATRULHA_H
#define PATRULHA_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <stack>

// Função que cria subgrafos a partir dos componentes fortemente conexos
std::vector<std::unordered_map<std::string, std::vector<std::string>>> criaSubgrafos(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo,
    const std::vector<std::vector<std::string>>& componentes
);

// Função principal para resolver o Problema do Carteiro Chinês
void resolverCarteiroChines(const std::unordered_map<std::string, std::vector<std::string>>& Grafo,
                            const std::vector<std::vector<std::string>>& componentes,
                            const std::vector<std::string>& batalhoes);

// Função que encontra os vértices com graus de entrada e saída diferentes
std::vector<std::string> encontrarVerticesImpares(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo
);

// Função que encontra o menor caminho entre dois vértices
int menorCaminho(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo,
    const std::string& origem,
    const std::string& destino
);

// Função que emparelha vértices ímpares e torna o grafo Euleriano
void tornarEuleriano(
    std::unordered_map<std::string, std::vector<std::string>>& grafo,
    const std::vector<std::string>& verticesImpares
);

// Função que verifica se existe um ciclo euleriano a partir de um vértice origem
bool encontrarCicloEuleriano(
    const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
    std::string origem, 
    std::vector<std::string>& ciclo
);

#endif // PATRULHA_H
