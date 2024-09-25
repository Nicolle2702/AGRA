#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <set>

using namespace std;

vector<int> topoSortKahn(vector<vector<int>>& G) {
    int n = G.size();
    vector<int> inc(n, 0), topo;
    queue<int> q;

    // Contar el número de entradas para cada nodo
    for (int u = 0; u < n; u++) {
        for (int j = 0; j < G[u].size(); j++) {
            int v = G[u][j];
            inc[v]++;
            cout<<inc[v]<<"incidencia en posi: "<<v<<endl;
        }
    }

    // Agregar a la cola los nodos con 0 entradas
    for (int u = 0; u < n; u++) {
        if (inc[u] == 0) {
            q.push(u);
        }
    }

    // Procesar los nodos
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        cout<<q.front()<<endl;

        for (int j = 0; j < G[u].size(); j++) {
            int v = G[u][j];
            inc[v]--;
            if (inc[v] == 0) {
                q.push(v);
            }
        }
    }

    // Verificar si se encontró un ordenamiento topológico válido
    if (topo.size() != n) {
        topo.clear();  // Si hay un ciclo, limpiar el vector para devolver un vector vacío
    }

    return topo;
}


int main(){
    int n;
    int m;
    cin>>n>>m;
    while(n,m){
        vector<int> ans;
        vector<vector<int>> adj(n);
        for(int i=0; i<m;++i){
            int casa1;
            int casa2;
            cin>>casa1>>casa2;
            adj[casa1].push_back(casa2);
            

        }
        ans=topoSortKahn(adj);

        for (vector<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
            cout << *it << " ";
        }
        cout<<endl;

    }
    return 0;
}