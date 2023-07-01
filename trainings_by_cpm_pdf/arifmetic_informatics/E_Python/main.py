from math import gcd, lcm


# def gcd(a: int, b: int):
#     if a > b:
#         a, b = b, a
#     while b > 0:
#         a = a % b
#         a, b = b, a
#     return a
#
#
# def lcm(a: int, b: int):
#     return a * b // gcd(a, b)


def main():
    [a, b, c, d] = map(int, input().split(' '))
    if b < 0:
        a, b = a * -1, b * -1
    if d < 0:
        c, d = c * -1, d * -1
    de = lcm(b, d)
    a, c = a * (de // b), c * (de // d)
    s_f = a + c
    if s_f < 0:
        print('-', end='')
    s_f, de = abs(s_f), abs(de)
    if s_f >= de:
        print(s_f // de, end=' ')
    if s_f % de != 0:
        ff = gcd(s_f % de, de)
        print((s_f % de) // ff, end='/')
        print(de // ff, end='')


main()
