#include <iostream>
#include <queue>
#include <vector>
#include <climits>

#define INF LLONG_MAX

using namespace std;

class Solution {
public:
    // Estrutura para armazenar as arestas
    struct Aresta {
        int prox;
        int custo;
    };

    // Função para calcular a distância mínima entre nós usando Dijkstra com fila de prioridade
    void dijkstra(int n, vector<vector<Aresta>>& grafo, vector<long long>& distancia, int inicio) {
        distancia.assign(n, INF);
        distancia[inicio] = 0;

        // Fila de prioridade para armazenar os nós e suas distâncias
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, inicio});

        while (!pq.empty()) {
            long long d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // Se a distância já for maior que a distância atual, ignore
            if (d > distancia[u]) continue;

            // Atualiza as distâncias dos vizinhos
            for (const Aresta& e : grafo[u]) {
                int v = e.prox;
                int custo = e.custo;
                long long distanciaNova = distancia[u] + custo;
                if (distanciaNova < distancia[v]) {
                    distancia[v] = distanciaNova;
                    pq.push({distancia[v], v});
                }
            }
        }
    }

    vector<bool> findAnswer(int n, vector<vector<int>>& arestas) {
        // Passo 1: Criar o grafo com lista de adjacência
        vector<vector<Aresta>> grafo(n);

        // Preenche o grafo com os dados das arestas
        for (const auto& aresta : arestas) {
            int u = aresta[0];
            int v = aresta[1];
            int custo = aresta[2];

            // Adiciona aresta de u para v
            grafo[u].push_back({v, custo});

            // Adiciona aresta de v para u (grafo não direcionado)
            grafo[v].push_back({u, custo});
        }

        // Passo 2: Rodar Dijkstra de 0 para todos os nós e de n-1 para todos os nós
        vector<long long> distanciaComeco(n, INF);
        vector<long long> distanciaFinal(n, INF);
        dijkstra(n, grafo, distanciaComeco, 0);  // Distâncias do nó 0
        dijkstra(n, grafo, distanciaFinal, n - 1); // Distâncias do nó n-1

        // Passo 3: Verificar se cada aresta faz parte de um caminho de menor custo
        long long menorDistancia = distanciaComeco[n - 1];
        vector<bool> resultadoFinal(arestas.size(), false);

        for (int i = 0; i < arestas.size(); i++) {
            int u = arestas[i][0];
            int v = arestas[i][1];
            int custo = arestas[i][2];

            // Verifica se a aresta (u, v) faz parte do caminho de menor custo
            if (distanciaComeco[u] != INF && distanciaFinal[v] != INF) {
                if (distanciaComeco[u] + custo + distanciaFinal[v] == menorDistancia) {
                    resultadoFinal[i] = true;
                }
            }

            // Verifica a aresta v -> u
            if (distanciaComeco[v] != INF && distanciaFinal[u] != INF) {
                if (distanciaComeco[v] + custo + distanciaFinal[u] == menorDistancia) {
                    resultadoFinal[i] = true;
                }
            }
        }

        return resultadoFinal;
    }
};