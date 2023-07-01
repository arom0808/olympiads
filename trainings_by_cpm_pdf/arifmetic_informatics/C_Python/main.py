def main():
    n = int(input())
    is_prime = [True] * (n + 1)
    is_prime[0], is_prime[1] = False, False
    for i in range(2, n + 1):
        if (not is_prime[i]) or i ** 2 > n:
            continue
        for j in range(i ** 2, n + 1, i):
            is_prime[j] = False
    for i in range(2, n + 1):
        if is_prime[i]:
            if is_prime[n - i]:
                print(i, n - i)
                return


main()
