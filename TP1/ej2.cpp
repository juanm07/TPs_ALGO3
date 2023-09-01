#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


long long int descontentoTotal(vector<int> &M, vector<int> &C, vector<int> &orden){
    long long int suma_actual = 0;
    long long int suma_tiempo = 0;
    for(int i=0; i<orden.size(); i++){
        suma_tiempo += M[orden[i]];
        suma_actual += suma_tiempo*C[orden[i]];
    }
    return suma_actual;
}

long long int correccionesPendientes(vector<int> &M, vector<int> &C){
    vector<pair<double,int>> t(C.size());
    for(int i=0; i<C.size();i++){
        double descontento_prom = static_cast<double>(C[i]) / M[i]; //calculo el coef de descontento en relación al tiempo
        t[i] = make_pair(descontento_prom,i); //me guardo el resultado junto al número de examen en una tupla
    }
    sort(t.begin(), t.end(), greater<pair<double,int>>()); //ordeno de manera decreciente según el primer valor de la tupla

    vector<int> orden(C.size());
    for(int i=0; i< C.size();i++){
        orden[i] = t[i].second; //orden en el cual se deben corregir los exámenes
    }
    return descontentoTotal(M, C, orden)%1000000007;
}

int main() {
    int tests;
    cin >> tests;

    while(tests>0){
        int N;
        cin >> N; // cantidad de parciales para corregir

        vector<int> M(N);
        vector<int> C(N);

        int min;
        for (int i = 0; i < N; i++) {
            cin >> min; //minutos que tarda en corregir cada parcial
            M[i] = min;
        }

        int coef;
        for (int i = 0; i < N; i++) {
            cin >> coef; //coeficientes de descontento
            C[i] = coef;
        }

        cout << correccionesPendientes(M, C) << endl;
        tests--;
    }
    return 0;
}
