import os

os.system("g++ stupid.cpp -o stupid")
os.system("g++ main.cpp -o main")

for i in range(1000):
    print("Test", i)
    os.system("python gen.py > input.txt")
    r1 = os.popen("main.exe").read()
    r2 = os.popen("stupid.exe").read()
    if r1 != r2:
        print("Error")
        print("Input:")
        print(open("input.txt", "r").read())
        print("Main:")
        print(r1)
        print("Stupid:")
        print(r2)
        break
