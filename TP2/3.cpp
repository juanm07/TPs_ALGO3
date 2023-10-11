#include <iostream>
#include <vector>
#include <tuple>
using namespace std;




int main(){
    int tests;
    cin>>tests;

    while(tests > 0){

        int cant_edificios; //N
        cin>>cant_edificios;

        int cant_conexiones_posibles; //M
        cin>>cant_conexiones_posibles;

        vector<vector<int>>mat_ady(cant_edificios,vector<int>(cant_edificios));
        vector<tuple<int,int,int,int>>aristas(cant_conexiones_posibles); //{d_i,r_i,u,v}

        for(int i = 0; i<cant_conexiones_posibles;i++){
            int u;
            cin>>u;

            int v;
            cin>>v;
            
            
            int d_i;
            cin>>d_i;

            int r_i;
            cin>>r_i;

            u--,v--;
            tuple<int,int,int,int>arista = make_tuple(d_i,r_i,u,v);
            aristas[i] = arista;


        }


        tests--;
    }
}