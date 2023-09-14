
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int casos;
int cantPuestos;
int cantProvs;
vector<int> ubicacionLocales;
vector<int> ubicacionProvs;
vector<vector<int>> pd; // Matriz de memoización

int choripanes(int ultProv, int i, int k, vector<int> & v) {
    if (i == cantPuestos) {
        if (k == 0) {
            return 0;
        } else {
            return INF;
        }
    }
    if (i != cantPuestos && k == 0) {
        int suma =0;
        int j = i;
        while (j < cantPuestos){
            suma = suma + ubicacionLocales[j]- ultProv;
            j++;

        }
        return suma;
    }
    if (pd[i][k-1] != -1) {
        return pd[i][k-1];
    }

    int noColocar = ubicacionLocales[i +1] - ubicacionLocales[i] + choripanes(ultProv,i + 1, k, v);
    ultProv = i;
    v[k-1] = ubicacionLocales[ultProv];
    ubicacionProvs =v;
    int colocar = choripanes(ultProv,i+1, k-1,v);

    pd[i][k-1] = min(noColocar, colocar);
    return pd[i][k-1];
}

int main() {
    cin >> casos;

    for (int i = 0; i < casos; i++) {
        cin >> cantPuestos >> cantProvs;

        ubicacionLocales.resize(cantPuestos);
        ubicacionProvs.resize(cantProvs);
        pd.assign(cantPuestos , vector<int>(cantProvs , -1));

        for (int j = 0; j < cantPuestos; j++) {
            cin >> ubicacionLocales[j];
        }

        int sol = choripanes(0,0, cantProvs, ubicacionProvs);

        cout << sol << endl;
        for(int j=0; j < cantProvs; j++){
            cout << ubicacionProvs[j] << " " ;
        }
    }

    return 0;
}
