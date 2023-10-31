def func(n, m, x, y):
    if n < m:
        n, m = m, n
    res = x
    if res > y:
        res = y
    if res > m - x:
        res = m - x
    if res > n - y:
        res = n - y
    return res


print(func(*map(int, input().split())))
