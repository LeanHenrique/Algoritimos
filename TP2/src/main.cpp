#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "ford_fulkerson.h"
#include "sort.h"

#define INFINITO 1000000 // Substitui INT_MAX por um valor grande

int main() {
    // Estruturas para armazenar o grafo, nós e geradores
    std::map<int, std::map<int, int>> Graph;  // Grafo de conexões e capacidades
    std::map<int, int> nodes;  // Mapeamento dos nós e suas demandas
    std::set<int> Geradores;  // Conjunto de geradores (nós com demanda 0)
    int DemandaMax = 0;  // A soma das demandas totais
    int EnergiaMax = 0;  // A soma das energias totais dos geradores

    int V, E;
    std::cin >> V >> E;  // Lê o número de vértices (nós) e arestas

    // Lendo os nós e suas demandas
    for (int i = 0; i < V; i++) {
        int indice, demanda;
        std::cin >> indice >> demanda;
        DemandaMax += demanda;  // Soma a demanda máxima
        if (demanda == 0) {
            Geradores.insert(indice);  // Adiciona o nó aos geradores se a demanda for 0
        }
        nodes[indice] = demanda;  // Registra a demanda do nó
    }

    // Lendo as conexões da rede (arestas)
    for (int i = 0; i < E; i++) {
        int Vi, Vj, C;
        std::cin >> Vi >> Vj >> C;
        if (Geradores.find(Vi) != Geradores.end()) {
            EnergiaMax += C;  // Se o nó Vi for gerador, soma sua energia
        }
        if (Vi) {
            Graph[Vi][Vj] = C;  // Adiciona a capacidade da aresta Vi -> Vj
        }
    }

    // Construção do grafo com fonte e sumidouro artificiais
    int fonteArtificial = 0;  // Fonte artificial (representa o ponto de origem)
    int sumidouroArtificial = V + 1;  // Sumidouro artificial (representa o ponto de destino)

    // Criação do grafo de capacidades
    std::map<int, std::map<int, int>> capacidade;

    // Adiciona as capacidades do grafo original
    for (const auto& u_map : Graph) {
        for (const auto& v_pair : u_map.second) {
            capacidade[u_map.first][v_pair.first] = v_pair.second;  // Adiciona cada aresta no grafo de capacidades
        }
    }

    // Conecta a fonte artificial aos geradores com capacidade infinita
    for (const auto& [nodo, tipo] : nodes) {
        if (tipo == 0) {  // Se o nó é um gerador
            capacidade[fonteArtificial][nodo] = INFINITO;
        }
    }

    // Conecta os consumidores ao sumidouro artificial com sua demanda
    for (const auto& [nodo, tipo] : nodes) {
        if (tipo > 0) {  // Se o nó é um consumidor com demanda
            capacidade[nodo][sumidouroArtificial] = tipo;
        }
    }

    // Mapa para armazenar as arestas que atingiram a capacidade máxima
    std::map<int, std::map<int, int>> arestasMax;

    // Executa o algoritmo de Ford-Fulkerson para calcular o fluxo máximo
    int fluxoMaximo = fordFulkerson(capacidade, fonteArtificial, sumidouroArtificial, arestasMax, Graph);
    
    // Calcula a energia perdida e a demanda não atendida
    int Energia_perdida = EnergiaMax - fluxoMaximo;
    int Demanda_nAtendida = DemandaMax - fluxoMaximo;

    // Exibe o fluxo máximo, a demanda não atendida e a energia perdida
    std::cout << fluxoMaximo << std::endl;
    std::cout << Demanda_nAtendida << std::endl;
    std::cout << Energia_perdida << std::endl;

    // Transferindo as arestas que atingiram a capacidade máxima para um vetor de vetores (u, v, capacidade)
    std::vector<std::vector<int>> arestas;
    for (const auto& u_map : arestasMax) {
        for (const auto& v_pair : u_map.second) {
            arestas.push_back({u_map.first, v_pair.first, v_pair.second});
        }
    }

    // Ordena as arestas pela capacidade (índice 2 do vetor) em ordem decrescente
    insertionSort(arestas);

    // Imprime o número de arestas e as arestas ordenadas
    std::cout << arestas.size() << std::endl;
    for (const auto& aresta : arestas) {
        std::cout << aresta[0] << " " << aresta[1] << " " << aresta[2] << std::endl;
    }

    return 0;
}
