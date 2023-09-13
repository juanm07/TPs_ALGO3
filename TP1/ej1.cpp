#include <iostream>
#include <vector>

using namespace std;

int camino_min;
int camino_max;
int INF = 1e17;

bool esPosValida(vector<vector<char>> &tablero, int fila_actual, int col_actual){
    int N = tablero.size();
    int M = tablero[0].size();

    return (0<=fila_actual && fila_actual < N && 0<=col_actual && col_actual<M && tablero[fila_actual][col_actual] != '#');
}


void sendero(vector<vector<char>> &tablero,vector<vector<int>> &utilizados, int fila_anterior, int col_anterior, int fila_actual, int col_actual, int long_actual) {
    int N = tablero.size();
    int M = tablero[0].size();


    if (fila_actual == N - 1 && col_actual == M - 1) {
        if(long_actual < camino_min){
            camino_min = long_actual;
        }
        if(long_actual > camino_max){
            camino_max = long_actual;
        }
        return;
    }

    if(!esPosValida(tablero, fila_actual, col_actual)) return;

    if(utilizados[fila_actual][col_actual] == 1) return;

    utilizados[fila_actual][col_actual] = 1;

    if(col_actual == col_anterior && fila_actual == fila_anterior){ // Si estoy en la primera casilla, puedo ir abajo o a la derecha
        sendero(tablero, utilizados, fila_actual, col_actual,fila_actual + 1, col_actual, long_actual + 1); //voy abajo
        sendero(tablero, utilizados, fila_actual, col_actual,fila_actual, col_actual + 1, long_actual + 1); //voy der
    }else{
        if(tablero[fila_actual][col_actual] == 'L'){//Si estoy en L y vengo de la izq/der ahora puedo ir abajo o arriba, y sivengo de arriba/abajo puedo ir a la izq o a la der
            if(fila_actual == fila_anterior){
                sendero(tablero, utilizados,fila_actual, col_actual,fila_actual+1,col_actual,long_actual+1); //voy abajo
                sendero(tablero, utilizados,fila_actual, col_actual,fila_actual-1,col_actual,long_actual+1); //voy arriba
            }else{
                sendero(tablero, utilizados, fila_actual, col_actual,fila_actual, col_actual - 1, long_actual + 1); //voy izq
                sendero(tablero, utilizados, fila_actual, col_actual,fila_actual, col_actual + 1, long_actual + 1); //voy der
            }

        }else {
            if (tablero[fila_actual][col_actual] == 'I') {//Si estoy en I y vengo de abajo/arriba ahora puedo ir arriba/abajo, y si vengo de izq/der puedo ir der/izq
                if(col_actual == col_anterior){
                    if(fila_anterior + 1 == fila_actual){
                        sendero(tablero, utilizados,fila_actual, col_actual, fila_actual + 1, col_actual, long_actual + 1); // voy abajo
                    }else{
                        sendero(tablero, utilizados, fila_actual, col_actual,fila_actual - 1, col_actual, long_actual + 1); //voy arriba
                    }
                }else{
                    if(col_anterior + 1 == col_actual){
                        sendero(tablero, utilizados, fila_actual, col_actual,fila_actual, col_actual + 1, long_actual + 1); // voy der
                    }else{
                        sendero(tablero, utilizados, fila_actual, col_actual,fila_actual, col_actual - 1, long_actual + 1); //voy izq
                    }
                }
            } else {
                if (tablero[fila_actual][col_actual] == '+') {//Si estoy en + puedo ir a cualquier lado
                    sendero(tablero, utilizados,fila_actual, col_actual, fila_actual + 1, col_actual, long_actual + 1); //voy abajo
                    sendero(tablero, utilizados, fila_actual, col_actual,fila_actual - 1, col_actual, long_actual + 1); //voy arriba
                    sendero(tablero, utilizados, fila_actual, col_actual,fila_actual, col_actual - 1, long_actual + 1); // voy izq
                    sendero(tablero, utilizados, fila_actual, col_actual,fila_actual, col_actual + 1, long_actual + 1); //voy der
                }
            }
        }
    }

    utilizados[fila_actual][col_actual] = 0;
}


int main() {
    int tests;
    cin >> tests;

    while (tests > 0) {
        int N;
        cin >> N;

        int M;
        cin >> M;

        vector<vector<char>> tablero(N,vector<char>(M));

        for (int i = 0; i < N; i++) {
            for(int j=0;j<M; j++){
                cin >> tablero[i][j];
            }
        }

        if( tablero[N - 1][M - 1] == '#'){ // veo si el último casillero es vacío.
            cout << "IMPOSIBLE" << endl;
        }else{
            vector<vector<int>> utilizados(N,vector<int>(M, 0));
            camino_min = INF;
            camino_max = 0;
            sendero(tablero, utilizados,0,0,0,0,0); // empiezo desde la posición (0,0)
            if(camino_min != INF){
                cout << "POSIBLE " << camino_min << ' ' << camino_max<< endl;
            }else{
                cout << "IMPOSIBLE" << endl;
            }
        }

        tests--;
    }
    return 0;
}
