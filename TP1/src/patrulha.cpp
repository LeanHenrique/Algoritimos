#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/patrulha.h"
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/dfs.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <queue>

// Função para criar subgrafos a partir dos componentes
std::vector<std::unordered_map<std::string, std::vector<std::string>>> criaSubgrafos(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo,
    const std::vector<std::vector<std::string>>& componentes) {

    std::cout << "Criando subgrafos..." << std::endl;
    
    // Lista para armazenar cada subgrafo (um por componente)
    std::vector<std::unordered_map<std::string, std::vector<std::string>>> subgrafos;

    // Itera sobre cada componente
    for (const auto& regiao : componentes) {
        // Inicializa o subgrafo para este componente
        std::unordered_map<std::string, std::vector<std::string>> subgrafo;

        // Conjunto para verificar rapidamente se um vértice pertence à região
        std::unordered_set<std::string> regiaoSet(regiao.begin(), regiao.end());

        std::cout << "Componente: ";
        for (const auto& vertice : regiao) {
            std::cout << vertice << " ";
        }
        std::cout << std::endl;

        // Adiciona as arestas entre os vértices da região
        for (const auto& vertice : regiao) {
            bool verticeTemArestas = false;  // Flag para verificar se o vértice tem arestas na região
            for (const auto& vizinho : grafo.at(vertice)) {
                // Verifica se o vizinho pertence à região
                if (regiaoSet.find(vizinho) != regiaoSet.end()) {
                    subgrafo[vertice].push_back(vizinho);
                    verticeTemArestas = true;
                    std::cout << "Aresta encontrada: " << vertice << " -> " << vizinho << std::endl;
                }
            }

            // Se o vértice não tiver arestas, ainda assim é adicionado ao subgrafo
            if (!verticeTemArestas) {
                subgrafo[vertice] = {};  // Adiciona o vértice com uma lista vazia de vizinhos
                std::cout << "Vértice sem arestas: " << vertice << std::endl;
            }
        }

        // Adiciona o subgrafo à lista de subgrafos
        subgrafos.push_back(subgrafo);
    }
    
    return subgrafos;
}


// Função para verificar se todos os vértices têm grau de entrada e saída iguais
bool verificarGrausIguais(const std::unordered_map<std::string, std::vector<std::string>>& grafo) {
    std::cout << "Verificando se todos os vértices têm grau de entrada e saída iguais..." << std::endl;
    
    std::unordered_map<std::string, size_t> grauEntrada, grauSaida;

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
        std::cout << "Vértice: " << vertice << " - Grau Entrada: " << grauEntrada[vertice]
                  << " - Grau Saída: " << grauSaida[vertice] << std::endl;
        if (grauEntrada[vertice] != grauSaida[vertice]) {
            std::cout << "Erro: Grau de entrada e saída diferentes para o vértice " << vertice << std::endl;
            return false;
        }
    }
    return true;
}

// Função para encontrar o ciclo Euleriano em um grafo direcionado
bool encontrarCicloEuleriano(const std::unordered_map<std::string, std::vector<std::string>>& grafo, std::string origem, std::vector<std::string>& ciclo) {
    std::cout << "Buscando ciclo euleriano a partir de: " << origem << std::endl;

    // Caso especial: se o grafo tem apenas um vértice e nenhuma aresta, não há ciclo Euleriano
    if (grafo.size() == 1 && grafo.begin()->second.empty()) {
        std::cout << "Grafo com apenas um vértice e sem arestas. Sem ciclo Euleriano." << std::endl;
        return false;
    }

    // Verifica se todos os vértices têm grau de entrada e saída iguais
    if (!verificarGrausIguais(grafo)) {
        std::cout << "Não é possível encontrar ciclo Euleriano: graus de entrada e saída não são iguais para todos os vértices." << std::endl;
        return false;
    }

    // Cópia temporária do grafo para manipulação durante a busca do ciclo
    std::unordered_map<std::string, std::vector<std::string>> grafoTemp = grafo;
    std::stack<std::string> pilha;
    pilha.push(origem);

    size_t totalArestas = 0;
    // Conta o total de arestas no grafo
    for (const auto& entrada : grafo) {
        totalArestas += entrada.second.size();
    }

    std::cout << "Total de arestas no grafo: " << totalArestas << std::endl;

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
    std::cout << "Tamanho do ciclo encontrado: " << ciclo.size() << " (Esperado: " << totalArestas + 1 << ")" << std::endl;
    return ciclo.size() == static_cast<size_t>(totalArestas) + 1;
}


// Função para encontrar vértices de grau ímpar
std::vector<std::string> encontrarVerticesImpares(const std::unordered_map<std::string, std::vector<std::string>>& grafo) {
    std::unordered_map<std::string, size_t> grauEntrada, grauSaida;
    for (const auto& [origem, destinos] : grafo) {
        grauSaida[origem] += destinos.size();
        for (const auto& destino : destinos) {
            grauEntrada[destino]++;
        }
    }

    std::vector<std::string> impares;
    for (const auto& [vertice, _] : grafo) {
        if (grauEntrada[vertice] != grauSaida[vertice]) {
            impares.push_back(vertice);
        }
    }
    return impares;
}


// Implementação manual de BFS para calcular menor caminho
int menorCaminho(const std::string& origem, const std::string& destino,
                 const std::unordered_map<std::string, std::vector<std::string>>& grafo) {
    std::unordered_map<std::string, int> distancias;
    std::queue<std::string> fila;
    fila.push(origem);
    distancias[origem] = 0;

    while (!fila.empty()) {
        std::string atual = fila.front();
        fila.pop();

        for (const auto& vizinho : grafo.at(atual)) {
            if (distancias.find(vizinho) == distancias.end()) {
                distancias[vizinho] = distancias[atual] + 1;
                fila.push(vizinho);
                if (vizinho == destino) {
                    return distancias[vizinho];
                }
            }
        }
    }

    return 1000000000;  // Retorna um valor muito grande caso não haja caminho
}

// Implementação manual de Bubble Sort para ordenar pares
void ordenarCaminhos(std::vector<std::tuple<int, std::string, std::string>>& caminhos) {
    bool trocado;
    do {
        trocado = false;
        for (size_t i = 0; i < caminhos.size() - 1; ++i) {
            if (std::get<0>(caminhos[i]) > std::get<0>(caminhos[i + 1])) {
                std::swap(caminhos[i], caminhos[i + 1]);
                trocado = true;
            }
        }
    } while (trocado);
}

void tornarEuleriano(std::unordered_map<std::string, std::vector<std::string>>& grafo, const std::vector<std::string>& impares) {
    // Calcula todos os pares de vértices ímpares e seus menores caminhos
    std::vector<std::tuple<int, std::string, std::string>> caminhos;
    for (size_t i = 0; i < impares.size(); ++i) {
        for (size_t j = i + 1; j < impares.size(); ++j) {
            int custo = menorCaminho(impares[i], impares[j], grafo);
            caminhos.push_back({custo, impares[i], impares[j]});
        }
    }

    // Ordena os pares por menor custo (usando Bubble Sort)
    ordenarCaminhos(caminhos);

    // Calcula os graus de entrada e saída de cada vértice
    std::unordered_map<std::string, size_t> grauEntrada, grauSaida;
    for (const auto& par : grafo) {
        const auto& origem = par.first;
        grauSaida[origem] += par.second.size();
        for (const auto& destino : par.second) {
            grauEntrada[destino]++;
        }
    }

    // Emparelha os vértices de grau ímpar
    std::unordered_set<std::string> usados;
    for (const auto& [custo, u, v] : caminhos) {
        // Verifica se ambos os vértices têm grau ímpar e não foram usados ainda
        if (usados.find(u) == usados.end() && usados.find(v) == usados.end()) {
            // Balanceia os graus de entrada e saída antes de adicionar a aresta
            if (grauSaida[u] < grauEntrada[u]) {
                // Se o vértice u tem mais grau de entrada, adiciona uma aresta de saída
                grafo[u].push_back(v);
                std::cout << "Adicionando aresta de " << u << " -> " << v << std::endl;
            } else {
                // Se o vértice u tem mais grau de saída, adiciona uma aresta de entrada
                grafo[v].push_back(u);
                std::cout << "Adicionando aresta de " << v << " -> " << u << std::endl;
            }

            // Marca os vértices como usados
            usados.insert(u);
            usados.insert(v);
        }
    }
}


// Função principal para resolver o Problema do Carteiro Chinês
void resolverCarteiroChines(const std::unordered_map<std::string, std::vector<std::string>>& Grafo,
                            const std::vector<std::vector<std::string>>& componentes,
                            const std::vector<std::string>& batalhoes) {
    // Cria os subgrafos
    std::vector<std::unordered_map<std::string, std::vector<std::string>>> subgrafos = criaSubgrafos(Grafo, componentes);

    int totalCiclos = 0;
    std::vector<std::vector<std::string>> ciclos;

    std::cout << "Iniciando resolução do problema do Carteiro Chinês..." << std::endl;

    // Para cada subgrafo
    for (size_t i = 0; i < subgrafos.size(); ++i) {
        auto subgrafo = subgrafos[i];

        std::cout << "\nAnalisando subgrafo #" << i + 1 << std::endl;

        // Encontra vértices de grau ímpar
        std::vector<std::string> impares = encontrarVerticesImpares(subgrafo);
        std::cout << "Vértices de grau ímpar encontrados: ";
        for (const auto& vertice : impares) {
            std::cout << vertice << " ";
        }
        std::cout << std::endl;

        // Se houver vértices de grau ímpar, torna o subgrafo Euleriano
        if (!impares.empty()) {
            std::cout << "Tornando o subgrafo Euleriano..." << std::endl;
            tornarEuleriano(subgrafo, impares);
        } else {
            std::cout << "Subgrafo já é Euleriano." << std::endl;
        }

        // Encontra a origem a partir dos batalhões
        std::vector<std::string> ciclo;
        std::string origem;
        for (const auto& vertice : batalhoes) {
            if (subgrafo.find(vertice) != subgrafo.end()) {
                origem = vertice;
                std::cout << "Origem encontrada: " << origem << std::endl;
                break;
            }
        }

        // Se a origem foi encontrada, tenta encontrar o ciclo Euleriano
        if (!origem.empty()) {
            std::cout << "Tentando encontrar o ciclo Euleriano a partir de " << origem << "..." << std::endl;
            if (encontrarCicloEuleriano(subgrafo, origem, ciclo)) {
                totalCiclos++;
                ciclo.pop_back(); // Remove a última repetição da origem
                ciclos.push_back(ciclo);

                std::cout << "Ciclo Euleriano encontrado: ";
                for (const auto& vertice : ciclo) {
                    std::cout << vertice << " ";
                }
                std::cout << std::endl;
            } else {
                std::cout << "Não foi possível encontrar um ciclo Euleriano a partir de " << origem << std::endl;
            }
        } else {
            std::cout << "Nenhuma origem válida encontrada nos batalhões." << std::endl;
        }
    }

    // Exibe o total de ciclos encontrados
    std::cout << "\nTotal de ciclos Eulerianos encontrados: " << totalCiclos << std::endl;

    // Exibe os ciclos encontrados
    std::cout << "Ciclos encontrados:" << std::endl;
    for (const auto& ciclo : ciclos) {
        for (const auto& vertice : ciclo) {
            std::cout << vertice << " ";
        }
        std::cout << std::endl;
    }
}