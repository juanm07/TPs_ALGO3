#include <iostream>
#include <vector>
#include <queue>

using namespace std;



bool esValido(int n, int m, vector<vector<bool>>&visitado){
    int cant_filas = visitado.size();
    int cant_col = visitado[0].size();
    return ((n>=0 && n<cant_filas) && (m>=0 && m < cant_col));
}

vector<pair<int,int>>obtener_vecinos(int i, int j, vector<vector<bool>> &visitado,vector<vector<int>>&distancias_min,vector<vector<int>>&mat){
    vector<pair<int,int>>res;
    vector<pair<int,int>>posibles_movimientos = {{0,1},{0,-1},{1,0},{-1,0}}; //derecha,izquierda,arriba,abajo
    for(pair<int,int>movimiento : posibles_movimientos){
        int nueva_col = j + movimiento.second;
        int nueva_fila = i + movimiento.first;
        if(esValido(nueva_fila, nueva_col, visitado) && (!visitado[nueva_fila][nueva_col])){ //me fijo si no se va de rango y si no lo visité
            if(mat[nueva_fila][nueva_col]!=0){ //si va a haber una manifestacion
                if(distancias_min[i][j]+1<mat[nueva_fila][nueva_col]){ //si el tiempo que me tomo llegar a mi pos_actual + 1
                                                                      // no se pasa del tiempo en el que arranca la manifestacion
                    pair<int,int>c = make_pair(nueva_fila,nueva_col);
                    res.push_back(c);
                }
            }else{//si no va a haber manifestaciones agrego directo
                pair<int,int>c = make_pair(nueva_fila,nueva_col);
                res.push_back(c);
            }
        }
    }
    return res;
}

int bfs(int fila,int col,int h1,int h2,vector<vector<int>>&mat,vector<vector<bool>>&visitado,vector<vector<int>>&distancias_min,int tiempo_inicial){
    visitado[fila][col] = true;
    distancias_min[fila][col] = tiempo_inicial; //en el primer bfs tiempo_inicial va a ser 0
    queue<pair<int,int>>q;
    pair<int,int>c = make_pair(fila,col);
    q.push(c);
    while(!q.empty()){
        pair<int,int>v = q.front(); q.pop();
        vector<pair<int,int>>adyacentes = obtener_vecinos(v.first,v.second,visitado,distancias_min,mat);


        for(pair<int,int> nodo : adyacentes){
            visitado[nodo.first][nodo.second] = true;
            distancias_min[nodo.first][nodo.second] = distancias_min[v.first][v.second] + 1;
            q.push(nodo);
        }
    }
    if(distancias_min[h1][h2] == 0)return -1; //si la distancia del nodo destino se mantuvo en 0 es porque nunca lo visite. Entonces es imposible
    return distancias_min[h1][h2];
}

int main(){

    int tests;

    cin >> tests;

    while(tests>0) {
        int cant_filas;
        cin >> cant_filas;

        int cant_col;
        cin >> cant_col;

        vector<vector<int>> mat(cant_filas, vector<int>(cant_col));
        for (int i = 0; i < cant_filas; i++) {
            for (int j = 0; j < cant_col; j++) {
                int vertice;
                cin >> vertice;
                mat[i][j] = vertice;
            }

        }
        int x1; //coordenada x del inicio
        cin >> x1;
        int y1; //coordenada y del inicio
        cin >> y1;

        int x2; //coordenada x del hospital
        cin >> x2;
        int y2; //coordenada y del hospital
        cin >> y2;

        if ((x1 == x2) && (y1 == y2)) {
            cout << 0 << endl;
            cout << 0 << endl;
        } else {

            vector<vector<int>> dist(cant_filas, vector<int>(cant_col, 0));
            vector<vector<bool>> visit(cant_filas, vector<bool>(cant_col, false));

            int res = bfs(x1, y1, x2, y2, mat, visit, dist, 0);

            if (res == -1) {
                cout << "IMPOSIBLE" << endl;
            } else {
                

                vector<vector<int>> distancias(cant_filas, vector<int>(cant_col, 0));
                vector<vector<bool>> visitad(cant_filas, vector<bool>(cant_col, false));

                int vuelta = bfs(x2, y2, x1, y1, mat, visitad, distancias, res);
                if (vuelta == -1) {
                    cout << "IMPOSIBLE" << endl;
                } else {
                    cout << res << " "<<vuelta<<endl;
                }
            }

        }
        tests--;
    }

}
