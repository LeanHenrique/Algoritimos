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

#endif // PATRULHA_H
