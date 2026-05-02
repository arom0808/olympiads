import os

os.system("g++ stupid.cpp -o stupid")
os.system("g++ main.cpp -o main")

for i in range(1000):
    print("Test", i)
    os.system("python gen.py > input.txt")
    v1 = os.popen("stupid.exe").read()
    v2 = os.popen("main.exe").read()
    if v1 != v2:
        print("Input:")
        print(open("input.txt", "r").read())
        print("Stupid:")
        print(v1)
        print("Main:")
        print(v2)
        break
