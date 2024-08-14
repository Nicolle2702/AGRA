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



int main(){
    int casos;
    cin>>casos;
    while(casos--){
        int cantCons;
        int cantProd;
        cin>>cantProd>>cantCons;
        vector<int> precioProd;
        vector<int> precioComer;

        for(int i=0; i<cantProd;++i){
            int precioP;
            cout<<"entre 1"<<endl;
            cin>>precioP;
            precioProd.push_back(precioP);
        }
        for(int i=0; i<cantCons;++i){
            int precioC;
            cout<<"entre 2"<<endl;
            cin>>precioC;
            precioComer.push_back(precioC);
        }
        precioProd=sort1(0,precioProd);
        precioComer=sort1(0,precioComer);
        for (vector<int>::iterator it = precioProd.begin(); it != precioProd.end(); ++it){
            cout << *it << endl;
        }

    }



    return 0;
}