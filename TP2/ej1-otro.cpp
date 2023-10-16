#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

vector<vector<int>> grafo;
int N;
vector<vector<int>> tree_edges;
vector<int> back_edges_ext_sup;
vector<int> back_edges_ext_inf;
vector<vector<int>> back_edges;
vector<int> estado;

void dfs(int v, int p){ //codigo de la catedra
    estado[v] = 1;
    for(int u: grafo[v]){
        if(estado[u] == 0){
            tree_edges[v].push_back(u);
            dfs(u, v);
        }else{
            if(u != p){
                if(estado[u] == 1){
                    back_edges_ext_inf[v]++;
                }else{
                    back_edges_ext_sup[v]++;
                    back_edges[v].push_back(u);
                }
            }
        }
    }
    estado[v] = 2;
}

int cubren(int v, int p, vector<int> &memo){ //codigo de la catedra
    if(memo[v] != -1) return memo[v];
    int res = 0;
    for(int hijo : tree_edges[v]){
        if(hijo != p){
            res += cubren(hijo, v, memo);
        }
    }

    res -= back_edges_ext_sup[v];
    res += back_edges_ext_inf[v];

    memo[v] = res;
    return res;
}

bool hayPuentes(int v, int w, vector<int> &memo){
    int k = 0;
    while(grafo[w][k] != v){
        k++;
    }
    grafo[w].erase(grafo[w].begin()+k);
    int puentes = 0; int componentes = 0;
    for(int i=0;i<N;i++){
        if(cubren(i,v,memo)==0) puentes++;
        if(estado[i] == 2) componentes++;
    }
    puentes -=componentes;

    grafo[w].push_back(v);
    return (puentes>0);
}

vector<pair<int,int>> malvinas(){

    vector<pair<int,int>> importantes;

    dfs(0,-1);

    vector<int> memo(N, -1);

    for(int i=0;i<N;i++){
        for(int v: tree_edges[i]){
            if(hayPuentes(v,i,memo)){
                pair<int, int> enlace = make_pair(min(i, v), max(i, v));
                importantes.push_back(enlace);
            }
        }
    }

    for(int i = 0; i<back_edges.size();i++){
        for(int u: back_edges[i]){
            if(cubren(u,i,memo)==1){
                pair<int, int> enlace = make_pair(min(i, u), max(i, u));
                importantes.push_back(enlace);
            }
        }
    }

    sort(importantes.begin(), importantes.end());
    return importantes;

}

int main(){
    int tests;
    cin >> tests;
    while(tests > 0){
        int cant_vertices;
        cin>>cant_vertices;

        N = cant_vertices;

        int cant_aristas;
        cin>>cant_aristas;

        tree_edges.resize(N);
        back_edges_ext_sup.resize(N);
        back_edges_ext_inf.resize(N);
        back_edges.resize(N);
        estado.assign(N, 0);

        vector<vector<int>>lista_ady(cant_vertices);
        //vector<vector<bool>>mat(cant_vertices,vector<bool>(cant_vertices,false)); //voy a ir marcando las aristas "imporantes"
        for(int i = 0; i<cant_aristas;i++){
            int U,V;
            cin>>U;
            cin>>V;
            lista_ady[U].push_back(V);
            lista_ady[V].push_back(U);
        }

        grafo = lista_ady;

        vector<pair<int,int>> importantes = malvinas();

        int K = importantes.size();

        cout<<K<<endl;

        for(int i=0;i<K;i++){
            cout<<importantes[i].first<<" "<<importantes[i].second<<endl;
        }
        tests--;
    }
    return 0;
}
