import os
import subprocess

os.system("g++ main.cpp -o main")

while True:
    os.system("python gen.py > input.txt")
    p = subprocess.Popen("main.exe")
    p.wait()
    if p.returncode != 0:
        break
