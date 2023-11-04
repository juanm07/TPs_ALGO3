#include <iostream>
#include <vector>
#include <queue>
using namespace std;

long long INF = 1e17;

int n;
int cant_personas;

vector<vector<long long>> capacity;
vector<vector<long long>> capacidades_original;
vector<vector<int>> adj;

long long bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, long long>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        long long flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                long long new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

long long maxflow(int s, int t) { // E-K de la catedra
    long long flow = 0;
    vector<int> parent(n);
    long long new_flow;

    while ((new_flow = bfs(s, t, parent))){
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

long long envios(long long desde, long long hasta){ // hago una busqueda binaria entre la cantidad de herramientas que puede llevar cada persona
    long long res = 0;

    while(hasta >= desde){
        long long mitad = (hasta+desde)/2;
        for(int i=0;i<n; i++){
            for(int j=0;j<n;j++){
                capacity[i][j] = capacidades_original[i][j]/mitad; //divido las aristas por la cant de herramientas
            }
        }
        long long max_actual = maxflow(0, n-1); // el flujo máximo seria la cant de personas que pueden llevar X (mitad) herramientas
        long long cant_herramientas_actual = cant_personas*mitad; //cant total de herramientas que se pueden transportar

        if(max_actual >= cant_personas && cant_herramientas_actual > res){
            res = cant_herramientas_actual;
            desde  = mitad + 1;
        }else{
            hasta = mitad - 1;
        }
    }

    return res;

}

int main(){
    int tests;
    cin>>tests;

    while (tests>0){
        int N; //cant esquinas
        cin >> N;

        int M; // cant calles
        cin >> M;

        int x; // cant de compañeros
        cin >> x;

        cant_personas = x;

        n = N;

        vector<vector<int>> grafo(N);
        vector<vector<long long>> capacidades(N, vector<long long>(N, 0));

        long long max_capacidad = 0;

        for (int i = 0; i < M; i++) {
            int v,w,c;
            cin >> v >> w >> c; // esquina origen, esquina destino y cantidad de herramientas

            grafo[v - 1].push_back(w-1);
            capacidades[v-1][w-1] = c;

            if(c>max_capacidad) max_capacidad = c; // max_capacidad va a ser mi cota superior para la busqueda binaria
        }

        adj = grafo;
        capacidades_original = capacidades;

        capacity.assign(N, vector<long long>(N,0));

        long long res = envios(1, max_capacidad);

        cout << res << endl;
        tests--;
    }
    return 0;
}
