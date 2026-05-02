import os
from sys import exit

os.system("g++ main.cpp -DTEST -o main")
os.system("g++ stupid.cpp -DTEST -o stupid")

for i in range(1, 4):
    for j in range(1, 4):
        for k in range(1, 4):
            with open("input.txt", "w") as f:
                f.write(str(i) + ' ' + str(j) + ' ' + str(k) + "\n")
            v1 = os.popen("main.exe").read()
            v2 = os.popen("stupid.exe").read()
            if v1 != v2:
                print("Input:")
                print(open("input.txt", "r").read())
                print("Main:")
                print(v1)
                print("Stupid:")
                print(v2)
                exit(0)
