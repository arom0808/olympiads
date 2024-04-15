def sopr(n, m):
    if n % 2 == 1 and (m // 100) % 2 == 0:
        return False
    if n % 2 == 0 and ((m // 100) % 2 == 1 or m // 100 == 0):
        return False
    return m % 100 == n // 100 + n % 100 // 10 + n % 10


def main():
    l, r = map(int, input().split())
    a, b = map(int, input().split())
    for n in range(b, a - 1, -1):
        if sopr(l, n) and sopr(r, n):
            print('V', n, sep='')
            return
    for n in range(b, a - 1, -1):
        if sopr(l, n):
            print('L', n, sep='')
            return
        if sopr(r, n):
            print('R', n, sep='')
            return
    print(0)


main()
