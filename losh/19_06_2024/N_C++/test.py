import os, sys

_, f1, f2, gen, iters = sys.argv
# первый аргумент это название программы, "checker.py",
# поэтому "забудем" его с помощью "_"

for i in range(int(iters)):
    print('Test', i + 1)
    os.system(f'python {gen} > test.txt')
    v1 = os.popen(f'{f1}').read()
    v2 = os.popen(f'{f2}').read()
    if v1 != v2:
        print("Failed test:")
        print(open("test.txt").read())
        print(f'Output of {f1}:')
        print(v1)
        print(f'Output of {f2}:')
        print(v2)
        break
