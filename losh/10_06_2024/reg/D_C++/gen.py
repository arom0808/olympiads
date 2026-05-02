from random import randint

maxn = 100000
maxt = int(1e9)
n, m, w = randint(2, 100), randint(1, maxn), randint(1, maxn)
print(n, m, w)
ts = [randint(1, maxt) for _ in range(n)]
print(" ".join(list(map(str, ts))))
for i in range(m):
    x = randint(0, n - 2)
    y = randint(x + 1, n - 1)
    a = randint(1, maxt - 1)
    b = randint(a + 1, maxt)
    c = randint(1, maxt)
    print(x, y, a, b, c)
for i in range(w):
    l = randint(1, maxt - 1)
    r = randint(l + 1, maxt)
    print(l, r)
