import os, sys, subprocess


def main():
    os.system("g++ main.cpp -o main")
    for n in range(2, 201):
        for k in range(1, n + 1):
            if n % k != 0:
                continue
            f = open("input.txt", "w")
            f.write(str(n) + " " + str(k))
            f.close()
            process = subprocess.Popen("main.exe", stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            returncode = process.wait()
            if returncode != 0:
                sys.exit(0)


main()
