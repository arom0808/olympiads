from random import randint


def rsol(a):
    b = sorted(a)
    return b[0], b[1]


def sol(a):
    m1, m2 = [30001] * 2
    for el in a:
        if el < m1:
            m2 = m1
            m1 = el
        elif el < m2:
            m2 = el
    return m1, m2


def test():
    while (True):
        a = [randint(-1000, 1000) for _ in range(randint(2, 100))]
        r1, r2 = sol(a), rsol(a)
        if r1 != r2:
            print(a)
            print(r1)
            print(r2)
            break


def main():
    n = int(input())
    a = [int(_) for _ in input().split()]
    m1, m2 = [30001] * 2
    for el in a:
        if el < m1:
            m2 = m1
            m1 = el
        elif el < m2:
            m2 = el
    print(m1, m2)


test()
