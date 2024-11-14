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

// Função principal para encontrar os ciclos em todos os subgrafos
void encontrarCiclosEmSubgrafos(
    const std::unordered_map<std::string, std::vector<std::string>>& Grafo,
    const std::vector<std::vector<std::string>>& componentes,
    const std::vector<std::string>& batalhoes
);

// Função que verifica se existe um ciclo euleriano a partir de um vértice origem
bool encontrarCicloEuleriano(
    const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
    std::string origem, 
    std::vector<std::string>& ciclo
);

// Função que verifica se todos os vértices têm graus iguais (necessário para ciclo euleriano)
bool verificarGrausIguais(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo
);

#endif // PATRULHA_H
