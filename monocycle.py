
from collections import deque
from sys import stdin
import sys

from collections import deque

dx, dy = [0, -1, 0, 1], [-1, 0, 1, 0]

def muros(x, y, matriz, vis):
    ans=False
    if 0 <= x < len(matriz) and 0 <= y < len(matriz[0]) and matriz[x][y] != '#' and not vis[x][y]:
        ans=True
    return ans

# Implementación con un único origen s
def ssspBFS(G, x1, y1, x2, y2):
    
    q = deque()
    vis = [[False for _ in range(len(G[i]))] for i in range(len(G))]
    d = [[float("inf") for _ in range(len(G[i]))] for i in range(len(G))]
    p = [[-1 for _ in range(len(G[i]))] for i in range(len(G))]
    
    q.append((x1, y1))
    vis[x1][y1] = True
    d[x1][y1] = 0
    

    while len(q) > 0:
        cx, cy = q.popleft()
        detenerBusqueda = False
        nobusco = True
        i=0

        if G[cx][cy] == "T":
            nobusco = False


        for k in range(4):
            nx, ny = cx + dx[k], cy + dy[k]
            
            if muros(nx, ny, G, vis):
                vis[nx][ny] = True
                d[nx][ny] = d[cx][cy] + 1
                p[nx][ny] = (cx, cy)
                q.append((nx, ny))

    print("hola")
    return d, p

def main():
    line = list(map(int, stdin.readline().split()))
    m,n=line[0],line[1]
    while line:
        print(m,n,"hola")
        posinix, posiniy, posfinx, posfiny = None, None,None,None
        matriz = []
        
        for i in range(line[0]):
            fila = stdin.readline().strip()
            matriz.append(list(fila))
        
        for i in range(len(matriz)):
            for j in range(len(matriz[i])):
                if matriz[i][j] == "S" and (posinix is None or posiniy is None):
                    posinix, posiniy = i, j
                if matriz[i][j] == "T" and (posinix is None or posiniy is None):
                    posfinx, posfiny = i, j
        
        totalcontador,p = ssspBFS(matriz, posinix, posiniy,posfinx, posfiny)
        print(totalcontador)
        line = list(map(int, stdin.readline().split()))

main()