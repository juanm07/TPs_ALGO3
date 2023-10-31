#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;
//vector<vector<int>> capacity;
vector<vector<int>> adj;
int INF = 1e7;

int bfs(int s, int t, vector<int>& parent,vector<vector<int>>&capacidades,vector<vector<int>>& adj) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacidades[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacidades[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t,vector<vector<int>>&capacidades,vector<vector<int>>&adj) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent,capacidades,adj)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacidades[prev][cur] -= new_flow;
            capacidades[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

bool no_esquina(int i,int j,int n){
    return !((i==0 && j==0)||(i==0 && j == n-1)||(i==n-1 && j == 0)||(i==n-1 && j == n-1));
}

int main(){
    int tests;
    cin>>tests;
    while (tests>0){
        int N;
        cin>>N;

        vector<vector<int>>tablero;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                int casillero;
                cin>>casillero;
                tablero[i][j] = casillero;
            }
        }
        for(int i = 0;i<N;i++){
            for(int j = 0;j<N;j++){
                if(tablero[i][j] == 1 && no_esquina(i,j,N)){

                }
            }
        }
        




        tests--;
    }
    
}
