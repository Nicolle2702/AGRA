
/*
NICOLLE RUIZ QUINTERO 
8974036

CODIGO DE SORT: https://www.cramirez.info/teaching/agra/2024-2 DE LA SECCION EJEMPLOS EN " Código Ejemplos Dividir y Conquistar"
BUSQUEDA BINEARIA: https://www.cramirez.info/teaching/agra/2021-2 DE LA SECCION EJEMPLOS EN "Búsqueda Binaria"

*/


#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;


int getMin(int l, vector<int> &arg1){
    int ans = l;
    while (l < arg1.size()){
        if (arg1[l] < arg1[ans]){
            ans = l;
            }
        l += 1;
    }
    return ans;
}


vector<int> sort1(int l, vector<int> &arg1){
    int m;
    if (l != arg1.size() - 1){
        m = getMin(l, arg1);
        int temp1= arg1[l];
        int temp2= arg1[m];
        arg1[m]= temp1;
        arg1[l] = temp2;
        sort1(l + 1, arg1);
    }
    return arg1;
}


int binsearch(vector<int> &A, int x){
    int low = 0;
    int hi = A.size();
    while (low < hi) {
        int mid = low + (hi - low) / 2;
        if (A[mid] < x) {
            low = mid + 1;
        } else {
            hi = mid;
        }
    }
    
    return low;
}

pair<int, int> encontrarMenor(vector<pair<int, int>>& enojos) {
    pair<int, int> minPair = enojos[0]; 

    for (vector<pair<int, int>>::iterator it = enojos.begin(); it != enojos.end(); ++it) {
        pair<int, int>& p = *it;
        if (p.second < minPair.second || (p.second == minPair.second && p.first < minPair.first)) {
            minPair = p;
        }
    }

    return minPair;
}


pair<int, int> recorro(vector<int> &precioProd, vector<int> &precioComer){
    int ans=0;
    int enojaos;
    vector<pair<int,int>> enojos;
    int a=precioProd.size();
    int xd=precioProd.size();
    for(vector<int>::iterator it =precioProd.end()-1 ; it >=precioProd.begin() ; --it){
        int persoEnoj;
        int posi;
        posi=binsearch(precioComer,*it);
        persoEnoj= posi+(xd-a);
        enojos.push_back(make_pair(*it,persoEnoj));
        --a;
    }
    pair<int, int> resultados=encontrarMenor(enojos);



    return resultados;
}



int main(){
    int casos;
    cin>>casos;
    while(casos--){
        int valor,enojaoss;
        int cantCons;
        int cantProd;
        cin>>cantProd>>cantCons;
        vector<int> precioProd;
        vector<int> precioComer;
        precioProd.push_back(0);
        for(int i=0; i<cantProd;++i){
            int precioP;
            cin>>precioP;
            precioProd.push_back(precioP);
        }
        for(int i=0; i<cantCons;++i){
            int precioC;
            cin>>precioC;
            precioComer.push_back(precioC);
        }
        precioProd=sort1(0,precioProd);
        precioComer=sort1(0,precioComer);
        pair<int, int> resultado=recorro(precioProd,precioComer);

        cout<<resultado.first<<" "<<resultado.second<<endl;
    }



    return 0;
}