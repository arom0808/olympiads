import os

os.system("g++ main.cpp -DTEST -o main")
os.system("g++ stupid.cpp -DTEST -o stupid")

for i in range(1000):
    print("Test", i + 1)
    os.system("python gen.py > input.txt")
    v1 = os.popen("main.exe").read()
    v2 = os.popen("stupid.exe").read()
    if v1 != v2:
        print("Input:")
        print(open("input.txt", "r").read())
        print("Main")
        print(v1)
        print("Stupid")
        print(v2)
        break
