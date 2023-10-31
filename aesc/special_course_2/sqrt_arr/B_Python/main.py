# from matplotlib import pyplot as plt
#
#
# def f(x, y):
#     return ((((-8)/5)*x+8-y-abs(((-8)/5)*x+8-y))**2+((8/5)*x+8-y-abs((8/5)*x+8-y))**2+((5/10)*x-3-y+abs((5/10)*x-3-y))**2)*(((6/10)*x-3-y+abs((6/10)*x-3-y))**2+((-6/10)*x-3-y+abs((-6/10)*x-3-y))**2+(y-3+abs(y-3))**2)*(((-5/10)*x-3-y+abs((-5/10)*x-3-y))**2+((-16/10)*x+8-y-abs((-16/10)*x+8-y))**2+((5/18)*x-(20/9)-y-abs((5/18)*x-(20/9)-y))**2)
#
#
# def main():
#     xs, ys = [], []
#     for dx in range(-400, 400, 1):
#         x = dx / 40
#         for dy in range(-400, 400, 1):
#             y = dy / 40
#             if f(x, y) == 0:
#                 xs.append(x)
#                 ys.append(y)
#     plt.xlim(-11, 11)
#     plt.ylim(-11, 11)
#     plt.scatter(xs, ys)
#     plt.show()
#
#
# main()
#
# # (abs(1 - x**2 - y**2 - abs(1 - x**2 - y**2)) + abs(2 - 2*x - y - abs(2 - 2*x - y)) + abs(y + 1 / 2 - abs(y + 1 / 2)) + abs(2*x + 2 - y - abs(2*x + 2 - y)))*(abs(4 / 25 - x**2 - (y - 1)**2 - abs(4 / 25 - x**2 - (y - 1)**2)) + abs(x**2 + (y - 1)**2 - 1 / 25 - abs(x**2 + (y - 1)**2 - 1 / 25)))*(abs(x - abs(x)) + abs(3 / 4 - y - abs(3 / 4 - y)) + abs(2 * (y - 1 / 4) - x - abs(2 * (y - 1 / 4) - x)))*(abs(y - abs(y)) + abs(x - 1) + abs(3 / 4 - y - abs(3 / 4 - y)))*(abs(4 / 5 - y - abs(4 / 5 - y)) + abs(y - 2 / 5 - abs(y - 2 / 5)) + abs(y + x + 2 / 5 - abs(y + x + 2 / 5)) + abs(-y - 2*x - 4 / 5 - abs(-y - 2*x - 4 / 5)))
# # (abs(5 - x**2 - y**2 - abs(5 - x**2 - y**2)) + abs(10 - 2*x - y - abs(10 - 2*x - y)) + abs(y + 5 / 2 - abs(y + 5 / 2)) + abs(2*x + 10 - y - abs(2*x + 10 - y)))*(abs(4 / 5 - x**2 - (y - 5)**2 - abs(4 / 5 - x**2 - (y - 5)**2)) + abs(x**2 + (y - 5)**2 - 1 / 5 - abs(x**2 + (y - 5)**2 - 1 / 5)))*(abs(x - abs(x)) + abs(15 / 4 - y - abs(15 / 4 - y)) + abs(2 * (y - 5 / 4) - x - abs(2 * (y - 5 / 4) - x)))*(abs(y - abs(y)) + abs(x - 5) + abs(15 / 4 - y - abs(15 / 4 - y)))*(abs(4 - y - abs(4 - y)) + abs(y - 2 - abs(y - 2)) + abs(y + x + 2 - abs(y + x + 2)) + abs(-y - 2*x - 4 - abs(-y - 2*x - 4)))
# # def mand(a, b):
# #     return abs(a) + abs(b)
#
#
# # def mor(a, b):
# #     return a * b
#
#
# # def main_okr(x, y):
# #     return 25 - x ** 2 - y ** 2 - abs(25 - x ** 2 - y ** 2)
# #
# #
# # def main_triangle_1(x, y):
# #     return 10 - 2 * x - y - abs(10 - 2 * x - y)
# #
# #
# # def main_triangle_2(x, y):
# #     return 10 + 2 * x - y - abs(10 + 2 * x - y)
# #
# #
# # def main_triangle_3(x, y):
# #     return y + 5 / 2 - abs(y + 5 / 2)
#
#
# # def main_triangle_and_okr(x, y):
# #     return abs(25 - x ** 2 - y ** 2 - abs(25 - x ** 2 - y ** 2)) + abs(10 - 2 * x - y - abs(10 - 2 * x - y)) + abs(
# #         10 + 2 * x - y - abs(10 + 2 * x - y)) + abs(y + 5 / 2 - abs(y + 5 / 2))
#
#
# # def krishka_1(x, y):
# #     return x ** 2 + (y - 5) ** 2 - 2 - abs(x ** 2 + (y - 5) ** 2 - 2)
# #
# #
# # def krishka_2(x, y):
# #     return 4 - x ** 2 - (y - 5) ** 2 - abs(4 - x ** 2 - (y - 5) ** 2)
#
#
# # def krishka(x, y):
# #     return abs(x ** 2 + (y - 5) ** 2 - 2 - abs(x ** 2 + (y - 5) ** 2 - 2)) + abs(
# #         4 - x ** 2 - (y - 5) ** 2 - abs(4 - x ** 2 - (y - 5) ** 2))
#
#
# # def derzh_1(x, y):
# #     return abs(x - abs(x)) + abs(4 - y - abs(4 - y)) + abs(y - 2 / 5 * x - 2 - abs(y - 2 / 5 * x - 2))
# #
# #
# # def derzh_2(x, y):
# #     return abs(4 - y - abs(4 - y)) + abs(y - abs(y)) + abs(x - 5)
#
#
# # def derzh(x, y):
# #     return (abs(x - abs(x)) + abs(4 - y - abs(4 - y)) + abs(y - 2 / 5 * x - 2 - abs(y - 2 / 5 * x - 2))) * (
# #             abs(4 - y - abs(4 - y)) + abs(y - abs(y)) + abs(x - 5))
# #
# #
# # def svist(x, y):
# #     return abs(4 - y - abs(4 - y)) + abs(y - abs(y)) + abs(y + 2 * x + 8 - abs(y + 2 * x + 8)) + abs(
# #         -y - x - 1 - abs(-y - x - 1))
from random import randint

n, q = randint(2000, 3000), randint(1000, 3000)
nums = [randint(0, int(1e9) - 1) for _ in range(n)]
reqs = [[0, 0] for _ in range(q)]

for req in reqs:
    req[0] = randint(1, n)
    req[1] = randint(req[0], n)

of = open("C:\\Users\\banan\\projects\\olympiads\\aesc\\special_course_2\\B_C++\\cmake-build-debug\\out.txt", "w")
of.write(str(n) + "\n")
of.write(" ".join(map(str, nums)))
of.write("\n" + str(q) + "\n")
of.write("\n".join([str(r[0]) + " " + str(r[1]) for r in reqs]))
of.write("\n")
of.close()

# import os
# from random import randint
#
# os.system(
#     "g++ C:\\Users\\banan\\projects\\olympiads\\aesc\\special_course_2\\B_C++\\main.cpp -o C:\\Users\\banan\\projects\\olympiads\\aesc\\special_course_2\\B_C++\\cmake-build-debug\\main.exe")
# while True:
#     n, q = randint(1000, 3000), randint(1000, 3000)
#     nums = [randint(0, int(1e9) - 1) for _ in range(n)]
#     reqs = [[0, 0] for _ in range(q)]
#
#     for req in reqs:
#         req[0] = randint(1, n)
#         req[1] = randint(req[0], n)
#
#     of = open("C:\\Users\\banan\\projects\\olympiads\\aesc\\special_course_2\\B_C++\\cmake-build-debug\\out.txt", "w")
#     of.write(str(n) + "\n")
#     of.write(" ".join(map(str, nums)))
#     of.write("\n" + str(q) + "\n")
#     of.write("\n".join([str(r[0]) + " " + str(r[1]) for r in reqs]))
#     of.write("\n")
#     of.close()
#     if os.system(
#             "C:\\Users\\banan\\projects\\olympiads\\aesc\\special_course_2\\B_C++\\cmake-build-debug\\main.exe") != 0:
#         break
#
# def f(x, y):
#     return abs(x ** 2 + y ** 2 - 16) + abs(-y - abs(-y))
#
#
# def f(x, y):
#     return (abs(x ** 2 + y ** 2 - 16) + abs(-y - abs(-y))) * (
#             abs(y - abs(y)) + abs(6 - y - abs(6 - y)) + abs(y - 3 * x - 8)) * (
#                    abs(y - abs(y)) + abs(6 - y - abs(6 - y)) + abs(y + 2 * x - 8)) * (
#                    abs(y + 4 - abs(y + 4)) + abs(-y - abs(-abs(-y - 1))) + abs(y - 6)) * (
#                    abs(x ** 2 + y ** 2 + 16) + abs(y - 6 - abs(y - 6)))
