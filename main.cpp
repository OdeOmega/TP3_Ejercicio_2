#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;

int INF = numeric_limits<int>::max();

void eliminarAristas(vector<vector<int>>& grafo){
    int N = grafo.size();
    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i != j){
                    if(grafo[i][j] == grafo[i][k] + grafo[k][j]){
                        grafo[i][j] = INF;
                    }

                }
            }
        }
    }
}

int main() {
    int cantTest, cantPC, latencia;
    cin >> cantTest;
    for(int i = 0; i < cantTest; i++){
        cin >> cantPC;
        vector<vector<int>> grafo(cantPC,vector<int>(cantPC,INF));
        for(int j = 0; j < cantPC; j++){
            for(int k = 0; k < j; k++){
                cin >> latencia;
                grafo[j][k] = latencia;
                grafo[k][j] = latencia;
                }
            }
        eliminarAristas(grafo);
        int a = 0;
        }


    int a = 0;
    return 0;
}