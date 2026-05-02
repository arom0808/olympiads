import sys, os

os.system("g++ main.cpp -o main -std=c++17")
os.system("g++ stupid.cpp -o stupid -std=c++17")

for i in range(100):
    print("Test", i + 1)
    os.system("python gen.py > input.txt")
    v1 = os.popen("main.exe").read()
    v2 = os.popen("stupid.exe").read()
    if v1 != v2:
        print("Failed test:")
        print(open("input.txt").read())
        print('Output of main:')
        print(v1)
        print('Output of stupid:')
        print(v2)
