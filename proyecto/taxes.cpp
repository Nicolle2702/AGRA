#include <iostream>
#include <numeric>
#include <algorithm>
#include <climits>
#include <vector>
#include <queue>
#include <set>
using namespace std;


int t;
vector<vector<int>> adj2(50000);
int visitado[50000];
int low[50000];
int padre[50000];
set<pair<int, int>> bridges;
int tamanoTotal;

// ENCONTRAR PUENTES Y COMPONENTES CONEXOS:

void bridgesAux(int v, int& tamSubarbol, vector<pair<pair<int, int>, int>>& ednPuen) {
    visitado[v] = low[v] = ++t;
    tamSubarbol = 1;
    tamanoTotal++;

    for (int i = 0; i < adj2[v].size(); i++) {
        int w = adj2[v][i];

        if (visitado[w] == -1) {
            padre[w] = v;
            int tamHijo = 0;
            bridgesAux(w, tamHijo, ednPuen);
            tamSubarbol += tamHijo;
            low[v] = min(low[v], low[w]);

            if (low[w] > visitado[v]) {
                bridges.insert(make_pair(v, w));
                low[w] = tamHijo;
            }
        } else if (w != padre[v]) {
            low[v] = min(low[v], visitado[w]);
        }
    }
}

void bridgesTarjan(int n, vector<pair<pair<int, int>, int>>& ednPuen, vector<pair<pair<int, int>,int>>& caminos) {
    fill(visitado, visitado + n, -1);
    fill(low, low + n, -1);
    fill(padre, padre + n, -1);
    bridges.clear();
    t = 0;

    for(int i = 0; i < n; i++) {
        if (visitado[i] == -1) {
            tamanoTotal = 0;
            int pabajo = 0;
            bridgesAux(i, pabajo, ednPuen);
        }
    }

    for(vector<pair<pair<int, int>,int>>::iterator it= caminos.begin(); it!= caminos.end(); ++it) {
         int u=it->first.first -1;   
         int v =it->first.second -1;  
         int peso= it->second;
         
        if (bridges.find({u, v})!=bridges.end() || bridges.find({v, u})!=bridges.end()){

            int tamComponente1= low[v];
            int tamComponente2= tamanoTotal-tamComponente1;

            int impuesto_arista = peso* (tamComponente1* tamComponente2);
            ednPuen.push_back(make_pair(make_pair(u+1, v+1), impuesto_arista));
        }
    }   
}

//ENCONTRAR L

int calcularL(vector<int>& impuestos) {
    int low=*max_element(impuestos.begin(), impuestos.end());
    return low;
}

// ENCONTRAR R

int calcularR( vector<int>& impuestos,  vector<pair<pair<int, int>, int>>& ednPuen) {
    vector<int> impuestoTotal(impuestos.size(), 0);
    impuestoTotal=impuestos;

    // Recorro puentes
    for (int i= 0; i< ednPuen.size(); ++i) {
        int u= ednPuen[i].first.first;  
        int v= ednPuen[i].first.second; 
        int impuesto_arista=ednPuen[i].second; 

        // asigno a nodo mas pesado
        if (impuestoTotal[u-1]>= impuestoTotal[v-1]) {
            impuestoTotal[u-1]=impuestoTotal[u-1]+ impuesto_arista;
        } else {
            impuestoTotal[v-1]= impuestoTotal[v-1]+ impuesto_arista;
        }
    }

    int maxImpuesto=0;
    for (int i=0; i<impuestoTotal.size(); ++i) {
        maxImpuesto= max(maxImpuesto, impuestoTotal[i]);
    }

    return maxImpuesto;
}

// FUNCION DE BB

bool esPosible(int mid, vector<int>& impuestos, vector<pair<pair<int, int>, int>>& ednPuen) {
    vector<int> carga(impuestos.size(), 0);
    bool ans=true;
    for (int i=0; i <impuestos.size(); i++) {
        carga[i]=impuestos[i];
        if (carga[i]>mid)  
            ans=false;
    }

    for (int i= 0; i<ednPuen.size(); i++) {
        int u= ednPuen[i].first.first - 1;
        int v= ednPuen[i].first.second - 1;
        int impuestoPuente= ednPuen[i].second;

        if (carga[u]> mid && carga[v]>mid) 
            ans= false;

        if (carga[u]+impuestoPuente<= mid&& carga[u]<=carga[v]) {
            carga[u]+=impuestoPuente;
        } else if (carga[v]+ impuestoPuente <=mid) {
            carga[v]+=impuestoPuente;
        } else {
            ans=false;
        }
    }

    return ans;
}

// BUSQUEDA BINARIA
int busquedaBinaria(vector<int>& impuestos, vector<pair<pair<int, int>, int>>& ednPuen) {
    int L= calcularL(impuestos); 
    int R= calcularR(impuestos, ednPuen); 
    int resultado= R; 

    while (L <= R) {
        int mid= L+(R-L)/ 2;

        if (esPosible(mid, impuestos, ednPuen)) {
            resultado= mid; 
            R=mid-1;
        } else {
            L= mid+1; 
        }
    }

    return resultado; 
}

int main() {
    int n, m;
    int caso = 0;
    while (cin >> n >> m) {
        caso++;
        vector<int> impuestos(n);
        vector<pair<pair<int, int>,int>> caminos; 
        vector<pair<pair<int, int>, int>> ednPuen;


        for (int i=0; i<n; i++) {
            cin >> impuestos[i];
        }

        for (int i=0; i<m; i++) {
            int u, v, l;
            cin>>u>>v>>l;
            caminos.emplace_back(make_pair(u, v),l); 
            adj2[u-1].push_back(v-1);
            adj2[v-1].push_back(u-1);
        }

        bridgesTarjan(n, ednPuen, caminos);

        int resultado=busquedaBinaria(impuestos, ednPuen);

        cout <<"Case #"<<caso<<": The highest tax that must be paid to Emperor Zlatan is "<<resultado<<"."<<endl<<endl;
        
    }
    return 0;
}