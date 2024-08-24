#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;




vector<int> bfsAux(int u,vector<vector<int>> &G, vector<bool> &vis){
    vector<int> pos;
    queue<int> cola;
    vis[u] = true;
    cola.push(u);
    while( cola.size()> 0){
        int v;
        v= cola.front();
        cola.pop();
        cout<<v<<endl;
        pos.push_back(v);
        for(vector<int>::iterator it= G[v].begin(); it!=G[v].end();++it){
            int w=*it;
            if(vis[w]==false){
                vis[w]=true;
                cola.push(w);
            }
        }
    }
    return pos;
}

vector<int> bfs(int tam, vector<vector<int>> &G){
    vector<int> pos;
    vector<bool> vis (tam,false);
    for(int i=0; i<G.size();++i){
        if (vis[i]==false){
            pos=bfsAux(i, G, vis);
        }
    }
    return pos;
}

int bfsAux2(int u,vector<vector<int>> &G,int tam){
    vector<int> rankorden (tam);
    queue<int> cola;
    cola.push(u);
    while( cola.size()> 0){
        int v;
        v=cola.front();
        cola.pop();
        rankorden.push_back(v);
        cout<<v<<endl;
        for(vector<int>::iterator it= G[v].begin(); it!=G[v].end();++it){
            int w=*it;
            if(){
                vis[w]=true;
                cola.push(w);
            }
        }
    }
    return 0;
}

int bfs2(int tam, vector<vector<int>> &G){
    vector<bool> vis (tam,false);
    for(int i=0; i<G.size();++i){
        bfsAux(i, G,tam);
    }
    return 0;
}

/*vector<int>ordenGrafo(vector<int> &a,vector<vector<int>> &grafoRank){

    return 0;
}*/

int main(){
    int casos;
    cin>>casos;
    while(casos--){
        vector<int> ranking;
        int numEmp;
        int numRela;
        cin>>numEmp;
        cout<<"hola 2"<<endl;
        cin>>numRela;
        cout<<"Hola 1"<<endl;
        vector<vector<int>> grafoRank(numEmp);
        for(int i=0; i<numRela;++i){
            cout<<"entre al ciclo"<<endl;
            int empleadoA;
            cin>>empleadoA;
            int empleadoB;
            cin>>empleadoB;
            grafoRank[empleadoB].push_back(empleadoA);
            cout<<"paso el insert"<<i<<endl;
        }
        //ranking=ordenGrafo(grafoRank)
        vector<int> a;
        int tam;
        tam=grafoRank.size();
        a=bfs(tam,grafoRank);
        //ranking=ordenGrafo(a,grafoRank)
        cout<<"Scenario #1:"<<endl;
        for(vector<int>::iterator it= a.begin(); it!= a.end();++it){
            int k;
            k= *it;
            cout<<k<<endl;
        }
    }
    return 0;
}