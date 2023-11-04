#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;
int INF = 1e7;

struct Vertice{
    int nombre;
};

struct Arista{
    int nodo_incidente;
    int capacidad;
    int flujo;
};

/*bool no_es_esquina_ni_borde(int i,int j,int n){
    return (i!=n-1 && i!=0 && j!=n-1 && j!=0);
}*/
bool r_no_tiene_aguj_ady(int i,int j, int n,vector<vector<int>>&t){
    return (t[i][j-1] == 0 || t[i][j+1] == 0);
}
bool c_no_tiene_aguj_ady(int i,int j, int n,vector<vector<int>>&t){
    return (t[i-1][j] == 0 || t[i+1][j] == 0);
}


int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
int main(){
    int tests;
    cin>>tests;

    while(tests>0){

        int N;
        cin>>N;

        int vertices_filas = 0; //Los vertices iniciales para representar a las filas
        int vertices_col = 0; //Los vertices iniciales para representar a las columnas
        vector<vector<int>>tablero(N,vector<int>(N));
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                int casillero;
                cin>>casillero;
                tablero[i][j] = casillero;
            }
        }
        int pos_ult_aguj_r =-1; //lo iniciaba en 0 y daba mal xd
        int pos_ult_aguj_c=-1;
        for (int i = 0; i < N; i++){//CUENTO CANTIDAD DE VERTICES FILAS
            int cant_aguj = 0;
            pos_ult_aguj_r = -1; //reseteo porque cambie de fila
            for (int j = 0; j < N; j++){
                if(tablero[i][j] == 1){
                    cant_aguj++;
                    if(j>pos_ult_aguj_r+1) vertices_filas++;//si tengo por lo menos un casillero vacio entre la ultima rota y la rota actual
                    pos_ult_aguj_r = j;
                }
            }
            if(N>pos_ult_aguj_r+1)vertices_filas++;//si entre el final y la ultima casilla rota tengo alguna vacia sumo otro vertice
        }
        for (int j = 0; j < N; j++){//CUENTO CANTIDAD DE VERTICES COLUMNAS
            int cant_aguj = 0;
            pos_ult_aguj_c = -1;
            for (int i = 0; i < N; i++){
                if(tablero[i][j] == 1){
                    cant_aguj++;
                    if(pos_ult_aguj_c+1<i)vertices_col++;
                    pos_ult_aguj_c = i;
                } 
            }
            if(N>pos_ult_aguj_c+1) vertices_col++;
        }
        vector<vector<int>>lista_ady(vertices_col+vertices_filas+2);//vertice 0 = fuente y ultimo vertice = sumidero
        vector<vector<int>>matriz_cap(((vertices_filas+1)*(vertices_col+1)),vector<int>(((vertices_filas+1)*(vertices_col+1)),0));
        vector<vector<int>>mapeo_filas(N,vector<int>(N));
        vector<vector<int>>mapeo_columnas(N,vector<int>(N));
        
        int num_vertice = 0;
        //AHORA NECESITO DADA UNA POSICION DEL TABLERO, SABER A QUE NUMERO DE VERTICE CORRESPONDE
        for (int i = 0; i < N; i++){//ME HAGO EL MAPEO DE CASILLEROS A VERTICES FILAS
            pos_ult_aguj_r = -1; //reseteo porque cambie de fila
            for (int j = 0; j < N; j++){
                if(tablero[i][j] == 1){
                    for(int k = pos_ult_aguj_r+1;k<j;k++){//todas las casillas entre el ultimo agujero encontrado y el que encontre ahora se condensan en un vertice solo
                        mapeo_filas[i][k] = num_vertice+1; 
                    }
                    if(j>pos_ult_aguj_r+1) num_vertice++;
                    pos_ult_aguj_r = j;
                }
            }
            for(int k = pos_ult_aguj_r+1;k<N;k++){//me estaba faltando considerar el vertice que correspondia al ultimo representante de esa fila
                mapeo_filas[i][k] = num_vertice+1; 
            }
            if(N>pos_ult_aguj_r+1)num_vertice++;//si entre el final y la ultima casilla rota tengo alguna vacia sumo otro vertice
        }

        for (int j = 0; j < N; j++){//ME HAGO EL MAPEO DE CASILLEROS A VERTICES COLUMNAS
            pos_ult_aguj_r = -1; //reseteo porque cambie de columna
            for (int i = 0; i < N; i++){
                if(tablero[i][j] == 1){
                    for(int k = pos_ult_aguj_r+1;k<i;k++){//todas las casillas entre el ultimo agujero encontrado y el que encontre ahora se condensan en un vertice solo
                        mapeo_columnas[k][j] = num_vertice+1; 
                    }
                    if(i>pos_ult_aguj_r+1) num_vertice++;
                    pos_ult_aguj_r = i;
                }
            }
            for(int k = pos_ult_aguj_r+1;k<N;k++){//me estaba faltando considerar el vertice que correspondia al ultimo representante de esa fila
                mapeo_columnas[k][j] = num_vertice+1; 
            }
            if(N>pos_ult_aguj_r+1)num_vertice++;//si entre el final y la ultima casilla rota tengo alguna vacia sumo otro vertice
        }
        
        for (int i = 1; i <= vertices_filas; i++){
            lista_ady[0].push_back(i);//conecto a la fuente con los vertices de filas
            lista_ady[i].push_back(0);
            matriz_cap[0][i] = 1;   
            //matriz_cap[i][0] = 1; 
        }
        int m = lista_ady.size()-1;
        for (int i = vertices_filas+1; i < lista_ady.size()-1; i++){
            lista_ady[m].push_back(i);//conecto al sumidero con los vertices de columnas
            lista_ady[i].push_back(m);
            matriz_cap[i][m] = 1;
            //matriz_cap[i][m] = 1; 
        }
        
        tests--;
    }
}
