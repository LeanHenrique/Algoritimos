#ifndef DFS_H
#define DFS_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

// Função que realiza DFS no grafo original para preencher a pilha com a ordem 
// de finalização dos vértices.
void DfsOrder(
    const std::string& vertice, 
    const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
    std::unordered_set<std::string>& visitados, 
    std::stack<std::string>& pilha
);

// Função que realiza DFS no grafo transposto para identificar um componente 
// fortemente conexo.
void DfsTranspose(
    const std::string& vertice, 
    const std::unordered_map<std::string, std::vector<std::string>>& GrafoTransposto, 
    std::unordered_set<std::string>& visitados, 
    std::vector<std::string>& componente
);

bool DfsPatrulhamento(
    const std::string& atual, 
    const std::string& inicio, 
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& subgrafo, 
    std::vector<std::string>& ciclo);



#endif // DFS_H
