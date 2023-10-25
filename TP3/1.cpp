#include <iostream>
#include <vector>
using namespace std;


struct Arista
{
    int nodo_incidente;
    int peso;
};



int dijkstra_mod(vector<vector<Arista>>&grafo,vector<pair<int,int>>&dist){
    for(int i = 0;i<grafo.size();i++){
        for(int j = 0;j<grafo[i].size();j++){
            Arista e = grafo[i][j];
            int dist_posible = dist[i].first + e.peso;
            if(e.peso == 2){//si la arista es un pasadizo
               if(dist[i].second + dist[e.nodo_incidente].second+1<= 3){//si la cant de pasadizos usados para conseguir la dist minima para llegar al nodo al cual apunta la arista
                                                                       //mas la cant de pasadizos usados para conseguir la dist minima desde el nodo origen mas 1, es menor o igual a 3
                    if(dist_posible < dist[e.nodo_incidente].first){//si encontre un mejor camino
                            dist[e.nodo_incidente].first = dist_posible;
                            dist[e.nodo_incidente].second = dist[e.nodo_incidente].second + dist[i].second + 1; //use un pasadizo
                    }
               }
            }else{//es una arista normal
                if((dist_posible < dist[e.nodo_incidente].first)//si puedo mejorar la distancia del nodo al que apunta la arista y si haciendolo no uso mas de 3 pasadizos
                    && (dist[i].second + dist[e.nodo_incidente].second <= 3)){
                    dist[e.nodo_incidente].first = dist_posible;
                    dist[e.nodo_incidente].second = dist[e.nodo_incidente].second + dist[i].second;
                }
            }

        }
    }
    int n = grafo.size()-1;
    return dist[n].first;
}


int main(){
    int tests;
    cin>>tests;
    while (tests>0)
    {
        int cant_salones,cant_pasadizos;
        cin>>cant_salones;
        cin>>cant_pasadizos;

        vector<vector<Arista>>lista_ady(cant_salones);
        vector<pair<int,int>>distancias_con_pasadizos(cant_salones); //la primer componente es la dist minima desde el inicio, la segunda es cuantos pasadizos use
        for(int i = 0;i<cant_salones;i++){
            distancias_con_pasadizos[i] = make_pair(i+1,0); //inicializo todas las distancias en el valor que tomaría llegar sin pasadizos
        }
        for (int i = 0; i < cant_salones-1; i++)
        {
            Arista v1;
            v1.peso = 1;
            v1.nodo_incidente = i+1;
            lista_ady[i].push_back(v1);
        }
        for (int i = 0; i < cant_pasadizos; i++)
        {
            Arista v1;
            Arista v2;
            int inicio,final;
            cin>>inicio;
            cin>>final;

            v2.peso = 2;
            v2.nodo_incidente = final-1;
            lista_ady[inicio-1].push_back(v2);
        }
        int res = dijkstra_mod(lista_ady,distancias_con_pasadizos);
        cout<<res<<endl;
        tests--;
    }

}
