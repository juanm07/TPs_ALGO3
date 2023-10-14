#include <iostream>
#include <vector>
#include <tuple>
#include <numeric>
using namespace std;

#include <bits/stdc++.h>


float C;

struct DSU { // código de la cátedra
    explicit DSU(int n){
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

bool compararPesos(tuple<int,int,int,int>& x, tuple<int,int,int,int>& y){
    float c_1 = get<0>(x) - C*get<1>(x);
    float c_2 = get<0>(y) - C*get<1>(y);
    return c_1>c_2;
}

float kruskal(vector<tuple<int,int ,int,int>>& E, int n){ //código de la cátedra modificado
    float res = 0;
    sort(E.begin(),E.end(),compararPesos); //ordeno las aristas de manera decreciente segun d_i - C*r_i
    DSU dsu(n);

    int aristas = 0;
    for(auto arista : E){
        int d_i = get<0>(arista);
        int r_i = get<1>(arista);
        float c_i = d_i - C*r_i;
        int u = get<2>(arista);
        int v = get<3>(arista);

        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u,v);
            res += c_i;
            aristas++;
        }
        if(aristas == n-1) break;
    }

    return res; // res = sum_{e \in T}(d_e - C*r_e)
}

void edificios(vector<tuple<int,int,int,int>>&aristas, int n){
    float desde = 0;
    float hasta = 1e7;

    while(abs(hasta-desde)>=1e-5){
        C = (desde+hasta)/2;
        float cuenta = kruskal(aristas, n);
        if(cuenta >= 0){
            desde = C;
        }else{
            hasta = C;
        }
    }
}


pair<int,int> solOptima(vector<tuple<int,int,int,int>>& E, int n){ //código de la cátedra modificado
    int sum_D = 0;
    int sum_R = 0;
    sort(E.begin(),E.end(),compararPesos); //ordeno las aristas de manera decreciente segun d_i - C*r_i
    DSU dsu(n);

    int aristas = 0;
    for(auto arista : E){
        int d_i = get<0>(arista);
        int r_i = get<1>(arista);
        int u = get<2>(arista);
        int v = get<3>(arista);

        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u,v);
            sum_D += d_i;
            sum_R += r_i;
            aristas++;
        }
        if(aristas == n-1) break;
    }

    pair<int,int> sol = make_pair(sum_D,sum_R);
    return sol;

}
int main(){
    int tests;
    cin>>tests;

    while(tests > 0){

        int cant_edificios; //N
        cin>>cant_edificios;

        int cant_conexiones_posibles; //M
        cin>>cant_conexiones_posibles;


        vector<tuple<int,int,int,int>>aristas(cant_conexiones_posibles); //{d_i,r_i,u,v}

        for(int i = 1; i<=cant_conexiones_posibles;i++){
            int u;
            cin>>u;

            int v;
            cin>>v;


            int d_i;
            cin>>d_i;

            int r_i;
            cin>>r_i;


            tuple<int,int,int,int>arista = make_tuple(d_i, r_i,u,v);
            aristas[i-1] = arista;

        }


        edificios(aristas, cant_conexiones_posibles);

        pair<int,int> sol = solOptima(aristas, cant_conexiones_posibles); //busco la sol optima con el mejor C hallado

        int sum_D = sol.first;
        int sum_R = sol.second;

        cout<< sum_D << ' ' << sum_R << endl;

        tests--;
    }
    return 0;
}

