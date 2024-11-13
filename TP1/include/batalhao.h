// batalhao.h

#ifndef BATALHAO_H
#define BATALHAO_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>
#include <stack>


int Kosaraju(const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
             std::vector<std::vector<std::string>>& componentes);

std::string Batalhaoadicional(const std::string& inicio, 
                              const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
                              const std::vector<std::string>& componente);

#endif // BATALHAO_H
