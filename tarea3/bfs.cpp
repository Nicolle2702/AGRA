/*
BFS EN C++

*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;


int bfsAux(int u,vector<vector<int>> &G, vector<bool> &vis){
    
    queue<int> cola;
    vis[u] = true;
    cola.push(u);
    while( cola.size()> 0){
        int v;
        v= cola.front();
        cola.pop();
        cout<<v<<endl;

        for(vector<int>::iterator it= G[v].begin(); it!=G[v].end();++it){
            int w=*it;
            if(vis[w]==false){
                vis[w]=true;
                cola.push(w);
            }
        }
    }
    return 0;
}

int bfs(int tam, vector<vector<int>> &G){
    vector<bool> vis (tam,false);
    for(int i=0; i<G.size();++i){
        if (vis[i]==false){
            bfsAux(i, G, vis);
        }
    }
    return 0;
}