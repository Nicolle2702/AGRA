/*

NICOLLE RUIZ QUINTERO
8974936

PARCIAL 1 - PUNTO A

REFERENCIAS: 
    CODIGO DE BFS: https://www.cramirez.info/teaching/agra/2024-2 DE LA SECCION EJEMPLOS EN "Implementaciones BFS (08/22)"

*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;


queue<int> encontrarVacio(vector<int> &incidencias,vector<bool> &vis){
    queue<int> vaci;
    for(int i=0; i<incidencias.size(); ++i){
        if(incidencias[i]==0 && vis[i]==false){
            vaci.push(i);
            
        }
    }
    return vaci;
}

int bfsAux(int u,vector<vector<int>> &G, vector<bool> &vis,vector<int> &incidencias){
    vector<int> posiElim;
    queue<int> cola;
    cola.push(u);
    vis[u]=true;
    while( cola.size()> 0){
        int v;
        v= cola.front();
        cola.pop();
        for(vector<int>::iterator it= G[v].begin(); it!=G[v].end();++it){
            int w=*it;
            //cout<< "INCIDENCIA DE LA POSI"<<incidencias[w]<<endl;
            incidencias[w]-=1;
        }
    }
    return 0;
}


vector<pair<int,int>> bfs(vector<vector<int>> &G, vector<int> &incidencias, int numEmp) {
    vector<pair<int,int>> posiElim;
    vector<bool> vis(numEmp, false);
    queue<int> cola= encontrarVacio(incidencias, vis);
    int w = 1;

    while (!cola.empty()) {
        int nivelSize=cola.size();

        for (int i=0; i<nivelSize;++i) {
            int u= cola.front();
            cola.pop();
            if (incidencias[u]==0 && !vis[u]) {
                bfsAux(u, G, vis, incidencias);
                posiElim.push_back(make_pair(w, u));
            }
        }
        cola= encontrarVacio(incidencias, vis);
        w += 1;
    }
    
    return posiElim;
}


int main(){
    int casos;
    cin>>casos;
    int m=1;
    while(casos--){
        int posit=0;
        int numEmp;
        int numRela;
        cin>>numEmp;
        cin>>numRela;
        vector<vector<int>> listaAdya(numEmp);
        vector<int> incidencias (numEmp,0);

        for(int i=0; i<numRela;++i){  // CREACION DE LISTA DE ADYACENCIA Y LISTA DE INCIDENCIAS
            int empleadoA;
            cin>>empleadoA;
            int empleadoB;
            cin>>empleadoB;
            listaAdya[empleadoB].push_back(empleadoA);
            incidencias[empleadoA]+=1;
        }

        // PARTE 2
        vector<pair<int,int>> a;
        a=bfs(listaAdya,incidencias,numRela);  // BFS
    
        // IMPRESION DE RESULTADO
        cout<<"Scenario #"<<m<<":"<<endl;  
        for (vector<pair<int, int>>::iterator it = a.begin(); it != a.end(); ++it) {
            int firstElement = it->first;
            int secondElement = it->second;

            cout<<firstElement<<" "<<secondElement<<endl;
        }
        m+=1;

    }
    return 0;
}