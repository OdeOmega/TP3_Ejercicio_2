#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;

int INF = numeric_limits<int>::max();

vector<vector<long long>> eliminarAristas(vector<vector<long long>> grafo){
    int N = grafo.size();
    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i != j && k != j && i != k){
                    if(grafo[i][j] == grafo[i][k] + grafo[k][j]){
                        grafo[i][j] = INF;
                    }
                }
            }
        }
    }
    for(int p = 0; p < N; p++){
        grafo[p][p] = 0;
    }
    return grafo;
}

pair<vector<vector<long long>>,vector<vector<long long>>> floyd(vector<vector<long long>> grafo){
    int N = grafo.size();
    vector<vector<long long>> distancias(N, vector<long long>(N));
    for(int p = 0; p < N; p++){
        for(int q = 0; q < N; q++){
            if(p == q){
                distancias[p][q] = 0;
            }
            else if(grafo[p][q] == INF){
                distancias[p][q] = INF;
            }
            else{
                distancias[p][q] = 1;
            }
        }
    }
    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(grafo[i][j] > grafo[i][k] + grafo[k][j]){
                    grafo[i][j] = grafo[i][k] + grafo[k][j];
                }
                if(distancias[i][j] > distancias[i][k] + distancias[k][j]){
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                }

            }
        }
    }
    return {grafo,distancias};
}


int main() {
    int cantTest, cantPC, latencia;
    cin >> cantTest;
    for(int i = 0; i < cantTest; i++){
        cin >> cantPC;
        vector<vector<long long>> grafo(cantPC,vector<long long>(cantPC,INF));
        for(int j = 0; j < cantPC; j++){
            for(int k = 0; k < j; k++){
                cin >> latencia;
                grafo[j][k] = latencia;
                grafo[k][j] = latencia;
                }
            }
        for(int i = 0; i < cantPC; i++){
            grafo[i][i] = 0;
        }
        vector<vector<long long>> limpio = eliminarAristas(grafo);
        pair<vector<vector<long long>>,vector<vector<long long>>> recuperado_dist = floyd(limpio);
        if(recuperado_dist.first != grafo){
            cout << "IMPOSIBLE" << endl;
        } else{
            cout << "POSIBLE" << endl;
            for(int i = 0; i < cantPC; ++i){
                for (int j = 0; j < cantPC; ++j) {
                    cout << recuperado_dist.second[i][j] << " ";
                }
                cout << endl;
            }
        }
        }
    return 0;
}