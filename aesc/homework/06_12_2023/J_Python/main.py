def sol(n):
    dp = [[0] * (n // 2 * 9 + 1) for _ in range(n // 2 + 1)]
    dp[0][0] = 1
    for i in range(0, n // 2):
        for j in range(n // 2 * 9 + 1):
            for k in range(min(n // 2 * 9 + 1 - j, 10)):
                dp[i + 1][j + k] += dp[i][j]
    res = 0
    for i in range(n // 2 * 9 + 1):
        res += dp[n // 2][i] ** 2
    if n % 2 == 1:
        res *= 10
    res -= 1
    return res


def main():
    print(sol(int(input())))


main()
