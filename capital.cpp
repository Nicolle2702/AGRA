#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;


int main(){
    int captot;
    int conex;
    cin>>captot;
    cin>>conex;

    //while(captot){
        vector<vector<int>> ady (conex);
        for(int i=0; i<conex;i++){
            int cap1;
            cin>>cap1;
            int cap2;
            cin>>cap2;
            cout<<"entre1"<<endl;
            ady[cap1].push_back(cap2);
            cout<<"pase el ady"<<endl;
        }
        int j=0;
        for (vector<vector<int>>::iterator fila = ady.begin(); fila != ady.end(); ++fila) {
            for (vector<int>::iterator elemento = fila->begin(); elemento != fila->end(); ++elemento) {
                cout << *elemento << " "; // Sin std:: en cout
            }
            j+=1;
            cout << endl;
        }

    //}
    return 0;
}
