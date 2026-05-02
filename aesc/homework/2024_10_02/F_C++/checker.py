import os, sys


def main():
    os.system("g++ main.cpp -o main")
    res = []
    for k in range(3, 10):
        for mut_cnt in range(1, 6):
            for best_part in range(2, 9, 2):
                f = open("input.txt", "w")
                f.write(str(k) + " " + str(mut_cnt) + " " + str(0.1 * best_part) + "\n")
                f.close()
                s = 0
                for i in range(3):
                    v = os.popen(f'main.exe').read()
                    print(int(v))
                    s += int(v)
                res.append((s, k, mut_cnt, best_part))
    res.sort(key=lambda x: x[0])
    r = open("results.txt", "w")
    for ee in res:
        r.write(str(ee[0]) + " " + str(ee[1]) + " " + str(ee[2]) + " " + str(ee[3]) + "\n")
    r.close()


main()
