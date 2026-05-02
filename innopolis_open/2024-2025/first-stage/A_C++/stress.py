import os, sys

f1 = "stupid.exe"
f2 = "clever.exe"
gen = "gen.py"
iters = 1000

for i in range(int(iters)):
    print('Test', i + 1)
    os.system(f'python {gen} > input.txt')
    v1 = os.popen(f'{f1}').read()
    v2 = os.popen(f'{f2}').read()
    if v1 != v2:
        print("Failed test:")
        print(open("input.txt").read())
        print(f'Output of {f1}:')
        print(v1)
        print(f'Output of {f2}:')
        print(v2)
        break
