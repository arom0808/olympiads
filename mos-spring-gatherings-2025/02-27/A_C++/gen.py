from random import randint

n, m, p = randint(2, 5), randint(1, 10), randint(1, 10)
print(n, m, p)
for i in range(m):
    a = randint(1, n - 1)
    b = randint(a + 1, n)
    c = randint(1, p)
    print(a, b, c)

q = randint(1, 10)
print(q)
for i in range(q):
    l = randint(1, p)
    r = randint(l, p)
    x = randint(0, 10)
    print(l, r, x)
