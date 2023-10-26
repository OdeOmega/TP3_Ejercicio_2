#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int INF = numeric_limits<int>::max();

void bellman(vector<vector<int>> grafo){
    int N = grafo.size();
    vector<long long> minimos(N,INF);
    minimos[0] = 0;
    bool hayCambios = true;
    while(hayCambios){


        hayCambios = false;
        vector<long long> minimosTemp = minimos;
        for(int i = 1; i<minimosTemp.size();i++){
            long long posibleNuevo = INF;
            for(int j = 0; j<i+1; j++){
                long long TEMP = minimos[j]+grafo[j][i];
                posibleNuevo = min(posibleNuevo,TEMP);
            }
            if(posibleNuevo != minimosTemp[i]){
                hayCambios = true;
                minimos[i] = posibleNuevo;
            }

        }
    }
    int K = minimos.size()/4;
    long long ceroPuentes = minimos[K - 1];
    long long unPuente = minimos[2*K - 1];
    long long dosPuentes = minimos[3*K - 1];
    long long tresPuentes = minimos[4*K - 1];
    cout << min(ceroPuentes,min(unPuente,min(dosPuentes,tresPuentes))) << endl;
}

int main() {
    int cantTest, cantSalones, cantTuneles, entrada, salida;
    cin >>cantTest;
    for(int i = 0; i < cantTest; i++){
        cin >> cantSalones >> cantTuneles;
        vector<vector<int>> caminos((cantSalones+1)*4, vector<int>((cantSalones+1)*4,INF));
        for(int j = 0; j < caminos.size()-1;j++){
            caminos[j][j+1] = 1;
            caminos[j][j] = 0;
        }

        caminos[caminos.size()-1][caminos.size()-1] = 0;

        int N = cantSalones + 1;
        for(int k = 0; k < cantTuneles; k++){
            cin >> entrada >> salida;
            caminos[entrada][salida+N] = 2;
            caminos[entrada+N][salida + 2*N] = 2;
            caminos[entrada + 2*N][salida + 3*N] = 2;
        }
        bellman(caminos);
    }
    return 0;
}

