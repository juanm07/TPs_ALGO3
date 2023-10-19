
#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

vector<vector<int>> grafo;
int N;
vector<vector<int>> tree_edges;
vector<int> back_edges_ext_sup;
vector<int> back_edges_ext_inf;
vector<int> estado;
vector<int> memo;


void dfs(int v, int p){ //codigo de la catedra
    estado[v] = 1; //EMPECE A VER
    for(int u: grafo[v]){
        if(estado[u] == 0){//SI NO LO VI
            tree_edges[v].push_back(u);
            dfs(u, v);
        }else{
            if(u != p){
                if(estado[u] == 1){//SI EMPECE A VER
                    back_edges_ext_inf[v]++;
                }else{
                    back_edges_ext_sup[v]++;
                }
            }
        }
    }
    estado[v] = 2; // TERMINE DE VER
}

int cubren(int v, int p){ //codigo de la catedra
    if(memo[v] != -1) return memo[v];
    int res = 0;
    for(int hijo : tree_edges[v]){
        if(hijo != p){
            res += cubren(hijo, v);
        }
    }

    res -= back_edges_ext_sup[v];
    res += back_edges_ext_inf[v];

    memo[v] = res;
    return res;
}

bool hayPuentes(int v, int w){

    tree_edges.assign(N, vector<int>());
    back_edges_ext_sup.assign(N, 0);
    back_edges_ext_inf.assign(N, 0);
    estado.assign(N, 0);
    memo.assign(N, -1);

    int i = 0;
    while(grafo[v][i] != w) i++;
    grafo[v].erase(grafo[v].begin()+i); //borro el vertice w de la lista de ady de v

    int j = 0;
    while(grafo[w][j] != v) j++;
    grafo[w].erase(grafo[w].begin()+j); //borro el vertice w de la lista de ady de v

    int componentes = 0;
    for(int k = 0; k<N;k++){
        if(estado[k] == 0){
            dfs(k, -1);
            componentes++;
        }
    }

    int puentes = 0;
    for(int k=0;k<N;k++){
        if(cubren(k,-1)==0){
            puentes++;
        }
    }
    puentes -=componentes;

    grafo[v].insert(grafo[v].begin() + i, w); // vuelvo a agregar el vertice w a la lista de ady de v
    grafo[w].insert(grafo[w].begin() + j, v); // vuelvo a agregar el vertice v a la lista de ady de w
    
    return (puentes>0);
}

vector<pair<int,int>> malvinas(){

    vector<pair<int,int>> importantes;

    for(int i = 0;i<N;i++){
        for(int u : grafo[i]){
            if(u>i){ // pido u>i para no repetir aristas
                if(hayPuentes(i,u)){ // si al quitar la arista tengo puentes, entonces dicha arista es importante
                    pair<int,int>arista = make_pair(min(i,u),max(i,u));
                    importantes.push_back(arista);
                }
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



        vector<vector<int>>lista_ady(cant_vertices);
        
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
