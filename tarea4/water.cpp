#include <vector>
#include <list>
#include <iostream>

using namespace std;

int n;
vector<vector<int> > adj(500, vector<int>());
vector<vector<int> > adjT(500, vector<int>());
bool visitados[500];
list<int> ord;
int sccInd[500];
int numScc;
vector<vector<int>> sccNodos;

void kosarajuAux(int);
void asignar(int, int);

void kosaraju(){
    int i, num = 0;

    for(i = 0; i < n; i++)
        visitados[i] = false;

    for(i = 0; i < n; i++)
        if(!visitados[i])
        kosarajuAux(i);

    for(i = 0; i < n; i++)
        sccInd[i] = -1;

    for(list<int>::iterator it = ord.begin(); it != ord.end(); it++){
        if(sccInd[*it] == -1){
            numScc++;
            sccNodos.push_back(vector<int>());
            asignar(*it, num++);
        }
    }
}

void kosarajuAux(int v){
    visitados[v] = true;

    for(int i = 0; i < adj[v].size(); i++)
        if(!visitados[adj[v][i]])
            kosarajuAux(adj[v][i]);

    ord.push_front(v);
}

void asignar(int u, int num){
    sccInd[u] = num;
    sccNodos[sccNodos.size() -1].push_back(u);
    for(int i = 0; i < adjT[u].size(); i++){
        if(sccInd[adjT[u][i]] == -1)
            asignar(adjT[u][i], num);
    }
}


void dfsAux2(int u, vector<vector<int>> &G, vector<bool> &vis){
    int w, i;
    vis[u] = true;
    printf("%d\n", u);
    for(i = 0; i < G[u].size(); ++i){
        w = G[u][i];
        cout<<w<<" :ESTOY RECORRIENDO EN"<<endl;
        if(!vis[w])
            dfsAux2(w, G, vis);
        }
    }


int main(){
    int m, i, u, v,contConex=0;

    cin >> n >> m;
    for(i = 0; i < m; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adjT[v].push_back(u);
    }

    kosaraju();
    cout<<sccNodos.size();
    for(i = 0; i < m; i++){
        cout << sccInd[i] << " ";
    }
    vector<vector<int>> grafoNuevo(sccNodos.size());
    for (int u=0; u<m; ++u) {
        for (int k=0; k<adj[u].size(); ++k) {
            int v= adj[u][k];  
            
            int sccU=sccInd[u];  
            int sccV=sccInd[v];  
            
            if (sccU!=sccV) {
                cout<<"Hay conexion entre "<<v<<"Y "<<u<<endl;
                grafoNuevo[sccU].push_back(sccV);  
            }
        }
    }
    for (int j= 0; j<sccNodos.size(); j++) {
        cout<<"SCC "<<j<<": ";
        for (vector<int>::iterator it= sccNodos[j].begin(); it!=sccNodos[j].end(); ++it) {
            cout<<*it<<" ";
        }
        cout<<endl;
    }
    

    vector<bool> vis(grafoNuevo.size(), false);
    dfsAux2(sccInd[0], grafoNuevo, vis);
    for(int i=0; i< vis.size(); ++i){
        if(vis[i]==false){
            contConex+=1;
        }
    }

    cout<<"CANTIDAD MINIMA DE CONEX "<<contConex<<endl;

    cout << endl;
    
    return 0;
}