import os, sys

_, f1, f2, gen, iters = sys.argv

os.system(f"g++ {f1}.cpp -o {f1} -std=c++20")
os.system(f"g++ {f2}.cpp -o {f2} -std=c++20")
for i in range(int(iters)):
    print(f"Test {i}")
    os.system(f"python {gen} > input.txt")
    v1 = os.popen(f'{f1}.exe').read()
    v2 = os.popen(f'{f2}.exe').read()
    if v1 != v2:
        print("Failed test:")
        print(open("input.txt").read())
        print(f'Output of {f1}:')
        print(v1)
        print(f'Output of {f2}:')
        print(v2)
        break
