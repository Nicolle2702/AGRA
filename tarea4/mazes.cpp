
#include <vector>
#include <stack>
#include <iostream>
#include <map>
#include <set>

using namespace std;

int n, numSCC, t;
vector<vector<int> > adj(50000);
vector<vector<int> > grafoPuente(50000);
int visitado[50000];
int low[50000];
int padre[50000];
set<pair<int, int> > bridges;

void bridgesAux(int);

void bridgesTarjan(){
  int i;

  for(i = 1; i <= n; i++)
    low[i] = visitado[i] = padre[i] =-1;

  for(i = 1; i <= n; i++)
    if(visitado[i] == -1)
      bridgesAux(i);
}

void bridgesAux(int v){
  int w;
  visitado[v] = low[v] = ++t;

  for(int i = 1; i <= adj[v].size(); i++){
    w = adj[v][i];
    if(visitado[w] == -1){
      padre[w] = v;
      bridgesAux(w);
      low[v] = min(low[v], low[w]);

      //verificar si es un puente
        if(low[w] > visitado[v])
	        bridges.insert(make_pair(v, w));
    }
    else if(w != padre[v])
      low[v] = min(low[v], visitado[w]);
  }
}


void dfsAux2(int ini, int fin, int& suma, vector<vector<int>>& G, vector<bool>& vis) {
    vis[ini] = true;  

    if (ini==fin) {
        suma+=1;
    }

    for (int w = 1; w <= G[ini].size(); ++w) {
        int nexx=G[ini][w];  
        if (!vis[nexx]) {
            dfsAux2(nexx, fin, suma, G, vis);  
        }
    }
}
    

int dfs(int ini, int fin, vector<vector<int>>& adj) {
    int suma = 0;
    vector<bool> vis(adj.size(), false);
    dfsAux2(ini, fin, suma, adj, vis);

    return suma;
}

void nuevasVar() {
    bridges.clear();
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        grafoPuente[i].clear();
        visitado[i] = low[i] = padre[i] = -1;
    }
    t = 0;
}

int main(){
    int m, i, aux1, aux2,retos;
    int bandera=true;
    cin >> n >> m >>retos;
    while(bandera){
        if ( n==0 && m==0 && retos==0){
            bandera=false;
        }
        else{
            nuevasVar();
            for(i = 1; i <= m; i++){
                cin >> aux1 >> aux2;
                adj[aux1].push_back(aux2);
                adj[aux2].push_back(aux1);
            }

            bridgesTarjan();
            
            for (set<pair<int, int>>::iterator it = bridges.begin(); it != bridges.end(); ++it) {
                int u = it->first;
                int v = it->second;
                grafoPuente[u].push_back(v);
                grafoPuente[v].push_back(u);
            }

            for(int i=1; i <= retos; ++i){
                    int inicio, fin;
                    cin>>inicio>>fin;
                    int resul=dfs(inicio,fin,grafoPuente);
                    if(resul==1){
                        cout<<"Y"<<endl;
                    }
                    else{
                        cout<<"N"<<endl;
                    }
            }
            
            cin>>n>>m>>retos; 
            if ( n!=0 && m!=0 && retos!=0){
                cout<<"-"<<endl;
            }
        }

    }
    return 0;
}