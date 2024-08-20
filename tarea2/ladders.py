from sys import stdin

def main():
    line=stdin.readline()
    lista= []
    while line:
        i=0
        print(line)
        for i in line:
            lista.append(i)
        line=stdin.readline()
main()