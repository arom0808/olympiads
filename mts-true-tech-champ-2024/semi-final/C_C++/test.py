import sys, os

for i in range(int(10000)):
    print('Test', i + 1)
    f = open("input.txt", "w")
    f.write(str(i)+str('\n'))
    f.close()
    v1 = os.popen(f'main.exe').read()
    print(v1)
    if v1 =="1 1\n":
        print("Failed test:")
        print(open("test.txt").read())
        break