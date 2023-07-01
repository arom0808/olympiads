def gcd(a: int, b: int):
    if a > b:
        a, b = b, a
    while b > 0:
        a = a % b
        a, b = b, a
    return a


def main():
    [a, b] = [int(input()) for _ in range(2)]
    print(gcd(a, b))


main()
