def bin_gcd(a: int, b: int):
    if a < b:
        a, b = b, a
    if b == 0:
        return a
    f, s = a % 2 == 0, b % 2 == 0
    if f and s:
        return 2 * bin_gcd(a // 2, b // 2)
    if f:
        return bin_gcd(a // 2, b)
    if s:
        return bin_gcd(a, b // 2)
    return bin_gcd(a - b, b)


def main():
    [a, b] = [int(input()) for _ in range(2)]
    print(bin_gcd(a, b))


main()
