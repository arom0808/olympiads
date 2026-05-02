from random import randint

n, q, sv = randint(1, 1000), randint(1, 1000), randint(1, 1000)
print(n, q)
print(sv)

for _ in range(q):
    if randint(0, 1):
        a = randint(0, n - 1)
        b = randint(a + 1, n)
        c = randint(1, 1000)
        print(1, a, b, c)
    else:
        print(0, randint(0, n - 1))
