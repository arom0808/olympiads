from sys import stdin, stdout


def dig_cnt(num: int):
    res = 0
    while num > 0:
        res += num % 10
        num //= 10
    return res


def factorial_digit_sum(l, r):
    if abs(l - r) <= 10:
        num = l
        for i in range(l + 1, r + 1):
            num *= i
        while num > 9:
            num = dig_cnt(num)
        return num
    return 9


def main():
    n = int(stdin.readline().rstrip('\n'))
    for i in range(n):
        stdout.write(str(factorial_digit_sum(*[int(i) for i in stdin.readline().rstrip('\n').split()])))
        stdout.write('\n')


main()
# # def fact_factor(n: int):
#     if n < 0:
#         return 0
#     if n == 0:
#         return 1
#     if n == 1 or n == 2:
#         return n
#     u = [False] * (n + 1)
#     p = []
#     for i in range(2, n + 1):
#         if not u[i]:
#             k = n // i
#             c = 0
#             while k > 0:
#                 c += k
#                 k //= i
#             p.append((i, c))
#             j = 2
#             while i * j <= n:
#                 u[i * j] = True
#                 j += 1
#     r = 1
#     for i in reversed(range(0, len(p))):
#         r *= p[i][0] ** p[i][1]
#     return r
#
#
# print(fact_factor(int(1e9)))
