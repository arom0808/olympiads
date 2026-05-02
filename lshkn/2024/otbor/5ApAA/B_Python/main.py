from functools import cmp_to_key


def cmp_f(a, b):
    if a[0] < b[0]:
        return -1
    if a[0] > b[0]:
        return 1
    if (not a[1]) and b[1]:
        return -1
    if a[1] and not b[1]:
        return 1
    return 0


def main():
    n, x, d = map(int, input().split())
    acts = [[] for _ in range(abs(d))]
    for k in range(n + 1):
        n_min = x * k + d * (k - 1) * k // 2
        n_max = x * k + d * (2 * n - k - 1) * k // 2
        if n_min > n_max:
            n_min, n_max = n_max, n_min
        acts[x * k % abs(d)].append((n_min, False))
        acts[x * k % abs(d)].append((n_max, True))
    result = 0
    for ost in range(abs(d)):
        acts[ost].sort(key=cmp_to_key(cmp_f))
        cnt, start = 0, 0
        for (pos, type) in acts[ost]:
            if cnt == 0 and not type:
                start = pos
            if type and cnt == 1:
                result += (pos - start) // abs(d) + 1
            if not type:
                cnt += 1
            else:
                cnt -= 1
    print(result)


main()
