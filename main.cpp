#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;

int INF = numeric_limits<int>::max();

struct MinHeap {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    void push(pair<int, int> value) {
        minHeap.push(value);
    }
    void pop() {
        minHeap.pop();
    }
    pair<int, int> top() {
        return minHeap.top();
    }
    size_t size() const {
        return minHeap.size();
    }
    bool isEmpty() const {
        return minHeap.empty();
    }
};


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

pair<int,int> dijkstraAristas(vector<vector<pair<int,int>>>& grafo, int v, int w){
    int N = grafo.size();
    vector<int> minimos(N, INF);
    vector<int> cantidadAristas(N, -1);
    minimos[v] = 0;
    cantidadAristas[v] = 0;
    MinHeap heap;
    heap.push({0,v});

    while (!heap.isEmpty()){
        int distancia = heap.top().first;
        int vertice = heap.top().second;
        heap.pop();

        if (vertice == w) {
            return {distancia, cantidadAristas[w]};
        }

        for(int i = 0; i < grafo[vertice].size(); i++){
            int posibleNuevaDist = minimos[vertice] + grafo[vertice][i].second;
            if(posibleNuevaDist < minimos[grafo[vertice][i].first]){
                minimos[grafo[vertice][i].first] = posibleNuevaDist;
                cantidadAristas[grafo[vertice][i].first] = cantidadAristas[vertice] + 1;
                heap.push({posibleNuevaDist,grafo[vertice][i].first});
                heap.push({posibleNuevaDist,grafo[vertice][i].first});
            }
        }
    }
    return {-1,-1};
}

void distConexion(vector<triple> latencias, int cantPC){
    vector<vector<int>> distancias(cantPC, vector<int>(cantPC));
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
            distancias[latActual.PC1][latActual.PC2] = 1; //Como agrego el arista que los une, si dist es cero
            distancias[latActual.PC2][latActual.PC1] = 1;

        }
        else{
            if(DSU.find(latActual.PC1) != DSU.find(latActual.PC2)){
                grafo[latActual.PC1].push_back({latActual.PC2,latActual.latencia});
                grafo[latActual.PC2].push_back({latActual.PC1,latActual.latencia});
                DSU.unite(latActual.PC1,latActual.PC2);
                distancias[latActual.PC1][latActual.PC2] = 1;
                distancias[latActual.PC2][latActual.PC1] = 1;

            }
            else{ // revisar que la distancia que voy a agregar sean menores o iguales a las que ya están
                pair<int,int> lat_dist = dijkstraAristas(grafo, latActual.PC1,latActual.PC2);
                if(lat_dist.first < latActual.latencia){
                    i = latencias.size();
                    cout << "IMPOSIBLE" << endl;
                }
                else{
                    grafo[latActual.PC1].push_back({latActual.PC2,latActual.latencia});
                    grafo[latActual.PC2].push_back({latActual.PC1,latActual.latencia});
                    distancias[latActual.PC1][latActual.PC2] = lat_dist.second;
                    distancias[latActual.PC2][latActual.PC1] = lat_dist.second;
                }
            }
        }
    }
    cout << "POSIBLE" << endl;
    for (int i = 0; i < cantPC; ++i) {
        for (int j = 0; j < cantPC; ++j) {
            cout << distancias[i][j] << " ";
        }
        cout << endl;
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

