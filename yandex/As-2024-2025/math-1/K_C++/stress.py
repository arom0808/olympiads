import os

os.system("g++ main.cpp -std=c++20 -DTEST -o main")
os.system("g++ stupid.cpp -std=c++20 -DTEST -o stupid")

for i in range(1000):
    print("Test", i)
    os.system("python gen.py > input.txt")
    v1 = os.popen("main").read()
    v2 = os.popen("stupid").read()
    if v1 != v2:
        print("Input:")
        print(open("input.txt", "r").read())
        print("Main:")
        print(v1)
        print("Stupid:")
        print(v2)
        break
