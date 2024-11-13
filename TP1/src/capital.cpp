#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/capital.h"
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/bfs.h"
#include <queue>
#include <iostream>





std::string Capital(const std::unordered_map<std::string, std::vector<std::string>>& Grafo){
    // Mapa para armazenar os resultados de cada BFS
    std::unordered_map<std::string, std::pair<std::string, int>> resultados;
   for (const auto& [vertice, _] : Grafo) {
        resultados[vertice] = BfsCapital(vertice, Grafo);
    }
    // Variáveis para armazenar o vértice com a maior distância
    std::string verticeMenorDistancia;
    int menorDistancia = 100000;  // Inicializa com valor negativo para garantir que qualquer distância será maior.

    // Itera sobre os resultados e encontra o vértice com a maior distância
    for (const auto& [vertice, par] : resultados) {
        if (par.second < menorDistancia && par.second >=0) {
            menorDistancia = par.second;
            verticeMenorDistancia = vertice;
        }
    }

    return verticeMenorDistancia;  // Retorna o vértice com a maior distância
}