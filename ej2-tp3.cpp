


#include <iostream>
#include <vector>

using namespace std;

int N;


void floyd(vector<vector<int>> &matriz_dist, vector<vector<int>> &latencias, vector<vector<bool>> &usados){
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (latencias[i][j] > (latencias[i][k] + latencias[k][j])) {
                    latencias[i][j] = latencias[i][k] + latencias[k][j];
                    latencias[j][i] = latencias[i][k] + latencias[k][j];
                    matriz_dist[i][j] = matriz_dist[i][k] + matriz_dist[k][j];
                    matriz_dist[j][i] = matriz_dist[i][k] + matriz_dist[k][j];

                    usados[i][j] = false;
                    usados[j][i] = false;
                }
            }
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (latencias[i][j] == (latencias[i][k] + latencias[k][j])) {
                    if (usados[i][k] && usados[k][j]) {
                        matriz_dist[i][j] = matriz_dist[i][k] + matriz_dist[k][j];
                        matriz_dist[j][i] = matriz_dist[i][k] + matriz_dist[k][j];
                    }
                }
            }
        }
    }
}


bool latenciasCompatibles(vector<vector<int>> &latencias){

        for(int i = 0;i<N;i++){
            for(int j=0;j<i;j++){
                for(int k=0;k<N;k++){
                    if(k!=i && k!=j){
                        if(latencias[i][k] + latencias[k][j] == latencias[i][j]) break;
                        if(latencias[i][k] + latencias[k][j] < latencias[i][j]) return false;
                    }
                }
            }
        }
        return true;
}

int main() {
    int tests;
    cin>>tests;

    while(tests > 0){

        int cant_computadoras; //N
        cin>>cant_computadoras;

        N = cant_computadoras;

        vector<vector<int>>grafo(N, vector<int>(N, 0));

        for(int i = 1; i<cant_computadoras;i++){
            for(int j = 0; j<i;j++){
                int latencia;
                cin>> latencia;

                grafo[i][j] = latencia;
                grafo[j][i] = latencia;

            }
        }

        vector<vector<int>> latencias = grafo;
        bool esPosible = true;
        if(N > 2){
            esPosible = latenciasCompatibles(latencias);
        }

        if(esPosible){
            cout<< "POSIBLE" <<endl;

            vector<vector<bool>> enlaces_visitados(N, vector<bool>(N,true));

            vector<vector<int>> matriz_dist(N, vector<int>(N,1));
            for(int i=0;i<N;i++) matriz_dist[i][i] = 0;

            floyd(matriz_dist, latencias, enlaces_visitados);

            for(int i = 0; i<N; i++){
                for(int j = 0; j<N;j++){
                    cout << matriz_dist[i][j] << " ";
                }
                cout << endl;
            }
        }else{
            cout<< "IMPOSIBLE" <<endl;
        }

        tests--;
    }
    return 0;
}




