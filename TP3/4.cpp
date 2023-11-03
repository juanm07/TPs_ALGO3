
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int INF = 1e7;

int n;
int cant_personas;

vector<vector<int>> capacity;
vector<vector<int>> capacidades_original;
vector<vector<int>> adj;

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

int envios(int desde, int hasta){
    int res = 0;

    while(hasta - desde > 1){
        int mitad = (hasta+desde)/2;
        for(int i=0;i<n; i++){
            for(int j=0;j<n;j++){
                capacity[i][j] = capacidades_original[i][j]/mitad;
            }
        }
        int max_actual = maxflow(0, n-1);

        if(max_actual >= cant_personas && max_actual*mitad > res){
            res = max_actual*mitad;
            desde  = mitad;
        }else{
            hasta = mitad;
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
        vector<vector<int>> capacidades(N, vector<int>(N, 0));

        int max_capacidad = 0;

        for (int i = 0; i < M; i++) {
            int v,w,c;
            cin >> v >> w >> c; // esquina origen, esquina destino y cantidad de herramientas

            grafo[v - 1].push_back(w-1);
            capacidades[v-1][w-1] = c;

            max_capacidad = max(max_capacidad, c);
        }

        adj = grafo;
        capacidades_original = capacidades;

        capacity.assign(N, vector<int>(N,0));

        int res = envios(1, max_capacidad);

        cout << res << endl;
        tests--;
    }
    return 0;
}
