#include <iostream>
#include <vector>
using namespace std;
long long INF = 1e17;



long long costo(const vector<int> &puestos, int inicio, int final){
    long long res = 0;

    if(final == puestos.size()){
        for(int i=inicio;i<final;i++) {
            res += abs(puestos[i] - puestos[inicio]);
        }
    }else{
        for(int i=inicio;i<final;i++){
            long long min1 =  abs(puestos[i] - puestos[inicio]);
            long long min2 =  abs(puestos[i] - puestos[final]);
            res += min(min1, min2);
        }
    }
    return res;
}

long long f(int pos_ult,int k,const vector<int>&puestos,vector<vector<long long>>&memo){

    if(k>pos_ult) return memo[pos_ult][k] = INF;
    if(memo[pos_ult][k]==INF){
        if(k==0){
            long long minBase = 0;
            for(int i = 0;i<pos_ult;i++){
                minBase+=abs(puestos[i] - puestos[pos_ult]);
            }
            memo[pos_ult][0] = minBase;
        }else{
            long long mini = INF;
            for(int i = 0; i < pos_ult; i++){
                long long ra =  costo(puestos, i, pos_ult) + f(i, k-1, puestos, memo);
                if(ra<mini) mini = ra;
            }
            memo[pos_ult][k] = mini;
        }
    }

    return memo[pos_ult][k];
}

vector<int> reconstruirSolucion(int pos_ult,int k,const vector<int>&puestos,vector<vector<long long>>&memo,vector<vector<vector<int>>> &memoSols){
    if(k>pos_ult) return memoSols[pos_ult][k] = {};

    if(memoSols[pos_ult][k].empty()){
        if(k==0){
            memoSols[pos_ult][0].push_back(puestos[pos_ult]);
        }else{
            long long mini = INF;
            vector<int> mejorSol;
            for (int i = 0; i < pos_ult; i++) {
                long long ra = costo(puestos, i, pos_ult) + memo[i][k - 1];
                if (ra < mini) {
                    mini = ra;
                    mejorSol = reconstruirSolucion(i, k - 1, puestos, memo, memoSols);
                }
            }

            if (pos_ult < puestos.size()) {
                mejorSol.push_back(puestos[pos_ult]);
            }
            memoSols[pos_ult][k] = mejorSol;
        }
    }
    return memoSols[pos_ult][k];
}



int main() {
    int tests;
    cin >> tests;

    while (tests > 0) {
        int N;
        cin >> N; //cantidad de puestos

        int K;
        cin >> K; //cantidad de proveedurías

        vector<int> puestos(N);
        for (int i = 0; i < N; i++) {
            cin >> puestos[i];
        }

        vector<vector<long long>>memo(N+1,vector<long long>(K+1, INF));
        f(N,K,puestos,memo);

        cout<<memo[N][K]<<endl;

        vector<int>sol;
        vector<vector<vector<int>>> memoSols(N+1,vector<vector<int>>(K+1, sol));
        reconstruirSolucion(N, K,puestos,memo,memoSols);


        for(int l : memoSols[N][K]){
            cout<<l<<" ";
        }
        cout<<endl;
        tests--;
    }
}
