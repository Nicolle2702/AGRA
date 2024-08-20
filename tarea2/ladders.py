from sys import stdin
import math


def laFormula(mid,x,y):

    a = math.sqrt(abs((x*x)- (mid*mid)))
    b = math.sqrt(abs((y*y)- (mid*mid)))

    return ((a*b)/(a+b))

    

def bisectionDouble(f, low, hi, x):
    eps = 1e-9
    ans, wans = None, None

    if low < hi:
        while abs(hi - low) > eps:
            mid = low + ((hi - low) / 2)

            if f(mid) <= x:
                low = mid
            else:
                hi = mid
        ans, wans = f(low), low
    return ans, wans


def main():
    line=stdin.readline().strip()
    lista= []
    while line:
        i=0
        print(line)
        line2=line.split()
        for i in line2:
            lista.append(float(i))
        mid=lista[1]+((lista[0]-lista[1]))/2
        ans,wans=bisectionDouble(laFormula(mid,lista[0],lista[1]),lista[1],lista[0],lista[2])
        print(wans)
        line=stdin.readline()
        
main()