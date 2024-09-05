"""
NICOLLE RUIZ QUINTERO 
8974036

PUNTO D -RANK 


NO LO PUDE TERMINAR PERO LA FUNCION ESTAPROX  DEBE VERIFICAR SI ADEMAS DE LAS 4 INMEDIATAS HAY UNA SIGUIENTE PROXIMA Y ASI PARA HACER EL RECORRIDO,
Y QUE LO SUME COMO UNO SOLO ;)

"""

from collections import deque
from sys import stdin
import sys

sys.setrecursionlimit(10**6)

dx, dy = [0, -1, 0, 1], [-1, 0, 1, 0]



def estaProx(idiomas,mapa,vis,x,y):
    ans=False
    for k in range(4):
        nx, ny = x + dx[k], x + dy[k]
        if 0 <= x < len(mapa) and 0 <= y < len(mapa[0]) and mapa[nx][ny] == idiomas and not vis[nx][ny]:
            ans=True
    return ans


def bfsAux(x,y,vis,mapa,idiomas):
    q = deque()
    vis[x][y] = True
    q.append((x, y))
    sumo=1
    ans=estaProx(idiomas,mapa,vis,x,y)
    while len(q) > 0:
        cx, cy = q.popleft()
        print("Nodo = (%d, %d)" % (cx, cy))

        for k in range(4):
            nx, ny = cx + dx[k], cy + dy[k]
            if 0 <= nx < len(mapa) and 0 <= ny < len(mapa[nx]) and not vis[nx][ny]:
                if  mapa[nx][ny]== idiomas:
                    sumo+=1
                    vis[nx][ny] = True
                    q.append((nx, ny))

    return sumo

def bfs(mapa, posiniIdim, idiomas):
    sumadetodas=[]
    vis = [[False for _ in range(len(mapa[i]))] for i in range(len(mapa))]
    for u in range(len(idiomas)):
        sumadetodas.append((idiomas[u],bfsAux(posiniIdim[u][0], posiniIdim[u][1], vis, mapa,idiomas[u])))
    return sumadetodas


def main():
    casos = input()
    for _ in range(len(casos)):
        line=list(map(int, stdin.readline().split()))
        posinix, posiniy = None, None
        matriz = []
        idiomas=[]
        posiniIdim=[]
        for i in range(line[0]):
            fila = stdin.readline().strip()
            matriz.append(list(fila))
        
        for i in range(len(matriz)):
            for j in range(len(matriz[i])):
                if(matriz[i][j] not in idiomas):
                    idiomas.append(matriz[i][j])
                    posiniIdim.append((i,j))
        totalcontador = bfs(matriz,posiniIdim,idiomas)
        totalcontador.sort()
        print("World #",_+1)
        print(totalcontador)
        

        line = list(map(int, stdin.readline().split()))

main()