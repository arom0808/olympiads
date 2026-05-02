from sys import exit


def ask(t):
    print("X", t)
    res = input()
    if res == "-1":
        exit(0)
    return [int(x) for x in res.split(' ')]


def ans(t):
    print("N", t)
    res = input()
    if res != "Correct":
        exit(0)


def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


def lcm(a, b):
    return a * b // gcd(a, b)


def run_game():
    l, r = 1, 10 ** 18
    


def main():
    g = int(input())
    for _ in range(g):
        run_game()


main()
