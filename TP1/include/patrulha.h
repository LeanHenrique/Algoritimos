#ifndef PATRULHA_H
#define PATRULHA_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <stack>

// Função para criar subgrafos a partir dos componentes
std::vector<std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>> criaSubgrafos(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo,
    const std::vector<std::vector<std::string>>& componentes);


void rodarDFSNosSubgrafos(
    std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
    const std::vector<std::vector<std::string>>& componentes,
    const std::vector<std::string>& batalhoes); 

bool modifiedDFS(
    const std::string& atual, 
    const std::string& inicio, 
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& subgrafo, 
    std::vector<std::string>& ciclo, 
    bool& todasArestasVisitadas,
    std::unordered_map<std::string, std::unordered_map<std::string, bool>>& arestasVisitadas);

    // Função para rodar o DFS até percorrer todas as arestas
void percorreSubgrafo(
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& subgrafo,
    std::string& origem,
    std::vector<std::string>& ciclo);

    void ordenarArestasPorPeso(std::vector<std::pair<std::string, int>>& vizinhos) ;

#endif // PATRULHA_H
