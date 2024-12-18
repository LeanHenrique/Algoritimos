#ifndef BFS_H
#define BFS_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

// Função para realizar BFS em um grafo
void bfs(const std::unordered_map<int, std::vector<std::pair<int, int>>>& Graph, int start);

#endif // BFS_H
