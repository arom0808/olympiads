from random import randint

n, q = randint(1, 10), randint(1, 10)
print(n, q)
print(" ".join([str(randint(1, 10)) for _ in range(n)]))

for i in range(q):
    t = randint(1, 4)
    if t == 1 or t == 2:
        l = randint(1, n)
        r = randint(l, n)
        print(t, l, r, randint(1, 10))
    elif t == 3:
        c = randint(1, n + 1)
        print(t, c, randint(1, 10))
        n += 1
    elif t == 4:
        l = randint(1, n)
        r = randint(l, n)
        print(t, l, r)
