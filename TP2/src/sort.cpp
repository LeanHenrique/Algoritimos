#include "sort.h"

// Função para realizar a ordenação das arestas por capacidade
void insertionSort(std::vector<std::vector<int>>& vec) {
    size_t n = vec.size();
    for (size_t i = 1; i < n; i++) {
        std::vector<int> key = vec[i];
        size_t j = i - 1;

        // Move os elementos para a direita, até encontrar o local da chave
        while (j < n && vec[j][2] < key[2]) {  // Alterado para '<'
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = key;
    }
}