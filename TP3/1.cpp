#include <iostream>
#include <vector>
using namespace std;

int INF = 1e7;

struct Arista
{
    int nodo_incidente;
    int peso;
};





int main(){
    int tests;
    cin>>tests;
    while (tests>0)
    {
        int cant_salones,cant_pasadizos;
        cin>>cant_salones;
        cin>>cant_pasadizos;

        vector<vector<Arista>>lista_ady(cant_salones);
        vector<vector<int>>dist_con_pasadizos(cant_salones,vector<int>(4)); //me guardo el tiempo minimo para llegar a un salon i habiendo usado j pasadizos
        for(int i = 0;i<cant_salones;i++){
            for (int j = 0; j < 4; j++){
                dist_con_pasadizos[i][j] = i+1; //inicializo todos los tiempos como si no hubiese pasadizos
            }
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
        //IDEA INSPIRADA EN EL ULTIMO EJERCICIO DE LA CLASE PRACTICA DE DAGS DEL TURNO MAÑANA
        for(int i = 0;i<lista_ady.size();i++){
            for(int j = 0;j<lista_ady[i].size();j++){
                Arista e = lista_ady[i][j];
                if(e.peso == 2){//si es un pasadizo
                    for(int k = 1;k<5;k++){//voy viendo si las distancias usando 0, 1, 2 o 3 pasadizos cambian
                        dist_con_pasadizos[e.nodo_incidente][k] = min(dist_con_pasadizos[e.nodo_incidente][k],dist_con_pasadizos[i][k-1]+2);
                    }//hago k-1 porque hasta ese momento habria tomado k-1 pasadizos
                }else{
                    for(int k = 0;k<4;k++){//si no puedo tomar un pasadizo, quizas al nodo origen llegue mas rapido mediante pasadizos
                                           //por eso actualizo tambien las distancias del nodo incidente
                        dist_con_pasadizos[e.nodo_incidente][k] = min(dist_con_pasadizos[e.nodo_incidente][k],dist_con_pasadizos[i][k]+1);
                    }
                }
            }
        }
        int n = dist_con_pasadizos.size()-1;
        int res = dist_con_pasadizos[n][0];//quizas no habia pasadizos
        for(int i = 0;i<4;i++){
            int d = dist_con_pasadizos[n][i];
            if(d<res) res = d;
        }
        cout<<res<<endl;

        tests--;
    }

}
