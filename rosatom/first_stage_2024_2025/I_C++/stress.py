import os

os.system("g++ main.cpp -o main")

for i in range(1000):
    print("Test", i + 1)
    os.system("python gen.py")
    os.system("main.exe")
    v = os.popen("python check.py").read().rstrip('\n')
    if v != "0":
        print(v)
        break
