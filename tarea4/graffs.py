

from sys import stdin
import sys
sys.setrecursionlimit(10**6)

G = [[] for _ in range(500000)]
visited = [False for _ in range(500000)]
low = [-1 for _ in range(500000)]
p = [-1 for _ in range(500000)]
bridgesSet = set()
t, n,cont = int(), int(),int()
totalPares= int()
sizeB, size= int(),int()
gDesconectado= [[] for _ in range(500000)]

def bridgesTarjan():
    global low, visited, p
    for i in range(n):
        low[i] = visited[i] = p[i] = -1

    for i in range(n):
        if visited[i] == -1:
            bridgesAux(i)

def bridgesAux(v):
    global low, visited, p, bridgesSet, t
    t += 1
    visited[v] = low[v] = t

    for w in G[v]:
        if visited[w] == -1:
            p[w] = v
            bridgesAux(w)
            low[v] = min(low[v], low[w])

            #verificar si es un puente
            if low[w] > visited[v]:
                bridgesSet.add((v, w))
                
        elif w != p[v]:
            low[v] = min(low[v], visited[w])

def dfsAux(u, G, vis):
    global size
    vis[u] = True
    size+=1
    for w in G[u]:
        if not vis[w]:
            dfsAux(w, G, vis)
    return size


def main():
    global G, n, totalPares,sizeB,cont,gDesconectado,visited,low,p,t,size,bridgesSet
    
    n, m = map(int, stdin.readline().split())
    while(n,m):
        
        for i in range(m):
            u, v = map(int, stdin.readline().split())
            G[u].append(v)
            G[v].append(u)

        bridgesTarjan()

        for i in range(m):
            for u in G[i]:
                if (u,i) not in bridgesSet and (i,u) not in bridgesSet and (u,i):
                    gDesconectado[i].append(u)
                    gDesconectado[u].append(i)

        vis = [False for _ in range(len(gDesconectado))]
        nodosFaltantes=n
        for u, v in bridgesSet:
            if not vis[u]:
                size1=dfsAux(u,gDesconectado,vis)
                sizeB = nodosFaltantes - size1
                #print(size1, "SIZE 1")
                #print(sizeB ,"SIZE B")
                totalPares += size1 * sizeB
                nodosFaltantes-=size1
            #print(totalPares, "Total Pares")
            #print (bridgesSet)
        combi= ((n-1)*n)/2
        tot=totalPares/combi
        print("{:.5f}".format(tot))

        G = [[] for _ in range(500000)]
        visited = [False for _ in range(500000)]
        low = [-1 for _ in range(500000)]
        p = [-1 for _ in range(500000)]
        bridgesSet = set()
        t, n,cont = int(), int(),int()
        totalPares= int()
        sizeB, size= int(),int()
        gDesconectado= [[] for _ in range(500000)]
        
        n, m = map(int, stdin.readline().split())

main()




