#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct Arista
{   
    long long nodo_origen;
    long long salones_recorridos;
    long long nodo_incidente;
    long long peso;
};

bool comparar(Arista a,Arista b){
    if(a.salones_recorridos > b.salones_recorridos) return true;
    else return false;
}


long long DAG_cm(vector<vector<Arista>>&grafo,vector<pair<long long,long long>>&dist){
    for(int i = 0;i<grafo.size();i++){
        for(int j = 0;j<grafo[i].size();j++){
            Arista e = grafo[i][j];
            long long dist_posible = dist[i].first + e.peso; 
            if(dist_posible < dist[e.nodo_incidente].first){//si encontre un mejor camino
                dist[e.nodo_incidente].first = dist_posible;
            }
        }
    }
    long long n = grafo.size()-1;
    return dist[n].first;
}


int main(){
    int tests;
    cin>>tests;
    while (tests>0)
    {
        long long cant_salones,cant_pasadizos;
        cin>>cant_salones;
        cin>>cant_pasadizos;

        vector<vector<Arista>>lista_ady(cant_salones);
        vector<pair<long long,long long>>distancias_con_pasadizos(cant_salones); //la primer componente es la dist minima desde el inicio, la segunda es cuantos pasadizos use
        vector<Arista>aristas;
        for(int i = 0;i<cant_salones;i++){
            distancias_con_pasadizos[i] = make_pair(i+1,0); //inicializo todas las distancias en el valor que tomaría llegar sin pasadizos
        }

        for (int i = 0; i < cant_pasadizos; i++)
        {
            Arista v2;
            long long inicio,final;
            cin>>inicio;
            cin>>final;

            v2.peso = 2;
            v2.nodo_incidente = final-1;
            v2.nodo_origen = inicio -1;
            v2.salones_recorridos = final - inicio;
            aristas.push_back(v2);
        }
        sort(aristas.begin(),aristas.end(),comparar);//ordeno los pasadizos de mayor a menos en base a cuantos salones cubre
        int puse = 0;
        for (int j = 0; j < aristas.size(); j++){
            if(puse == 3) break;  //si ya meti los 3 mejores pasadizos
            Arista e = aristas[j];
            long long origen = e.nodo_origen;
            if(lista_ady[origen].size()!=0)continue; //si el salon ya tiene un pasadizo
            lista_ady[origen].push_back(e);
            puse++;
        }
        
        for (int i = 0; i < cant_salones-1; i++){
            Arista v1;
            v1.peso = 1;
            v1.nodo_incidente = i+1;
            v1.nodo_origen = i;
            v1.salones_recorridos = 1;
            lista_ady[i].push_back(v1); //todos los salones se conectan al siguiente con una arista de peso 1
        }
        
        long long res = DAG_cm(lista_ady,distancias_con_pasadizos);
        cout<<res<<endl;
        tests--;
    }

}
