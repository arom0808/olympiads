def GetPreSum(summs, i, j):
    res = 0
    if i > 0:
        res += summs[i - 1][j]
    if j > 0:
        res += summs[i][j - 1]
    if i > 0 and j > 0:
        res -= summs[i - 1][j - 1]
    return res


def GetSum(summs, i1, j1, i2, j2):
    res = summs[i2 - 1][j2 - 1]
    if i1 > 0 and j1 > 0:
        res += summs[i1 - 1][j1 - 1]
    if i1 > 0:
        res -= summs[i1 - 1][j2 - 1]
    if j1 > 0:
        res -= summs[i2 - 1][j1 - 1]
    return res


def main():
    in_file = open("input.txt", 'r')
    [N, M] = [int(s) for s in in_file.readline().strip('\n').rstrip('\n').split(' ')]
    map, summs = [[] for __ in range(N)], [[0 for _ in range(M)] for __ in range(N)]
    for i in range(N):
        map[i] = [int(s) for s in in_file.readline().strip('\n').rstrip('\n').split(' ')]
        for j in range(M):
            summs[i][j] = GetPreSum(summs, i, j) + map[i][j]
    in_file.close()
    max_pribil = -99999999999999999999999999999999999999999999999999
    for start_i in range(N):
        for start_j in range(M):
            for end_i in range(0, N + 1):
                for end_j in range(0, M + 1):
                    # pribil = 0
                    # for i in range(start_i, end_i):
                    #     for j in range(start_j, end_j):
                    #         pribil += map[i][j]
                    pribil = GetSum(summs, min(start_i, end_i), min(start_j, end_j), max(start_i, end_i),
                                    max(start_j, end_j))
                    if pribil > max_pribil:
                        max_pribil = pribil
    out_file = open("output.txt", 'w')
    out_file.write(str(max(max_pribil, 0)))
    out_file.close()


main()
