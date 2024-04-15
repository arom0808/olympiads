# from random import randint
from math import sqrt


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def sol(m, k, sb, sc):
    if m + k == 0:
        return 1
    a, b = int(sb + sc), int('0' + sb)
    if a == 0:
        return 1
    x, y = 0, 0
    if k == 0 or int(sc) == 0:
        x, y = int(sb), 1
        for i in range(m):
            y *= 10
    else:
        x, y = a - b, 0
        for i in range(k):
            y = y * 10 + 9
        for i in range(m):
            y *= 10
    g = gcd(x, y)
    x, y = x // g, y // g
    res, mod = 1, 10 ** 9 + 7
    sqy = int(sqrt(y)) + 2
    prime = [True] * (sqy + 1)
    prime[0], prime[1] = False, False
    oot = y
    for i in range(2, sqy + 1):
        if prime[i]:
            if y % i == 0 and i * i <= y:
                res = (res * i) % mod
                while oot % i == 0:
                    oot //= i
            for j in range(i * i, sqy + 1, i):
                prime[j] = False
    if oot > 1:
        i, ee = 2, True
        while i * i <= oot and ee:
            if oot % i == 0:
                ee = False
            i += 1
        if ee:
            res = (res * oot) % mod
    return res


# def ngen(l):
#     r = ''
#     for i in range(l):
#         r += str(randint(0, 9))
#     return r
#
#
# def Test():
#     while True:
#         n, m, k, = [randint(0, 7) for _ in range(3)]
#         a, b, c = ngen(n), ngen(m), ngen(k)
#         try:
#             sol(m, k, b, c)
#         except:
#             print(n, m, k, a, b, c)
#             break


def main():
    n, m, k = map(int, input().split())
    a, b, c = [input() for _ in range(3)]
    print(sol(m, k, b, c))


main()
