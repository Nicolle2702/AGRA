#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <set>
using namespace std;

// Variables globales
int total;
vector<int> d(50000);
vector<int> p(50000);


void prim(int s,vector<vector<pair<int, int> > > &adj,int n){
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > cola;
    vector<bool> visitado(n, false);
    

    for(int i = 0; i < n; ++i){
        d[i] = INT_MAX;
        p[i] = -1;
    }

    total = 0;
    d[s] = 0;
    cola.push(make_pair(0, s));

    while(!cola.empty()){
        int u = cola.top().second;
        int peso = cola.top().first;
        visitado[u] = true;
        cola.pop();

        if(peso == d[u]){
            total += peso;
            for(int i = 0; i < adj[u].size(); ++i){
                int v = adj[u][i].first;
                int pesoAux = adj[u][i].second;

                if(!visitado[v] && pesoAux < d[v]){
                    p[v] = u;
                    d[v] = pesoAux;
                    cola.push(make_pair(d[v], v));
                }
            }
        }
    }
}


// ENCONTRAR PUENTES:
int numSCC, t;
vector<vector<int> > adj2(50000);
vector<vector<int> > grafoPuente(50000);
int visitado[50000];
int low[50000];
int padre[50000];
set<pair<int, int> > bridges;

void bridgesAux(int);

void bridgesTarjan(int n) {
    fill(visitado, visitado + n, -1);
    fill(low, low + n, -1);
    fill(padre, padre + n, -1);
    bridges.clear();
    t = 0; 
    
    for (int i = 0; i < n; i++) {
        if (visitado[i] == -1)
            bridgesAux(i);
    }
}

void bridgesAux(int v) {
    visitado[v] = low[v] = ++t;

    for (int i = 0; i < adj2[v].size(); i++) {
        int w = adj2[v][i];

        if (visitado[w] == -1) {
            padre[w] = v;
            bridgesAux(w);
            low[v] = min(low[v], low[w]);

            // Verificar si es un puente
            if (low[w] > visitado[v]) {
                bridges.insert(make_pair(v, w));
            }
        } else if (w != padre[v]) {
            low[v] = min(low[v], visitado[w]);
        }
    }
}

// COMPONENTES CONEXOS

//operaciones disjoint set union
//**************************************
int p2[15], rango[15];

void makeSet(int v){
  p2[v] = v;
  rango[v] = 0;
}

int findSet(int v){
  if(v == p2[v])
    return v;
  else{
    p2[v] = findSet(p2[v]);
    return p2[v];
  }
}

void unionSet(int u, int v){
  u = findSet(u);
  v = findSet(v);

  if(u != v){
    if(rango[u] < rango[v])
      swap(u, v);
    
    p2[v] = u;
    if(rango[u] == rango[v])
      rango[u]++;
  }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<int> datos(n);
        vector<vector<pair<int, int>>> camino(n);
        vector<vector<pair<int, int>>> camino2(n);
        
        for(int i = 1; i <= 12; i++){
            makeSet(i);
        }

        for (int i = 0; i < n; i++) {
            cin >> datos[i];
        }

        for (int i = 0; i < m; i++) {
            int a, b, peso;
            cin >> a >> b >> peso;
            camino[a - 1].push_back(make_pair(b - 1, peso));
            camino[b - 1].push_back(make_pair(a - 1, peso));
            adj2[a-1].push_back(b-1);
            adj2[b-1].push_back(a-1);
            makeSet(a);
            makeSet(b);
            unionSet(a,b);
        }

        // Primera llamada a Prim
        prim(0, camino, n);

        cout << "Aristas:" << endl;
        for (int i = 1; i < n; ++i) {
            if (p[i] != -1) {
                cout << "(" << p[i] + 1 << ", " << i + 1 << ")" << endl;
                camino2[p[i]].push_back(make_pair(i, datos[i]));
                camino2[i].push_back(make_pair(p[i], datos[p[i]]));
            }
        }

        // Segunda llamada a Prim
        prim(0, camino2, n);
        
        cout << "Aristas2:" << endl;
        for (int i = 1; i < n; ++i) {
            if (p[i] != -1) {
                 cout << "(" << p[i] + 1 << ", " << i + 1 << ") - Peso: " << d[i] << endl;
            }
        }

        bridgesTarjan(n);
        if(bridges.size() == 0)
            cout << "El grafo no tiene puentes" << endl;
        else{
            cout << "Total de Puentes: " << bridges.size() << endl;
            for(set<pair<int, int> >::iterator it = bridges.begin(); it !=  bridges.end(); ++it)
                cout << " (" << it->first +1 << ", " << it->second +1<< ")";
                cout << endl;
        }

        
    }
    return 0;
}