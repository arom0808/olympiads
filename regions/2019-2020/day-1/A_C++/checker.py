import os

os.system("g++ main.cpp -o main -std=c++20")
os.system("g++ stupid.cpp -o stupid -std=c++20")

for n in range(0, 1025):
    f = open("input.txt", "w")
    f.write(str(n) + "\n")
    f.close()
    r1 = os.popen("main.exe").read()
    r2 = os.popen("stupid.exe").read()
    if r1 != r2:
        print(r1)
        print(r2)
        break
