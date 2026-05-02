import os, subprocess

os.system("g++ main.cpp -DTEST -std=c++20 -o main")

for i in range(1000):
    print("Test", i + 1)
    os.system("python gen.py > input.txt")
    p = subprocess.Popen("main.exe", stdout=subprocess.PIPE)
    p.wait()
    if p.returncode != 0:
        print("Input:")
        print(open("input.txt", "r").read())
        break
