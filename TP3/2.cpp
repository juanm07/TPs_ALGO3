
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
vector<int> distancia;
vector<bool> visitado;

void bfs(int s, vector<vector<int>> &aristas){ //CODIGO DE LA CATEDRA
    visitado[s] = true;
    distancia[s] = 0;
    queue<int> q;
    q.push(s);

    while(!q.empty()){
        int v = q.front(); q.pop();
        for(auto u: aristas[v]){
            if(!visitado[u]){
                visitado[u] = true;
                distancia[u] = distancia[v] + 1;
                q.push(u);
            }
        }
    }
}

void quitarArista(vector<vector<int>> &aristas, int a, int b){

    for(int i=0;i<aristas[a].size();i++){
        if(aristas[a][i] == b){
            aristas[a].erase(aristas[a].begin()+i);
        }
    }

    for(int i=0;i<aristas[b].size();i++){
        if(aristas[b][i] == a){
            aristas[b].erase(aristas[b].begin()+i);
        }
    }

}
vector<vector<int>> distancias(vector<vector<int>> &latencias){
    vector<vector<int>> aristas(N);
    for(int i=0; i<N;i++){ //agrego todas las aristas posibles
        for(int j=0;j<N;j++){
            if(i!=j){
                aristas[i].push_back(j);
            }
        }
    }

    for(int k=0;k<N;k++){ //quito las aristas inncesearias. Es decir, aquellas que tengan un camino indirecto de igual latencia
        for(int i=0;i<N;i++){
            for(int j=0;j<i;j++){
                if(k!=i && k!=j){
                    if(latencias[i][k] + latencias[k][j] == latencias[i][j]){
                            quitarArista(aristas, i, j);
                    }
                }
            }
        }
    }


    vector<vector<int>> res(N, vector<int>(N, 1));

    for(int i=0;i<N;i++){
        res[i][i] = 0;
        distancia.assign(N, 1);
        visitado.assign(N, false);
        bfs(i, aristas); //hago bfs en cada nodo
        for(int j=0; j<i;j++){ //construyo la matriz con las distancias de conexion entre las computadoras
            res[i][j] = distancia[j];
            res[j][i] = distancia[j];
        }
    }

    return res;
}


bool latenciasCompatibles(vector<vector<int>> &latencias){ //me fijo que la matriz sea FW
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

        vector<vector<int>>M(N, vector<int>(N, 0));

        for(int i = 1; i<cant_computadoras;i++){
            for(int j = 0; j<i;j++){
                int latencia;
                cin>> latencia;

                M[i][j] = latencia;
                M[j][i] = latencia;
            }
        }

        vector<vector<int>> latencias = M;

        bool esPosible = latenciasCompatibles(latencias);


        if(esPosible){
            cout<<"POSIBLE"<<endl;

            vector<vector<int>> res = distancias(latencias);

            for(int i = 0; i<N; i++){
                for(int j = 0; j<N;j++){
                    cout << res[i][j] << " ";
                }
                cout << endl;
            }
        }else{
            cout<<"IMPOSIBLE"<<endl;
        }

        tests--;
    }
    return 0;
}
