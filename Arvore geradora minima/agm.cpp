#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int minCostConnectPoints(vector<vector<int>>& points) {
        int numeroPontos = points.size(); //qtd de pontos a serem analisados
        priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> filaPri; //funcao de fila de prioridade
        filaPri.push({0,0}); 
        int soma = 0; //guarda a soma do PRIM
        vector<int> visitados(numeroPontos,0); //marca os pontos visitados

        while(!filaPri.empty()){ //para quando percorre toda a heap
            pair<int,int> p = filaPri.top(); //guarda os valores do nó e do caminho do topo da heap
            filaPri.pop(); //remove da heap
            int no = p.second; 
            int caminho = p.first;

            if(visitados[no]) continue;
            visitados[no]=1; 
            soma += caminho; //adiciona o valor na soma do PRIM

            for(int i=0; i<numeroPontos; i++){
                if(!visitados[i]){ //se nao foi visitado adiciona ao heap
                    int x1= points[no][0]; 
                    int x2 = points[i][0];
                    int y1 = points[no][1];
                    int y2 = points[i][1];
                    filaPri.push({abs(x2-x1)+abs(y2-y1), i}); // a aresta vai ser dada pela diferenca de manhattan dos pontos
                }
            }
        }

        return soma;

    }
};