#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;

int INF = numeric_limits<int>::max();

void eliminarAristas(vector<vector<int>> grafo){

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
        }
    return 0;
}