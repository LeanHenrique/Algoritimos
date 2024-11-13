#ifndef BFS_H
#define BFS_H

#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>

// Função que realiza BFS a partir de um vértice de início e retorna o vértice
// mais distante do início e a sua distância. Retorna {"", -1} se o grafo não for conexo.
std::pair<std::string, int> BfsCapital(
    const std::string& inicio, 
    const std::unordered_map<std::string, std::vector<std::string>>& Grafo
);

// Função que realiza BFS a partir de um vértice de início e retorna um mapa com 
// as distâncias de todos os vértices alcançáveis a partir do vértice de início.
std::unordered_map<std::string, int> BfsBatalhao(
    const std::string& inicio, 
    const std::unordered_map<std::string, std::vector<std::string>>& Grafo
);

#endif // BFS_H
