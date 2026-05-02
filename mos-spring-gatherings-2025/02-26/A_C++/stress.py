import os


def check_vs(v1, v2):
    s1 = v1.split('\n')
    s2 = v2.split('\n')
    if s1[0] != s2[0]:
        return False
    return True
    # rs = v1[2]
    # ts = map(int, v1[4].split(" "))
    # if ts[0] <= 0:
    #     return False
    # for i in range(len(ts) - 1):
    #     if i & 1:
    #         if ts[i] >= ts[i + 1]:
    #             return False
    #     else:
    #         if ts[i] <= ts[i + 1]:
    #             return False
    # if not (len(ts)&1)
    # ms = []
    # pos = 0
    # dir = True

    # ins = open("input.txt", "r").read().split("\n")[2]


os.system("g++ main.cpp -DTEST -o main")
os.system("g++ stupid.cpp -DTEST -o stupid")

for i in range(1000):
    print("Test", i)
    os.system("python gen.py > input.txt")
    v1 = os.popen("main.exe").read()
    v2 = os.popen("stupid.exe").read()
    if not check_vs(v1, v2):
        print("Input:")
        print(open("input.txt", "r").read())
        print("Main")
        print(v1)
        print("Stupid")
        print(v2)
        break
