from sys import stdin





def form(bisec,v):
    x=v.cos(bisec)
    y=v.sen(bisec)
    

def bisectionDouble(f, low, hi, x):
    eps = 1e-8
    ans, wans = None, None

    if low < hi:
        while abs(hi - low) > eps:
            mid = low + ((hi - low) / 2)
        #print(low, mid, hi)

            if f(mid) <= x:
                low = mid
            else:
                hi = mid
        ans, wans = f(low), low
    return ans, wans


def main():
    line=stdin.readline()
    lista= []
    while(line):
        casos=int(input)
        while(casos>=0):
            alt=float(input)
            d2=float(input)
            lista.append(alt)
            lista.append(d2)
            casos-=1
        
main()