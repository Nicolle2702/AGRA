from sys import stdin, setrecursionlimit
setrecursionlimit(10**6)

G = [[] for _ in range(500000)]
visited = [False for _ in range(500000)]
low = [-1 for _ in range(500000)]
p = [-1 for _ in range(500000)]
bridgesSet = set()
t, n, cont = 0, 0, 0
gDesconectado = [[] for _ in range(500000)]

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

            # Verificar si es un puente
            if low[w] > visited[v]:
                bridgesSet.add((v, w))
        elif w != p[v]:
            low[v] = min(low[v], visited[w])

def dfsAux2(u, G, vis):
    vis[u] = True
    size = 1  
    for w in G[u]:
        if not vis[w]:
            size += dfsAux2(w, G, vis) 
    return size

def dfs(G):
    vis = [False for _ in range(len(G))]
    totSize=0
    comSize = []
    for u in range(len(G)):
        if not vis[u] and G[u]:  
            totSize = dfsAux2(u, G, vis)
            comSize.append(totSize)
    return comSize


def main():
    global n
    
    n, m = map(int, stdin.readline().split())
    while(n,m):
        for _ in range(m):
            u, v = map(int, stdin.readline().split())
            G[u].append(v)
            G[v].append(u)

        bridgesTarjan()

        for i in range(n):  
            for u in G[i]:
                if (u, i) not in bridgesSet and (i, u) not in bridgesSet:
                    gDesconectado[i].append(u)
                    gDesconectado[u].append(i)


        comSize = dfs(gDesconectado)

        totCam = sum(size * (size - 1) // 2 for size in comSize)
        
        combi = (n * (n - 1)) // 2  
        tot = totCam / combi 
        print("{:.5f}".format(tot))
        n, m = map(int, stdin.readline().split())

main()





