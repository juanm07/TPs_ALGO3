#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int INF = 1e7;

int n;
vector<vector<int>> capacity;
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

    while (new_flow = bfs(s, t, parent)){
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

    while (tests>0){
        int N; //cant esquinas
        cin >> N;

        int M; // cant calles
        cin >> M;

        int x; // cant de compañeros
        cin >> x;

        n=N;

        int cantNodos = N+x+1;
        //int cantAristas = M + 2*x;
        int esquina_taller = x+1;

        vector<vector<int>> grafo(cantNodos);
        vector<vector<int>> capacidades(cantNodos);

        for(int i = 0; i<x;i++){ //fuente
            grafo[0].push_back(i);
            capacidades[0].push_back(INF);
        }

        for(int i=1;i<x+2;i++){ //compañeros
            grafo[i].push_back(esquina_taller);
            capacidades[i].push_back(INF);

        }
        for(int i=x+2;i<=cantNodos;i++){
            int v,w,c;
            cin >> v >> w >> c; // esquina origen, esquina destino y cantidad de herramientas

            grafo[v + esquina_taller - 1].push_back(w-1);
            capacidades[v + esquina_taller - 1].push_back(c);

        }

        adj = grafo;
        capacity = capacidades;

        int res = maxflow(0, cantNodos);

        cout << res << endl;
        tests--;
    }
    return 0;
}
