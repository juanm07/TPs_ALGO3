#include <iostream>
#include <vector>

using namespace std;

int camino_min;
int camino_max;

bool esPosValida(int N, int M, int fila_actual, int col_actual){
    return (0<=fila_actual && fila_actual < N && 0<=col_actual && col_actual<M);
}
string darDireccion(int fila_anterior, int col_anterior, int fila_actual, int col_actual){
    if(fila_actual == fila_anterior && col_actual == col_anterior + 1){
        return "izquierda";
    }
    if(fila_actual == fila_anterior && col_actual == col_anterior - 1){
        return "derecha";
    }
    if(fila_actual == fila_anterior + 1 && col_actual == col_anterior){
        return "arriba";
    }
    if(fila_actual == fila_anterior - 1 && col_actual == col_anterior){
        return "abajo";
    }
    if(fila_actual == fila_anterior && col_actual == col_anterior){
        return "principio";
    }
}

vector<pair<int,int>> movimientosPosibles(char simbolo_actual, string direccion){
    vector<pair<int, int>> mov_posibles;
    if(direccion == "principio"){
        mov_posibles = {{0,  1},{-1, 0}}; //solo puede moverse hacia la derecha o hacia abajo
    }else{
        if(simbolo_actual == 'L'){
            if(direccion == "izquierda" || direccion == "derecha"){
                mov_posibles = {{1, 0}, {-1, 0}}; //hacia arriba o hacia abajo
            }else{
                mov_posibles = {{0, 1}, {0, -1}}; //hacia la derecha o hacia la izquierda
            }
        }else{
            if(simbolo_actual == 'I'){
                if(direccion == "derecha"){
                    mov_posibles = {{0,-1}}; //izquierda
                }
                if(direccion == "izquierda"){
                    mov_posibles = {{0,1}}; //derecha
                }
                if(direccion == "arriba"){
                    mov_posibles = {{1,0}}; //abajo
                }
                if(direccion == "abajo"){
                    mov_posibles = {{-1,0}}; //arriba
                }
            }else{
                mov_posibles = {{0,  1}, {0,  -1},{1,  0},{-1, 0}}; //hacia cualquier lado
            }
        }
    }
    return mov_posibles;
}

void sendero(vector<vector<char>> &tablero,vector<vector<int>> &utilizados, int fila_anterior, int col_anterior, int fila_actual, int col_actual, int long_actual) {
    int N = tablero.size();
    int M = tablero[0].size();

    if (tablero[N - 1][M - 1] == '#') return; //si la ultima es vacia, retorno

    

    if (fila_actual == N - 1 && col_actual == M - 1) { //si llegué al final del tablero, actualizo camino máximo y mínimo
        if (long_actual < camino_min) {
            camino_min = long_actual;
        }
        if (long_actual > camino_max) {
            camino_max = long_actual;
        }
        return;
    }

    string direccion = darDireccion(fila_anterior, col_anterior, fila_actual, col_actual);
    char simbolo_actual = tablero[fila_actual][col_actual];

    vector<pair<int,int>> posibles_mov = movimientosPosibles(simbolo_actual, direccion);

    for(int i=0; i<posibles_mov.size();i++){ //hago la recursion para las posiciones posibles
        int nueva_fila = fila_actual + posibles_mov[i].first;
        int nueva_col = col_actual + posibles_mov[i].second;

        if(esPosValida(N, M, nueva_fila, nueva_col) && tablero[nueva_fila][nueva_col] != '#' && utilizados[nueva_fila][nueva_col] == 0){ //me fijo que la nueva posicion sea válida, que no sea vacía y que no haya sido utilizada
            utilizados[nueva_fila][nueva_col]  =  1;
            sendero(tablero, utilizados, fila_actual, col_actual, nueva_fila, nueva_col, long_actual + 1);
            utilizados[nueva_fila][nueva_col]  =  0;
        }
    }
}

/*void sendero(vector<vector<char>> &tablero,vector<vector<int>> &utilizados, int fila_actual, int col_actual, int long_actual){
    int N = tablero.size();
    int M =  tablero[0].size();

    if(fila_actual == N-1 && col_actual == M-1){ //si llegué al final del tablero, actualizo camino máximo y mínimo
        if(long_actual < camino_min){
            camino_min = long_actual;
        }
        if(long_actual > camino_max){
            camino_max = long_actual;
        }
        return;
    }

    vector<pair<int, int>> posibles_mov = {{0,  1},
                                           {0,  -1},
                                           {1,  0},
                                           {-1, 0}}; //en orden: derecha, izquierda, arriba, abajo

    for(int i=0; i<posibles_mov.size();i++){ //hago la recursion para las 4 posiciones posibles
        int nueva_fila = fila_actual + posibles_mov[i].first;
        int nueva_col = col_actual + posibles_mov[i].second;
        if(esPosValida(N, M, nueva_fila, nueva_col) && tablero[nueva_fila][nueva_col] != '#' && utilizados[nueva_fila][nueva_col] == 0){ //me fijo que la nueva posicion sea válida, que no sea vacía y que no haya sido utilizada
            utilizados[nueva_fila][nueva_col]  =  1;
            sendero(tablero, utilizados, nueva_fila, nueva_col, long_actual + 1);
            utilizados[nueva_fila][nueva_col]  =  0;
        }
    }
}*/
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
        camino_min = 999999;
        camino_max = 0;
        vector<vector<int>> utilizados(N,vector<int>(M, 0));
        utilizados[0][0] = 1;
        sendero(tablero, utilizados,0, 0, 0);

        if(camino_min != 999999){
            cout << "POSIBLE \n" << camino_min <<'\n'<< camino_max << endl;
        }else{
            cout << "IMPOSIBLE" << endl;
        }

        tests--;
    }
    return 0;
}
