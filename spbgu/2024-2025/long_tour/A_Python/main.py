def make_step(a, b, c):
    if b == a:
        return a, b, c
    return a + (b - a) * 2, b, c


def make_steps(a, b, c, i, t):
    if a == b:
        return a, b, c, t
    a, b, c = make_step(a, b, c)
    i += 1
    return a, b, c, i


def solve():
    a, b, c, t = map(int, input().split())
    vals = [a, b, c]
    ids = [0, 1, 2]
    i = 0
    while i < t:
        ids.sort(key=lambda x: (vals[x], x))
        vals[ids[0]], vals[ids[1]], vals[ids[2]], i = make_steps(vals[ids[0]], vals[ids[1]], vals[ids[2]], i, t)
    print(" ".join(map(str, vals)))


solve()
