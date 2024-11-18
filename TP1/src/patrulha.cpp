#include "patrulha.h"
#include "dfs.h"
#include "auxiliares.h"

// Função para rodar DFS em cada subgrafo e encontrar ciclos
void rodarDFSNosSubgrafos(
    std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
    const std::vector<std::vector<std::string>>& componentes,
    const std::vector<std::string>& batalhoes) {

    // Cria os subgrafos a partir dos componentes
    std::vector<std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>> subgrafos = criaSubgrafos(Grafo, componentes);

    // Vetor para armazenar ciclos de cada subgrafo
    std::vector<std::vector<std::string>> ciclos;
    int contaciclos = 0;

    // Percorre todos os subgrafos e encontra os ciclos
    for (size_t i = 0; i < subgrafos.size(); ++i) {
        auto& subgrafo = subgrafos[i];
        std::string origem;
        
        // Encontra o primeiro vértice que está no batalhão
        for (const auto& vertice : batalhoes) {
            if (subgrafo.find(vertice) != subgrafo.end()) {
                origem = vertice;
                break;
            }
        }

        // Se nenhum vértice do batalhão foi encontrado, pula para o próximo subgrafo
        if (origem.empty()) {
            continue;
        }

        std::vector<std::string> ciclo;  // Ciclo para este subgrafo

        // Chama a função para rodar o DFS no subgrafo e acumular os ciclos
        DfsPatrulhamento(origem, origem, subgrafo, ciclo);

        // Se o ciclo foi encontrado, adiciona ao vetor de ciclos
        if (!ciclo.empty()) {
            ciclos.push_back(ciclo);  // Armazena o ciclo para o subgrafo atual
            contaciclos++;
        }
    }

    // Imprime os ciclos encontrados para cada subgrafo
    std::cout << contaciclos << std::endl;
    for (size_t i = 0; i < ciclos.size(); ++i) {
        const auto& ciclo = ciclos[i];
        for (size_t j = 0; j < ciclo.size() - 1; ++j) {  // Itera até o penúltimo vértice
            std::cout << ciclo[j] << " ";
        }
        std::cout << std::endl;
    }
}
