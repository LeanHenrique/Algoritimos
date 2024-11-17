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
std::vector<std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>> criaSubgrafos(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo,
    const std::vector<std::vector<std::string>>& componentes) {
        
    // Lista para armazenar cada subgrafo (um por componente)
    std::vector<std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>> subgrafos;

    // Itera sobre cada componente
    for (const auto& regiao : componentes) {
        // Inicializa o subgrafo para este componente
        std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> subgrafo;

        // Conjunto para verificar rapidamente se um vértice pertence à região
        std::unordered_set<std::string> regiaoSet(regiao.begin(), regiao.end());

        // Adiciona as arestas entre os vértices da região
        for (const auto& vertice : regiao) {
            bool verticeTemArestas = false;  // Flag para verificar se o vértice tem arestas na região
            for (const auto& vizinho : grafo.at(vertice)) {
                // Verifica se o vizinho pertence à região
                if (regiaoSet.find(vizinho) != regiaoSet.end()) {
                    subgrafo[vertice].push_back({vizinho, 0});  // Adiciona a aresta com peso 0
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

bool modifiedDFS(
    const std::string& atual, 
    const std::string& origem, 
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& subgrafo, 
    std::vector<std::string>& ciclo
) {
    // Visita o vértice atual
    std::cout << "Visitando: " << atual << std::endl;
    ciclo.push_back(atual);  // Adiciona o vértice ao ciclo

    // Percorre todas as arestas conectadas ao vértice atual
    auto it = subgrafo.find(atual);
    if (it != subgrafo.end()) {
        std::vector<std::pair<std::string, int>>& vizinhos = it->second;  // Obtém os vizinhos

        // Verifica se todos os pesos das arestas são 0
        bool todasArestasVisitadas = true;
            for (auto& [vertice, vizinhos] : subgrafo) {
                for (auto& [vizinho, peso] : vizinhos) {
                    if (peso == 0) {  // Se algum peso for 0, significa que a aresta não foi visitada
                        todasArestasVisitadas = false;
                        break;
                    }
                }
                if (!todasArestasVisitadas) break;
            }

        // Se todos os pesos são 0 e o vértice atual for igual ao início, encontrou um ciclo
        if (todasArestasVisitadas && atual == origem) {
            std::cout << "Ciclo encontrado!" << std::endl;
            return true;  // Encontrou o ciclo
        }

        // Ordena as arestas por peso
        std::cout << "Ordenando as arestas de " << atual << " por peso" << std::endl;
        for (size_t i = 0; i < vizinhos.size(); ++i) {
            for (size_t j = i + 1; j < vizinhos.size(); ++j) {
                if (vizinhos[i].second > vizinhos[j].second) {
                    std::swap(vizinhos[i], vizinhos[j]);  // Troca para garantir a ordem de menor para maior peso
                }
            }
        }

        // Exibe as arestas ordenadas
        for (size_t i = 0; i < vizinhos.size(); ++i) {
            std::cout << "Vizinho: " << vizinhos[i].first << " Peso: " << vizinhos[i].second << std::endl;
        }

        // Percorre os vizinhos agora ordenados pelo peso
        for (size_t i = 0; i < vizinhos.size(); ++i) {
            std::cout << "Visitando a aresta de " << atual << " para " << vizinhos[i].first << std::endl;
            // Incrementa o peso da aresta (segundo elemento do par)
            vizinhos[i].second++;

            // Chama recursivamente o DFS
            std::cout << "Aplicando DFS para " << vizinhos[i].first << std::endl;
            if (modifiedDFS(vizinhos[i].first, origem, subgrafo, ciclo)) {
                return true;  // Encontrou um ciclo, retorna imediatamente
            }
        }
    }

    // Remove o vértice ao retroceder no DFS
    ciclo.pop_back();
    return false;
}


void percorreSubgrafo(
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& subgrafo,
    std::string& origem,
    std::vector<std::string>& ciclo) {

    bool encontrouCiclo = false;
    bool todasArestasVisitadas = false;  // Variável para controlar se todas as arestas foram visitadas
    std::cout << "Iniciando DFS para o subgrafo com origem: " << origem << std::endl;

    // Continua até que todas as arestas sejam visitadas
    while (!todasArestasVisitadas) {
        std::cout << "Executando modifiedDFS a partir de " << origem << std::endl;
        encontrouCiclo = modifiedDFS(origem, origem, subgrafo, ciclo);  // Começa o DFS de origem

        if (encontrouCiclo) {
            std::cout << "Ciclo encontrado, verificando se todas as arestas foram visitadas..." << std::endl;
            
            // Verifica se todas as arestas foram percorridas
            todasArestasVisitadas = true;
            for (auto& [vertice, vizinhos] : subgrafo) {
                for (auto& [vizinho, peso] : vizinhos) {
                    if (peso == 0) {  // Se algum peso for 0, significa que a aresta não foi visitada
                        todasArestasVisitadas = false;
                        break;
                    }
                }
                if (!todasArestasVisitadas) break;
            }

            if (todasArestasVisitadas) {
                std::cout << "Todas as arestas foram visitadas. Finalizando DFS para este subgrafo." << std::endl;
                break;  // Todas as arestas foram percorridas, então encerra
            }
        }
    }
}


void rodarDFSNosSubgrafos(
    std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
    const std::vector<std::vector<std::string>>& componentes,
    const std::vector<std::string>& batalhoes) {

    // Cria os subgrafos a partir do grafo e dos componentes
     std::cout << "Criando os subgrafos a partir do grafo e dos componentes..." << std::endl;
    std::vector<std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>> subgrafos = criaSubgrafos(Grafo, componentes);    

    std::vector<std::vector<std::string>> ciclos;  // Vetor para armazenar ciclos de cada subgrafo
       std::cout << "Iterando sobre os subgrafos para encontrar ciclos..." << std::endl;

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

        if (origem.empty()) {
            continue;
        }

        std::vector<std::string> ciclo;  // Ciclo para este subgrafo

        // Chama a função para rodar o DFS no subgrafo e acumular os ciclos
        percorreSubgrafo(subgrafo, origem, ciclo);

        // Se o ciclo foi encontrado, adiciona ao vetor de ciclos
        if (!ciclo.empty()) {
            ciclos.push_back(ciclo);  // Armazena o ciclo para o subgrafo atual
        }

    }

    // Imprime os ciclos encontrados para cada subgrafo
    std::cout << "Ciclos encontrados:" << std::endl;
    for (size_t i = 0; i < ciclos.size(); ++i) {
        const auto& ciclo = ciclos[i];
        for (const auto& vertice : ciclo) {
            std::cout << vertice << " ";
        }
        std::cout << std::endl;
    }
}
