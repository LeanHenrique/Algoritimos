#ifndef AUXILIARES_H
#define AUXILIARES_H

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

std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> criaSubgrafo(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo,
    const std::vector<std::string>& componente);

std::unordered_map<std::string, std::vector<std::string>> 
criaSubgrafoBatalhao(const std::unordered_map<std::string, std::vector<std::string>>& grafo,
const std::vector<std::string>& componente);    

#endif //AUXILIARES_H    