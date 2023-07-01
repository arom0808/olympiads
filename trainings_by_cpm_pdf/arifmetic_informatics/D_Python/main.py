def main():
    n, p, d = int(input()), [], 2
    while d ** 2 <= n:
        while n % d == 0:
            p.append(d)
            n //= d
        d += 1
    if n > 1:
        p.append(n)
    print(' '.join(map(str, sorted(p))))


main()
