import os, sys

_, f1, f2, gen, iters = sys.argv
# первый аргумент это название программы, "checker.py",
# поэтому "забудем" его с помощью "_"

os.system(f'g++ {f1}.cpp -o {f1}')
os.system(f'g++ {f2}.cpp -o {f2}')
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

# _, f, ofn, gen, iters = sys.argv
# os.system(f'g++ {f}.cpp -o {f}')
# with open(ofn, "w") as o_f:
#     for i in range(int(iters)):
#         os.system(f'python {gen} > test.txt')
#         v1 = os.popen(f'{f}').read()
#         o_f.write(open("test.txt").read())
#         o_f.write("\n")
#         o_f.write(v1)
#         o_f.write("\n\n")
