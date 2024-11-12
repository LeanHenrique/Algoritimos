// batalhao.h

#ifndef BATALHAO_H
#define BATALHAO_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
#include <stack>

// Declare as funções para uso em batalhao.h

void DfsOrder(const std::string& vertice, 
              const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
              std::unordered_set<std::string>& visitados, 
              std::stack<std::string>& pilha);

void DfsTranspose(const std::string& vertice, 
                  const std::unordered_map<std::string, std::vector<std::string>>& GrafoTransposto, 
                  std::unordered_set<std::string>& visitados, 
                  std::vector<std::string>& componente);

int Kosaraju(const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
             std::vector<std::vector<std::string>>& componentes);

std::unordered_map<std::string, int> BfsBatalhao(const std::string& inicio, 
                                                 const std::unordered_map<std::string, std::vector<std::string>>& Grafo);

std::string Batalhaoadicional(const std::string& inicio, 
                              const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
                              const std::vector<std::string>& componente);

#endif // BATALHAO_H
