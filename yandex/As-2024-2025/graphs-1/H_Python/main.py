from math import lcm


def main():
    n = int(input())
    a, b, c = map(int, input().split())
    print(n // a + n // b + n // c - n // lcm(a, b) - n // lcm(a, c) - n // lcm(b, c) + n // lcm(a, b, c))


main()
