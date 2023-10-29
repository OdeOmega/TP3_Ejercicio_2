#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;

int INF = numeric_limits<int>::max();

struct triple {
    long long latencia;
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

void distConexion(vector<triple> latencias, int cantPC){
    sort(latencias.begin(),latencias.end());
    vector<vector<pair<int,int>>> grafo(cantPC);
    vector<bool> agregado(cantPC,false);
    DSU DSU(cantPC);
    for(int i = 0; i < latencias.size(); i++){
        triple latActual = latencias[i];
        if(!agregado[latActual.PC1] || !agregado[latActual.PC2]){
            agregado[latActual.PC1] = true;
            agregado[latActual.PC2] = true;
            grafo[latActual.PC1].push_back({latActual.PC2,latActual.latencia});
            grafo[latActual.PC2].push_back({latActual.PC1,latActual.latencia});
            DSU.unite(latActual.PC1,latActual.PC2);
        }
        else{
            if(DSU.find(latActual.PC1) != DSU.find(latActual.PC2)){
                grafo[latActual.PC1].push_back({latActual.PC2,latActual.latencia});
                grafo[latActual.PC2].push_back({latActual.PC1,latActual.latencia});
                DSU.unite(latActual.PC1,latActual.PC2);
            }
            else{

            }
        }
    }
}


int main() {
    int cantTest, cantPC, latencia;
    cin >> cantTest;
    for(int i = 0; i < cantTest; i++){
        cin >> cantPC;
        vector<triple> latencias;
        for(int j = 0; j < cantPC; j++){
            for(int k = 0; k < j; k++){
                cin >> latencia;
                latencias.push_back({latencia,j,k});
            }
        }
        distConexion(latencias, cantPC);
    }
    return 0;
}

