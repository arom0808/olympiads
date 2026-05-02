import os, sys, subprocess

_, f1, gen, iters = sys.argv
# первый аргумент это название программы, "checker.py",
# поэтому "забудем" его с помощью "_"

os.system(f'g++ {f1}.cpp -o {f1}')

for i in range(int(iters)):
    print('Test', i + 1)
    os.system(f'python {gen} > test.txt')
    v1 = subprocess.run([f1]).returncode
    # v2 = os.popen(f'./{f2} < test.txt').read()
    if v1 != 0:
        print("Failed test:")
        print(open("test.txt").read())
        # print(f'Output of {f1}:')
        # print(v1)
        # print(f'Output of {f2}:')
        # print(v2)
        break
