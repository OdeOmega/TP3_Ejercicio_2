#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int INF = numeric_limits<int>::max();

struct triple {
    int latencia;
    int PC1;
    int PC2;

    bool operator<(const triple& other) const {
        if (latencia < other.latencia) {
            return true;
        } else {
            return false;
        }
    }

};

struct DSU {
    vector<int> padre;
    vector<int> tam;

    DSU(int n){
        padre = vector<int>(n);
        tam = vector<int>(n,0);
        for(int i = 0; i<n;i++){
            padre[i] = i;
        }
    }
    int find(int v){
        if (padre[v] != v){
            padre[v] = find(padre[v]);
        }
        return padre[v];
    }

    void unite (int a, int b){
        a = find(a);
        b = find(b);
        if(tam[a] < tam[b]){
            swap(a,b);
        }
        padre[b] = a;
        tam[a] = tam[a]+1;
    }

};

void floyW(vector<vector<int>>& grafo, vector<triple> latenciasLista){
    sort(latenciasLista.begin(),latenciasLista.end());
    DSU DSU(latenciasLista.size());
    int N = grafo.size();
    bool posible = true;
    vector<bool> agregado(N, false);
    vector<vector<int>> grafo2(grafo.size(),vector<int>(grafo.size(),INF));
    vector<vector<int>> distancias(N, vector<int>(N, 1));
    for(int p = 0; p < N; p++){
        distancias[p][p] = 0;
    }
    for(int i = 0; i < latenciasLista.size(); i++){
        int latActual = latenciasLista[i].first;
        int pc1 = latenciasLista[i].PC1
    }
    for(int i = 0; i < N ; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                if(grafo[i][j] == grafo[i][k] + grafo[k][j]){
                    if(distancias[i][j] < distancias[i][k] + distancias[k][j]){
                        distancias[i][j] = distancias[i][k] + distancias[k][j];
                        distancias[j][i] = distancias[i][k] + distancias[k][j];
                    }
                }
                if(grafo[i][j] > grafo[i][k] + grafo[k][j]){
                    posible = false;
                    cout << "IMPOSIBLE" << endl;
                    i = N;
                    j = N;
                    k = N;
                }
            }
        }
    }
    if(posible){
        cout << "POSIBLE" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << distancias[i][j] << " ";
            }
            cout << endl;
        }
    }
}


int main() {
    int cantTest, cantPC, latencia;
    cin >> cantTest;
    for(int i = 0; i < cantTest; i++){
        cin >> cantPC;
        vector<vector<int>> latencias(cantPC, vector<int>(cantPC,0));
        vector<triple> latenciasLista = {};
        for(int j = 0; j < cantPC; j++){
            for(int k = 0; k < j; k++){
                cin >> latencia;
                latencias[j][k] = latencia;
                latencias[k][j] = latencia;
                latenciasLista.push_back({latencia,j,k});
            }
        }
        floyW(latencias,latenciasLista);
    }
    int a = INF;
    return 0;
}