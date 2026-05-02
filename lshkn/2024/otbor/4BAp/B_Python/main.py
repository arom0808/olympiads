effs = [0 for _ in range(3001)]


def init_effs():
    effs[1] = -1
    for i in range(2, 3001):
        if i == 10 or i == 100 or i == 1000:
            effs[i] = effs[i - 1]
        else:
            effs[i] = effs[i - 1] + 1


# def get_for_n(n):
#     dp = [[0 for _ in range(6000)] for __ in range(n + 1)]
#     for i in range(1, n + 1):
#         dp[i][effs[i] + 3000] = 26
#     for i in range(2, n + 1):
#         for j in range(i - 1, 0, -1):
#             for j_eff in range(-j, j + 1):
#                 dp[i][3000 + effs[i - j] + j_eff] += dp[j][3000 + j_eff] * 25
#     res = 0
#     for eff in range(3001, 5999):
#         res += dp[n][eff]
#     return res


def main():
    init_effs()
    f = open('res.txt', 'w')
    f.write('\n')
    dp = [[[0 for _ in range(6000)] for ___ in range(3001)] for __ in range(3001)]
    for i in range(1, 3001):
        dp[i][effs[i] + 3000] = 26
    for i in range(2, 3001):
        for j in range(i - 1, 0, -1):
            for j_eff in range(-j, j + 1):
                dp[i][3000 + effs[i - j] + j_eff] += dp[j][3000 + j_eff] * 25
        res = 0
        for eff in range(3001, 5999):
            res += dp[i][eff]
        f.write(str(res))
        f.write('\n')
        f.flush()


main()
