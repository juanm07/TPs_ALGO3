#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#include <bits/stdc++.h>

float C;

struct DSU {
    DSU(int n){
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
        tamano = vector<int>(n,1);
    }
 
    int find(int v){
        while(padre[v] != v) v = padre[v];
        return v;
    }
 
    void unite(int u, int v){
        u = find(u); v = find(v);
        if(tamano[u] < tamano[v]) swap(u,v);
        //ahora u es al menos tan grande como v
        padre[v] = u;
        tamano[u] += tamano[v];
    }
 
    vector<int> padre;
    vector<int> tamano;
 
    //tamano[v] <= n
    //INV: si padre[v] != v entonces tamano[padre[v]] >= 2*tamano[v]
};


float edificios(vector<tuple<int,int,int>>&aristas){
    vector<float>posibles_Cs;
}



int kruskal(vector<tuple<int,int,int>>& E, int n){
    long long res = 0;
    sort(E.begin(),E.end(),greater<int>());
    DSU dsu(n);
 
    int aristas = 0;
    for(auto arista : E){
        //tuple<int,int,int,int> arista = E[i];
        int c_i = get<0>(arista);
        int u = get<1>(arista);
        int v = get<2>(arista);
        
        //u y v estan en distinta cc?
        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u,v);
            res += c_i;
            aristas++;
        }
        if(aristas == n-1) break;
    }
    
    if(aristas == n-1) return res;
    //else cout<<"IMPOSSIBLE\n";
}
 
// int main(){
//     int n,m;
//     cin>>n>>m;
//     vector<tuple<int,int,int>> E(m); //(costo,u,v)
//     for(int i = 0; i < m; i++){
//         int u,v,w;
//         cin>>u>>v>>w;
//         u--, v--;
//         E[i] = {w,u,v};
//     }
    
//     kruskal(E,n);
    
//     return 0;
// }


int main(){
    int tests;
    cin>>tests;

    while(tests > 0){

        int cant_edificios; //N
        cin>>cant_edificios;

        int cant_conexiones_posibles; //M
        cin>>cant_conexiones_posibles;

        vector<vector<int>>mat_ady(cant_edificios,vector<int>(cant_edificios));
        vector<tuple<int,int,int>>aristas(cant_conexiones_posibles); //{c_i,u,v}

        for(int i = 1; i<cant_conexiones_posibles;i++){
            int u;
            cin>>u;

            int v;
            cin>>v;
            
            
            int d_i;
            cin>>d_i;

            int r_i;
            cin>>r_i;

            //u--,v--;
            int c_i = r_i * C - r_i;
            tuple<int,int,int>arista = make_tuple(c_i,u,v);
            aristas[i] = arista;


        }
        
        int res = kruskal(aristas,cant_conexiones_posibles);


        tests--;
    }
}
