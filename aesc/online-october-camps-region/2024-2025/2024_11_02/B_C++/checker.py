import os

os.system("g++ main.cpp -o main")
os.system("g++ stupid.cpp -o stupid")

for i in range(1000):
    print(f"Test {i + 1}")
    os.system("python gen.py > input.txt")
    v1 = os.popen("main.exe").read()
    v2 = os.popen("stupid.exe").read()
    if v1 != v2:
        print("Error, test:")
        print(open("input.txt", "r").read())
        print("Main:")
        print(v1)
        print("Stupid:")
        print(v2)
        break
