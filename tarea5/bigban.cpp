#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>


using namespace std;


bool bellmanFordMoore(vector<vector<pair<int, int>> &G, int s, vector<int> &dist, vector<int> &pred){
    int N = G.size();
    dist.assign(N, 10001);
      pred.assign(N, -1);
      dist[s] = 0;
      int i = 0;
      int v;
    int duv; 
      while (i < N - 1) {
        for (int u = 0; u < N; ++u) {
            for (const auto &edge : G[u]) {
                v = edge.first;
                duv = edge.second; 
                if (dist[u] + duv < dist[v]) {
                    dist[v] = dist[u] + duv;
                    pred[v] = u;
                }
            }
        }
        i++;
    }
    int u = 0;
    bool ans  = false;
    while (u < N && !ans) {
        int j = 0;
        while (j < G[u].size() && !ans) {
            int v = G[u][j].first;
            int duv = G[u][j].second;
            if (dist[u] + duv < dist[v]) {
                ans = true;
            }
           j++;
        }
        u++;
    }
    return ans;
}

int main(){
    int c;
    int i=0;
    cin>> c;
    while(i<c){
        bool resul;
        int n; // nodos
        int m; // aristas
        vector<pair<int,int>> adj(n);
        cin>>n>>m;
        for(int j=0; j<m; ++j){
            int n1;
            int n2;
            int p;
            cin>>n1>>n2>>p;
            adj[n1].emplance_back(n2,p);
        }
        
        vector<int>dist;
        vector<int> pred;
        resul=bellmanFordMoore(adj,0,dist,pred);
        i++;
    }
    return 0;
}