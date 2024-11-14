#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/patrulha.h"
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/dfs.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>

// Função para criar subgrafos a partir dos componentes
std::vector<std::unordered_map<std::string, std::vector<std::string>>> criaSubgrafos(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo,
    const std::vector<std::vector<std::string>>& componentes) {

    // Lista para armazenar cada subgrafo (um por componente)
    std::vector<std::unordered_map<std::string, std::vector<std::string>>> subgrafos;

    // Itera sobre cada componente
    for (const auto& regiao : componentes) {
        // Inicializa o subgrafo para este componente
        std::unordered_map<std::string, std::vector<std::string>> subgrafo;

        // Conjunto para verificar rapidamente se um vértice pertence à região
        std::unordered_set<std::string> regiaoSet(regiao.begin(), regiao.end());

        // Adiciona as arestas entre os vértices da região
        for (const auto& vertice : regiao) {
            bool verticeTemArestas = false;  // Flag para verificar se o vértice tem arestas na região
            for (const auto& vizinho : grafo.at(vertice)) {
                // Verifica se o vizinho pertence à região
                if (regiaoSet.find(vizinho) != regiaoSet.end()) {
                    subgrafo[vertice].push_back(vizinho);
                    verticeTemArestas = true;
                }
            }

            // Se o vértice não tiver arestas, ainda assim é adicionado ao subgrafo
            if (!verticeTemArestas) {
                subgrafo[vertice] = {};  // Adiciona o vértice com uma lista vazia de vizinhos
            }
        }

        // Adiciona o subgrafo à lista de subgrafos
        subgrafos.push_back(subgrafo);
    }
    
    return subgrafos;
}

// Função para verificar se todos os vértices têm grau de entrada e saída iguais
bool verificarGrausIguais(const std::unordered_map<std::string, std::vector<std::string>>& grafo) {
    std::unordered_map<std::string, int> grauEntrada, grauSaida;

    // Calcula o grau de entrada e saída de cada vértice
    for (const auto& par : grafo) {
        const auto& origem = par.first;
        grauSaida[origem] += par.second.size();
        for (const auto& destino : par.second) {
            grauEntrada[destino]++;
        }
    }

    // Verifica se o grau de entrada é igual ao de saída para todos os vértices
    for (const auto& par : grafo) {
        const std::string& vertice = par.first;
        if (grauEntrada[vertice] != grauSaida[vertice]) {
            return false;
        }
    }
    return true;
}

// Função para encontrar o ciclo Euleriano em um grafo direcionado
bool encontrarCicloEuleriano(const std::unordered_map<std::string, std::vector<std::string>>& grafo, std::string origem, std::vector<std::string>& ciclo) {
    // Caso especial: se o grafo tem apenas um vértice e nenhuma aresta, não há ciclo Euleriano
    if (grafo.size() == 1 && grafo.begin()->second.empty()) {
        return false;
    }

    // Verifica se todos os vértices têm grau de entrada e saída iguais
    if (!verificarGrausIguais(grafo)) {
        return false;
    }

    // Cópia temporária do grafo para manipulação durante a busca do ciclo
    std::unordered_map<std::string, std::vector<std::string>> grafoTemp = grafo;
    std::stack<std::string> pilha;
    pilha.push(origem);

    int totalArestas = 0;
    // Conta o total de arestas no grafo
    for (const auto& entrada : grafo) {
        totalArestas += entrada.second.size();
    }

    // Encontra o ciclo percorrendo todas as arestas
    while (!pilha.empty()) {
        std::string vertice = pilha.top();

        if (!grafoTemp[vertice].empty()) {
            std::string vizinho = grafoTemp[vertice].back();
            grafoTemp[vertice].pop_back();
            pilha.push(vizinho);
        } else {
            ciclo.push_back(vertice);
            pilha.pop();
        }
    }

    // Verifica se o ciclo inclui todas as arestas do grafo
    return ciclo.size() == static_cast<size_t>(totalArestas) + 1;
}

// Função principal para encontrar os ciclos de todos os subgrafos
void encontrarCiclosEmSubgrafos(const std::unordered_map<std::string, std::vector<std::string>>& Grafo,
                                const std::vector<std::vector<std::string>>& componentes,
                                const std::vector<std::string>& batalhoes) {
    
    // Cria os subgrafos com base nos componentes
    std::vector<std::unordered_map<std::string, std::vector<std::string>>> subgrafos = criaSubgrafos(Grafo, componentes);
    
    int totalCiclos = 0;
    std::vector<std::vector<std::string>> ciclos;

    // Para cada subgrafo, tenta encontrar um ciclo Euleriano
    for (size_t i = 0; i < subgrafos.size(); ++i) {
        const auto& subgrafo = subgrafos[i];
        std::vector<std::string> ciclo;
        std::string origem;

        // Encontra uma origem válida em batalhoes que também pertence ao subgrafo atual
        for (const auto& vertice : batalhoes) {
            if (subgrafo.find(vertice) != subgrafo.end()) {
                origem = vertice;
                break;
            }
        }

        // Prossegue se uma origem válida foi encontrada
        if (!origem.empty() && encontrarCicloEuleriano(subgrafo, origem, ciclo)) {
            totalCiclos++;
            // Remove o último vértice do ciclo, pois ele é o mesmo que o primeiro
            ciclo.pop_back();
            ciclos.push_back(ciclo);
        }
    }

    // Exibe a quantidade total de ciclos encontrados
    std::cout << totalCiclos << std::endl;
    
    // Exibe os caminhos dos ciclos encontrados
    for (const auto& ciclo : ciclos) {
        for (const auto& vertice : ciclo) {
            std::cout << vertice << " ";
        }
        std::cout << std::endl;
    }
}
