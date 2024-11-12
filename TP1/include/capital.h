#ifndef CAPITAL_H
#define CAPITAL_H

#include <unordered_map>
#include <vector>
#include <string>

// Declarações das funções
std::pair<std::string, int> Bfs(const std::string& inicio, const std::unordered_map<std::string, std::vector<std::string>>& Grafo);
std::string Capital(const std::unordered_map<std::string, std::vector<std::string>>& Grafo);

#endif // CAPITAL_H
