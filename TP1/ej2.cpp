#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
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
    vector<pair<double, int> > t(C.size());
    for(int i=0; i<C.size();i++){
        double descontento_prom = C[i]/M[i];
        t[i] = make_pair(descontento_prom,i);
    }
    sort(t.begin(), t.end(), greater<pair<int, int> >());

    vector<int> orden(C.size());
    for(int i=0; i< C.size();i++){
        orden[i] = t[i].second;
    }
    return descontentoTotal(M, C, orden)%1000000007;
}

int main() {
    int tests;
    std::cin >> tests;

    while(tests>0){
        int N;
        cin >> N; // cantidad de parciales para corregir

        vector<int> M(N);
        vector<int> C(N); 
        
        for (int i = 0; i < N; ++i) {
            cin >> M[i]; // minutos que tarda en corregir cada parcial
        }

        for (int i = 0; i < N; ++i) {
            cin >> C[i]; // coeficientes de descontento
        }

        cout << correccionesPendientes(M, C) << endl;
        tests--;
    }
    return 0;
}
