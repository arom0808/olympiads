import os, sys, subprocess
from random import randint


def main():
    os.system("g++ main.cpp -o main")
    while (True):
        n = randint(2, 6)
        k = 0
        while 2 ** k < n:
            k += 1
        k = randint(k, n)
        g = [[0 for _ in range(n)] for __ in range(n)]
        for i in range(n):
            for j in range(i + 1, n):
                g[i][j] = g[j][i] = randint(1, 2)
        f = open("input.txt", "w")
        f.write(str(n) + " " + str(k) + "\n")
        for row in g:
            f.write(" ".join(map(str, row)))
            f.write("\n")
        f.close()
        process = subprocess.Popen("main.exe", stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        returncode = process.wait()
        if returncode != 0:
            sys.exit(0)


main()
