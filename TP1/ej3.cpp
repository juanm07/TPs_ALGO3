#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> comb_posibles;
vector<char> res;
vector<int> valores;

void combinacionFinal() {
    int N = comb_posibles[0].size();
    res = comb_posibles[0];
    for (int j = 0; j < N; j++) {
        for (int i = 1; i < comb_posibles.size(); i++) {
            if (comb_posibles[i][j] != res[j]) {
                res[j] = '?';
                break;
            }
        }
    }
}

void saldosSospechosos(int W, vector<char> &comb_actual, int i) {
    if (i == valores.size()) {
        if (W == 0) {
            comb_posibles.push_back(comb_actual);
        }
        return;
    }
    comb_actual.push_back('+');
    saldosSospechosos(W + valores[i], comb_actual, i + 1);
    comb_actual.pop_back();
    comb_actual.push_back('-');
    saldosSospechosos(W - valores[i], comb_actual, i + 1);
    comb_actual.pop_back();
}

int main() {
    int tests;
    cin >> tests;

    while (tests > 0) {
        int N;
        cin >> N;

        int W;
        cin >> W;

        vector<int> X(N);

        for (int i = 0; i < N; i++) {
            cin >> X[i];
        }

        vector<char> comb_actual;
        valores = X;
        saldosSospechosos(W, comb_actual, 0);

        combinacionFinal();

        for (int i = N-1; i >= 0; i--) {
            cout << res[i];
        }
        cout << endl;
        tests--;
    }
    return 0;
}
