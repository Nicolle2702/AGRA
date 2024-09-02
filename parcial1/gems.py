"""
NICOLLE RUIZ QUINTERO
8974036

PARCIAL 1 - PUNTO B

REFERENCIAS: 
    CODIGO DE BFSMOD: VIDEO DE CLASE 27 DE AGOSTO 2024 DEL MIN 1:30:00 AL MIN 1:40:00

"""



from collections import deque
from sys import stdin
import sys

sys.setrecursionlimit(10**6)

dx, dy = [0, -1, 0, 1], [-1, 0, 1, 0]
contadorgm=0

def muros(x, y, matriz, vis):
    ans=False
    if 0 <= x < len(matriz) and 0 <= y < len(matriz[0]) and matriz[x][y] != '#' and not vis[x][y]:
        ans=True
    return ans


def bfsMod(mapa, x1, y1):
    global contadorgm
    
    q = deque()
    vis = [[False for _ in range(len(mapa[i]))] for i in range(len(mapa))]
    vis[x1][y1] = True
    q.append((x1, y1))
    while len(q) > 0:
        cx, cy = q.popleft()
        detenerBusqueda = False
        #print("Nodo en la posicion: ", cx, cy)
    
        i=0
        while i < 4 and not detenerBusqueda:
            nx, ny = cx + dx[i], cy + dy[i]
            if muros(nx, ny, mapa, vis) and mapa[nx][ny] == 'T':
                    detenerBusqueda = True
            i+=1

        if not detenerBusqueda:
            for k in range(4):
                nx, ny = cx + dx[k], cy + dy[k]
                if muros(nx, ny, mapa, vis) and mapa[nx][ny] != 'T':
                    q.append((nx, ny))
                    vis[nx][ny] = True
                    if mapa[nx][ny] == 'G':
                        contadorgm += 1
                        #print("Contador de gemas encontrado:", contadorgm)
    
    return contadorgm

def main():
    global contadorgm
    line = list(map(int, stdin.readline().split()))
    
    while line:
        posinix, posiniy = None, None
        matriz = []
        
        for i in range(line[1]):
            fila = stdin.readline().strip()
            matriz.append(list(fila))
        
        for i in range(len(matriz)):
            for j in range(len(matriz[i])):
                if matriz[i][j] == "P" and (posinix is None or posiniy is None):
                    posinix, posiniy = i, j
                
        
        contadorgm = 0
        
        totalcontador = bfsMod(matriz, posinix, posiniy)
        print(totalcontador)
        
        line = list(map(int, stdin.readline().split()))

main()