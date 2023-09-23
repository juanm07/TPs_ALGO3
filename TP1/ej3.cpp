#include <iostream>
#include <vector>

using namespace std;

int objetivo;

bool ss(vector<int>&vals,int actual,vector<vector<int>>&mem,vector<vector<bool>>&sign,int i,int maxiv){
    int n = vals.size();
    if(i == n){
        return actual == objetivo;
    }
    int suma = actual+vals[i];
    int resta = actual-vals[i];
    if(mem[((suma)/100)+maxiv][i] == -1){
        mem[((suma)/100)+maxiv][i] = ss(vals,suma,mem,sign,i+1,maxiv); //caso en el que sumo el saldo
    }
    if(mem[((resta)/100)+maxiv][i] == -1){
        mem[((resta)/100)+maxiv][i] = ss(vals,resta,mem,sign,i+1,maxiv); //caso donde resto el saldo
    }
    if(mem[((suma)/100)+maxiv][i]) sign[0][i] = true;
    if(mem[((resta)/100)+maxiv][i]) sign[1][i] = true;

    return (mem[((resta)/100)+maxiv][i] || mem[((suma)/100)+maxiv][i]);
}

int main(){
    int tests;
    cin >> tests;

    while (tests > 0) {
        int N;
        cin >> N;

        int W;
        cin >> W;
        objetivo = W;

        vector<int> X(N);

        for (int i = 0; i < N; i++) {
            cin >> X[i];
        }

        int sum= objetivo;
        int resta = objetivo;
        for(int i =0;i<X.size();i++){
            sum+=X[i];
            resta-=X[i];
        }
        vector<char>res;
        vector<vector<bool>>signos(2,vector<bool>(N)); // Matriz de signos. La primera fila es '+' y la segunda es '-'. Voy asignando True en los casos donde sumé/resté el saldo y llegué a mi objetivo
        int max_v = (max(abs(sum),abs(resta)))/100;
        vector<vector<int>>m(((2*max_v)+1),vector<int>(N,-1)); // Matriz de posibles caminos. Si sumando o restando un saldo no llego a mi objetivo, asigno False. En caso de llegar, asigno True.
        ss(X,0,m,signos,0,max_v);
        for(int i = 0;i<N;i++){
            if(signos[0][i] && signos[1][i]){ //Caso donde tanto sumando como restando el saldo llego al objetivo
                res.push_back('?');
            }else{
                if(signos[0][i]){
                    res.push_back('+');
                }else res.push_back('-');
            }
        }

        for (int i = 0; i < res.size(); i++) {
            cout << res[i];
        }
        cout << endl;
        tests--;
    }
    return 0;
}
