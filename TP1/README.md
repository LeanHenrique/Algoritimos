# Trabalho Prático 1 - Algoritmos I

Este repositório contém a solução do Trabalho Prático 1 da disciplina **Algoritmos I** da **Universidade Federal de Minas Gerais**. O projeto aborda problemas computacionais relacionados à geopolítica fictícia do Império de Archadia, utilizando conceitos de teoria dos grafos.

## Objetivos

1. **Definir a capital**: Determinar o vértice que minimiza a soma das distâncias para todos os outros vértices conectados.
2. **Identificar batalhões adicionais**: Posicionar batalhões em regiões desconectadas para melhorar a segurança.
3. **Verificar rotas de patrulhamento**: Avaliar a viabilidade de ciclos fechados para patrulhamento em cada região.

## Modelagem do Problema

- O império é representado como um grafo dirigido:
  - **Vértices**: Cidades.
  - **Arestas**: Estradas unidirecionais entre cidades.
  
Os desafios foram tratados como problemas computacionais distintos, utilizando algoritmos clássicos de grafos.

## Abordagem

### 1. Definir a Capital
- **Algoritmo Utilizado**: Busca em Largura (BFS).
- **Descrição**:
  - Calcula a soma das distâncias de cada vértice para todos os outros no grafo.
  - O vértice com a menor soma é escolhido como capital.

### 2. Definir Batalhões Adicionais
- **Algoritmo Utilizado**: Kosaraju para identificar componentes fortemente conexos (CFCs).
- **Descrição**:
  - Para cada CFC desconectado da capital, um batalhão é posicionado na cidade mais próxima.

### 3. Verificar Patrulhamento
- **Algoritmo Utilizado**: Busca em Profundidade (DFS).
- **Descrição**:
  - Verifica a existência de ciclos em cada subgrafo, garantindo rotas de patrulhamento válidas.

## Análise de Complexidade

- **Definir a Capital**: \(O(V^2 + VE)\)
- **Definir Batalhões Adicionais**: \(O(V^2 + VE)\)
- **Verificar Patrulhamento**: \(O(V^2 + VE)\)
- **Complexidade Total**: \(O(V^3)\) no pior caso.

## Resultados

- O programa calcula:
  - A capital do império.
  - O número e a localização dos batalhões adicionais.
  - As rotas de patrulhamento ou a indicação de impossibilidade.

## Considerações Finais

Este trabalho foi uma excelente oportunidade para aprofundar o conhecimento em teoria dos grafos e algoritmos relacionados. Os desafios enfrentados, especialmente na implementação de ciclos, enriqueceram o aprendizado prático e teórico.

## Como Executar

1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/seu-repositorio.git

2. Compile o código C++;
   MAKE ALL

3. Execute o programa:
   ./TP1
   

