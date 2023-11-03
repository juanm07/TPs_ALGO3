#include <iostream>
#include <vector>
using namespace std;
int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;


struct Vertice{
    int nombre;
};

struct Arista{
    int nodo_incidente;
    int capacidad;
    int flujo;
};

bool no_es_esquina_ni_borde(int i,int j,int n){
    return (i!=n-1 && i!=0 && j!=n-1 && j!=0);
}
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

    while (new_flow = bfs(s, t, parent)) {
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
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                if((tablero[i][j] == 1) && no_es_esquina_ni_borde(i,j,N) && r_no_tiene_aguj_ady(i,j,N,tablero)){
                    vertices_filas+=2;
                    
                }
            }
        }
        for (int j = 0; j < N; j++){
            for (int i = 0; i < N; i++){
                if((tablero[i][j] == 1) && no_es_esquina_ni_borde(i,j,N) && c_no_tiene_aguj_ady(i,j,N,tablero)){
                    vertices_col+=2;
                    
                }
            }
        }
        
        
        
        tests--;
    }
}
