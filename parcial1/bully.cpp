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
            //cout<<"vacio en "<<i<<endl;
        }
    }
    return vaci;
}

int bfsAux(int u,vector<vector<int>> &G, vector<bool> &vis,vector<int> &incidencias){
    vector<int> posiElim;
    queue<int> cola;
    cola.push(u);
    vis[u] = true;
    while( cola.size()> 0 && incidencias[u]==0){
        int v;
        v= cola.front();
        cola.pop();
        for(vector<int>::iterator it= G[v].begin(); it!=G[v].end();++it){
            int w=*it;
            incidencias[w]-=1;
        }
    }
    return 0;
}


vector<pair<int,int>> bfs(int tam, vector<vector<int>> &G,vector<int> &incidencias,int numEmp){
    vector<pair<int,int>> posiElim;
    vector<bool> vis (numEmp,false);
    queue<int> cola;
    cola=encontrarVacio(incidencias,vis);
    int w=1;
    for(int i=0; i<numEmp;++i){
        if (vis[i]==false && !cola.empty()){
            if(cola.size()==1){
                bfsAux(cola.front(), G, vis,incidencias);
                posiElim.push_back(make_pair(w,cola.front()));
                //cout<<"elemento en el top: "<<cola.front()<<endl;
                w+=1;
                //cout<<"Ranking "<<w<<endl;
                cola.pop();
                
            }
            else if(cola.size()>1){
                bfsAux(cola.front(), G, vis,incidencias);
                posiElim.push_back(make_pair(w,cola.front()));
                //cout<<"2.elemento en el top: "<<cola.front()<<endl;
                cola.pop();
                

            }
            cola=encontrarVacio(incidencias,vis);
            
        }

    }
    return posiElim;
}

int main(){
    int casos;
    cin>>casos;
    int m=1;
    while(casos--){
        vector<int> ordenar;
        vector<int> ranking;
        vector<int> copia;
        map<int, int> id;
        map<int,int> inverso;
        int numEmp;
        int numRela;
        cin>>numEmp;
        cin>>numRela;
        vector<vector<int>> grafoRank(numEmp);
        vector<int> incidencias (numEmp,0);

        for(int i=0; i<numRela;++i){  // GUARDO EN LISTAS
            int empleadoA;
            cin>>empleadoA;
            int empleadoB;
            cin>>empleadoB;
            ordenar.push_back(empleadoA);
            ordenar.push_back(empleadoB);
        }
        // ORDENO
        copia=ordenar;
        sort(ordenar.begin(), ordenar.end()); // Ordeno la lista
        
        // ASIGNACION DE ID Y CREACION DE INCIDENCIAS
        int posit=0;
        for (int i=0; i<ordenar.size(); ++i) {
            if (id.find(ordenar[i]) == id.end()) {
                id[ordenar[i]] = posit;
                inverso[posit] = ordenar[i];
                
                posit++;
            }
        }
        
        // CREACION LISTA ADYACENCIAS E INCIDENCIAS
        for (int i=0; i<copia.size(); i+=2) {
            int k1=copia[i];
            int k2=copia[i + 1];
            grafoRank[id[k2]].push_back(id[k1]);
            incidencias[id[k1]] += 1;
        }

        //IMPRIMIR INCIDENCIAS
        /*for(int i=0; i<incidencias.size();++i){
            cout<<"INCIDENCIAS "<<incidencias[i]<<endl;
        }*/

        // PARTE 2
        vector<pair<int,int>> a;
        int tam;
        tam=grafoRank.size(); // TAMAÑO
        a=bfs(tam,grafoRank,incidencias,numRela);  // BFS

        cout<<"Scenario #"<<m<<":"<<endl;  // IMPRESION
        for (vector<pair<int, int>>::iterator it = a.begin(); it != a.end(); ++it) {
            int firstElement = it->first;
            int secondElement = it->second;
            cout << firstElement << " " << inverso[secondElement] << endl;
        }
        m+=1;


        
    }
    return 0;
}