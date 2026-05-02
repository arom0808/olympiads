import os
#
# maxn, maxexp = 3, 3
#
#
# def gprec(level, maxlevel, arr, cb):
#     global maxexp
#     if level == maxlevel:
#         cb()
#         return
#     for i in range(0, maxexp + 1):
#         arr[level] = i
#         gprec(level + 1, maxlevel, arr, cb)
#
#
# def main():
#     os.system("g++ main.cpp -o main")
#     os.system("g++ stupid.cpp -o stupid")
#     for n in range(1, maxn + 1):
#         for m in range(1, maxn + 1):
#             for k in range(1, n + m + 1):
#                 arr = [0 for i in range(n + m)]
#
#                 def rr():
#                     ff = open("input.txt", "w")
#                     ff.write(f"{n} {m} {k}\n")
#                     ff.write(" ".join(map(str, arr)))
#                     ff.write("\n")
#                     ff.close()
#                     v1 = os.popen("main.exe").read()
#                     v2 = os.popen("stupid.exe").read()
#                     if v1 != v1:
#                         print("Input:")
#                         print(open("input.txt").read())
#                         print("Main output:")
#                         print(v1)
#                         print("Stupid output:")
#                         print(v2)
#                         exit(0)
#
#                 gprec(0, n + m, arr, rr)
#
#
# main()
#
for i in range(1000):
    print("Test", i + 1)
    os.system("python gen.py > input.txt")
    v1 = os.popen("main.exe").read()
    v2 = os.popen("stupid.exe").read()
    if v1 != v1:
        print("Input:")
        print(open("input.txt").read())
        print("Main output:")
        print(v1)
        print("Stupid output:")
        print(v2)
        break
