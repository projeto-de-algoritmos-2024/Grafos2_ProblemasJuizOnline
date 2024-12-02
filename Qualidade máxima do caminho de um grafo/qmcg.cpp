#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Função DFS para explorar os caminhos
    void dfs(int no, int tempo, int tempoMaximo, vector<vector<pair<int, int>>>& grafo, vector<int>& valores, unordered_set<int>& nosVisitados, int qualidadeAtual, int& qualidadeMaxima) {
        // Se o tempo ultrapassar o máximo permitido, interrompa a busca
        if (tempo > tempoMaximo) {
            return;
        }

        // Se voltarmos para o nó 0, calcule a qualidade total do caminho
        if (no == 0 && tempo <= tempoMaximo) {
            qualidadeMaxima = max(qualidadeMaxima, qualidadeAtual);
        }

        // Explore todos os vizinhos do nó atual
        for (auto& vizinho : grafo[no]) {
            int proxNo = vizinho.first;
            int tempoCaminho = vizinho.second;

            // Se o próximo nó ainda não foi visitado, explore-o
            if (nosVisitados.find(proxNo) == nosVisitados.end()) {
                nosVisitados.insert(proxNo);  // Marque o nó como visitado
                dfs(proxNo, tempo + tempoCaminho, tempoMaximo, grafo, valores, nosVisitados, qualidadeAtual + valores[proxNo], qualidadeMaxima);
                nosVisitados.erase(proxNo);  // Desmarque o nó após explorar
            } else {
                // Caso o nó já tenha sido visitado, exploramos com ele já incluído
                dfs(proxNo, tempo + tempoCaminho, tempoMaximo, grafo, valores, nosVisitados, qualidadeAtual, qualidadeMaxima);
            }
        }
    }

    int maximalPathQuality(vector<int>& valores, vector<vector<int>>& arestas, int tempoMaximo) {
        int n = valores.size();
        vector<vector<pair<int, int>>> grafo(n);

        // Criar o grafo com as arestas
        for (auto& aresta : arestas) {
            int u = aresta[0], v = aresta[1], tempo = aresta[2];
            grafo[u].emplace_back(v, tempo);
            grafo[v].emplace_back(u, tempo);
        }

        // Variável para manter a qualidade máxima encontrada
        int qualidadeMaxima = 0;

        // Conjunto para marcar os nós visitados
        unordered_set<int> nosVisitados;
        nosVisitados.insert(0);  // Começar no nó 0

        // Realiza a busca DFS a partir do nó 0 com tempo inicial 0 e qualidade inicial do nó 0
        dfs(0, 0, tempoMaximo, grafo, valores, nosVisitados, valores[0], qualidadeMaxima);

        return qualidadeMaxima;
    }
};