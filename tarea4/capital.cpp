#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
#include <stack>
#include <list>
#include <unordered_set>
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

void dfsAux2(int u, vector<vector<int>>& adjT, vector<bool>& vis) {
    vis[u] = true;
      // Incrementar el contador de nodos visitados

    for (int i = 0; i < adjT[u].size(); ++i) {
        int w = adjT[u][i];
        if (!vis[w]) {
            cout<<w<<" VOY AL NODO";
            dfsAux2(w, adjT, vis);  
        }
    }
}

void dfs(vector<vector<int>>& G, vector<vector<int>>& adjT) {
    vector<bool> vis(adjT.size(), false);

    for (int i = 0; i < G.size(); ++i) {
        int scc = G[i][0];  
        if (!vis[scc]) {
            dfsAux2(scc, adjT, vis); 
        }
    }
}

int main(){
    int conex;
    map<int,int> id;
    vector<int> ant;
    vector<int> fin;
    cin>>n; // num tot de nodos
    cin>>conex; // num tot de conexiones


    //while(captot){
        vector<vector<int>> adj (n);
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

            adj[id[cap1]].push_back(id[cap2]);
            adjT[id[cap2]].push_back(id[cap1]);
        }

        kosaraju();

        



        for(list<int>::iterator it = ord.begin(); it != ord.end(); it++){
            int k;
            k= *it;
            cout<<ant[k]<<endl;
        }
        //

        dfs(sccNodos,adjT);


        for (int j= 0; j<sccNodos.size(); j++) {
            cout<<"Capitanía "<<ant[j]<<": ";
            for (vector<int>::iterator it= sccNodos[j].begin(); it!=sccNodos[j].end(); ++it) {
                cout<<ant[*it]<<" ";
            }
            cout<<endl;
        
        }

    //}
    return 0;
}
