#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
#include <stack>
using namespace std;



int main(){
    int captot;
    int conex;
    map<int,int> id;
    vector<int> ant;
    cin>>captot; // num tot de nodos
    cin>>conex; // num tot de conexiones

    //while(captot){
        vector<vector<int>> ady (captot);
        int posit=0;
        for(int i=0; i<conex;i++){
            int cap1;
            cin>>cap1;
            int cap2;
            cin>>cap2;
            if (id.find(cap1)==id.end()) {
                id[cap1]= posit;
                ant.push_back(cap1);
                posit++;
            }
            if (id.find(cap2)==id.end()) {
                id[cap2]= posit;
                ant.push_back(cap2);
                posit++;
            }

            ady[id[cap1]].push_back(id[cap2]);
        }

        tarjan(ady);

        for (int j= 0; j<ady.size(); j++) {
            if (j<ant.size()) {
                cout<<"Capitanía "<<ant[j]<<": ";
                
                for (vector<int>::iterator it= ady[j].begin(); it!=ady[j].end(); ++it) {
                    cout<<ant[*it]<<" ";
                }
                cout<<endl;
            }
        }

    //}
    return 0;
}
