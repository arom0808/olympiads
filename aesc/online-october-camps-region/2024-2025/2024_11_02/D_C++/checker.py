import os

os.system("g++ main.cpp -o main")

for i in range(100):
    print("Test", i + 1)
    os.system("python gen.py > input.txt")
    v = os.popen("main.exe").read()
    if v != "":
        print("Input: ")
        print(open("input.txt","r").read())
        print()
        print(v)
        break
