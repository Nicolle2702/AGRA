"""
NICOLLE RUIZ QUINTERO
8974036

PARCIAL 1 - PUNTO C

REFERENCIAS: 
    CODIGO DE BISECCION: https://www.cramirez.info/teaching/agra/2024-2 DE LA SECCION EJEMPLOS EN Códigos Problemas Online Judge 

"""

from sys import stdin
import sys


def funcion(mid, veloci, segme):
    ans = 0.0
    if veloci + mid > 0:
        ans= segme / (veloci + mid)
    else:
        ans= 1e9
    return ans

def sumatoria(mid, veloci, segme, totsegm):
    suma = 0.0
    for i in range(totsegm):
        suma += funcion(mid, veloci[i], segme[i])
    return suma

def biseccion(veloci, segme, totsegm, tiempotot):
    l=-1e100
    r=1e100
    EPS=1e-8
    while abs(r - l)> EPS:
        mid=(l + r) / 2
        tmp=sumatoria(mid, veloci, segme, totsegm)
        if tmp >tiempotot:
            l=mid
        else:
            r=mid
    return mid  

def main():
    line = list(map(int, sys.stdin.readline().strip().split()))
    while line:
        segme=[]
        veloci=[]
        
        for _ in range(line[0]):
            tmp = list(map(int, input().strip().split()))
            segme.append(tmp[0])
            veloci.append(tmp[1])

        respuesta = biseccion(veloci, segme, line[0], line[1])
        print(format(respuesta, ".6f"))

        line = list(map(int, sys.stdin.readline().strip().split()))

main()