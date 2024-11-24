#include <iostream>
#include <numeric>
#include <algorithm>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <bits/stdc++.h>
using namespace std;


int t;
vector<vector<int>> adj2(50000);
int visitado[50000];
int low[50000];
int padre[50000];
set<pair<int, int>> bridges;
int tamanoTotal;

// ENCONTRAR PUENTES Y COMPONENTES CONEXOS:
vector<pair<pair<int, int>,int>> hijos(50000);

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
                hijos.push_back(make_pair(make_pair(v+1,w+1),tamHijo));
                cout<<"HAY UN PUENTE: "<<v+1<<" - "<<w+1<<endl;
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
            int tamComponente1 = 0;
            for (int j = 0; j < hijos.size(); j++) {
                if ((hijos[j].first.first == u + 1 && hijos[j].first.second == v + 1) || 
                    (hijos[j].first.first == v + 1 && hijos[j].first.second == u + 1)) {
                    tamComponente1 = hijos[j].second;
                    
                }
            }
            int tamComponente2 = tamanoTotal - tamComponente1;
            int impuesto_arista = peso * (tamComponente1 * tamComponente2);

            cout<<"En la arista: "<<u+1<<" - "<<v+1<<" : "<< tamComponente1<<" * "<<tamComponente2<<" = "<<tamComponente1 * tamComponente2<<endl;
            ednPuen.push_back(make_pair(make_pair(u + 1, v + 1), impuesto_arista));
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
            impuestoTotal[u-1]+=impuesto_arista;
        } else {
            impuestoTotal[v-1]+= impuesto_arista;
        }
        cout<<"ENTRE LOS NODOS: "<<u<<" - "<<v<<" : "<<impuestoTotal[u-1]<<" Y "<<impuestoTotal[v-1]<<endl;
    }

    int maxImpuesto=0;
    for (int i=0; i<impuestoTotal.size(); ++i) {
        maxImpuesto= max(maxImpuesto, impuestoTotal[i]);
    }

    return maxImpuesto;
}

// FUNCION DE BB

bool dfs(int nodo, int mid, vector<int>& carga, vector<bool>& visitado, vector<vector<pair<int, int>>>& grafo) {
    visitado[nodo] = true;
    bool ans = true;

    for (pair<int, int>& vecino : grafo[nodo]) {
        int siguiente = vecino.first;
        int impuestoPuente = vecino.second;

        if (!visitado[siguiente]) {
            if (carga[nodo] + impuestoPuente <= mid) {
                carga[nodo] += impuestoPuente;
            }
            else if (carga[siguiente] + impuestoPuente <= mid) {
                carga[siguiente] += impuestoPuente;
            } else {
                ans= false;  
            }

            if (!dfs(siguiente, mid, carga, visitado, grafo)) {
                ans= false;  
            }

            if (carga[nodo] + impuestoPuente > mid) {
                carga[nodo] -= impuestoPuente;
                }
            else if (carga[siguiente] + impuestoPuente > mid) {
                carga[siguiente] -= impuestoPuente;
            }
            
        }
    }

    return ans;
}




bool esPosible(int mid, vector<int>& impuestos, vector<vector<pair<int, int>>>& grafo) {
    int n = impuestos.size();
    vector<int> carga(n, 0);
    vector<bool> visitado(n, false);
    bool ans = true;

    
    for (int i = 0; i < n; i++) {
        carga[i] = impuestos[i];
        if (carga[i] > mid) {
            ans = false;
        }
    }


    vector<int> hojas;
    for (int i = 0; i < n; i++) {
        if (grafo[i].size() == 1) { // Grado 1
            hojas.push_back(i);
        }
    }

    for (int i = 0; i < hojas.size(); ++i) {
        int hoja = hojas[i];
        if (!visitado[hoja]) {
            if (!dfs(hoja, mid, carga, visitado, grafo)) {
                ans = false;
            }
        }
    }

    return ans;
}



// BUSQUEDA BINARIA
int busquedaBinaria(vector<int>& impuestos, vector<pair<pair<int, int>, int>>& ednPuen,vector<vector<pair<int, int>>> &graf) {
    int L= calcularL(impuestos); 
    cout<<L<<endl;
    int R= calcularR(impuestos, ednPuen); 
    cout<<R<<endl;
    int resultado= 0; 
    while (L<=R) {
        int mid= L+(R-L)/ 2;
        cout<<"ESTOY EN MID: "<<mid<<endl;
        if (esPosible(mid, impuestos,graf)) {
            resultado= mid;
            R=mid-1;
            cout<<"ESTOY EN R "<<R<<endl;
        } else {
            L= mid+1;
            cout<<"ESTOY EN L "<<L<<endl;
        }

    }
    cout<<" VALOR DE R: "<<R<<endl;
    cout<<" VALOR DE L: "<<L<<endl;
    

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

        vector<vector<pair<int, int>>> graf(n);
        for (int i = 0; i < ednPuen.size(); ++i) {
            
            int u = ednPuen[i].first.first - 1;   
            int v = ednPuen[i].first.second - 1;  
            int impuestoPuente = ednPuen[i].second;

            
            graf[u].push_back(make_pair(v, impuestoPuente));
            graf[v].push_back(make_pair(u, impuestoPuente));
        }

        
        int resultado=busquedaBinaria(impuestos, ednPuen,graf);

        cout <<"Case #"<<caso<<": The highest tax that must be paid to Emperor Zlatan is "<<resultado<<"."<<endl<<endl;

        for (int i = 0; i < n; i++) {
            adj2[i].clear();
        }
        
    }
    return 0;
}