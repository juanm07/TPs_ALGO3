#include <iostream>
#include <vector>
using namespace std;
long long INF = 1e9;

int malvinas(vector<vector<int>>&lista_ady,vector<vector<bool>>&mat_visitados){
    int k = 0;
    for(int i = 0;i<lista_ady.size();i++){
        if(lista_ady[i].size()<=2){//Si el vertice esta conectado a 2 o menos vertices
            for(int j = 0;j<lista_ady[i].size();j++){
                int val = lista_ady[i][j];
                if((mat_visitados[val][i]))continue; //si ya agregué la arista lo ignoro
                if(val<i){ //chequeo si el vertice conectado a mi vertice actual es menor. Me va a servir para reconstruir la sol en orden lexicografico
                    mat_visitados[val][i] = true; //por eso marco la arista con el menor orden lexicografico. Por ej, en vez de marcar (4,2) marco (2,4)
                }else mat_visitados[i][val] = true; //marco la arista como visitada
                k++;
            }
        }
    }
    return k;
}

int main(){
    int tests;
    cin >> tests;
    while(tests > 0){
        int cant_vertices;
        cin>>cant_vertices;

        int cant_aristas;
        cin>>cant_aristas;

        vector<vector<int>>lista_ady(cant_vertices);
        vector<vector<bool>>mat(cant_vertices,vector<bool>(cant_vertices,false)); //voy a ir marcando las aristas "imporantes"
        for(int i = 0; i<cant_aristas;i++){
            int U,V;
            cin>>U;
            cin>>V;
            lista_ady[U].push_back(V);
            lista_ady[V].push_back(U);
        }
        int res = malvinas(lista_ady,mat);
        cout<<res<<endl;
        for(int i = 0;i<mat.size();i++){
            for(int j = 0; j<mat[0].size();j++){
                if(mat[i][j]){
                    cout<<i<<" "<<j<<endl; 
                }
            }
        }
        tests--;
    }
    return 0;
}
