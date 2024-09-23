#include <iostream>
#include <vector>
#include <map>
using namespace std;

void dfsAux2(int ini, int fin, int& suma, vector<vector<int>>& G, vector<bool>& vis) {
    vis[ini] = true;  // Marcamos el nodo actual como visitado

    if (ini==fin) {
        suma++;  // Incrementar el contador de caminos
    }

    for (int w = 0; w < G[ini].size(); ++w) {
        int nexx=G[ini][w];  
        if (!vis[nexx]) {
            dfsAux2(nexx, fin, suma, G, vis);  
        }
    }
    vis[ini]= false;
}
    

int dfs(int ini, int fin, vector<vector<int>>& adj) {
    int suma = 0;
    vector<bool> vis(adj.size(), false);
    dfsAux2(ini, fin, suma, adj, vis);

    return suma;  // Devolver el número total de caminos
}


int main(){

    int habita;
    int pasi;
    int retos;
    int bandera=true;
    cin>>habita>>pasi>>retos;
    while(bandera){
        map<int, int> id;
        vector<int> ant;
        vector<vector<int>> adj(habita);
        int posit = 0;
        for(int i=0; i<pasi;i++){
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

            adj[id[cap1]].push_back(id[cap2]);
            adj[id[cap2]].push_back(id[cap1]);
        }

        for(int i=0; i < retos; ++i){
            int inicio, fin;
            cin>>inicio>>fin;
            if (id.find(inicio) == id.end() || id.find(fin) == id.end()) {
                cout << "N" << endl;
            }
            else{
            int resul=dfs(id[inicio],id[fin],adj);
                if(resul==1){
                    cout<<"Y"<<endl;
                }
                else{
                    cout<<"N"<<endl;
                }
            }
            
        }

        cin>>habita>>pasi>>retos;

        if ( habita==0 && pasi==0 && retos==0){
            bandera=false;
        }

    }
}


