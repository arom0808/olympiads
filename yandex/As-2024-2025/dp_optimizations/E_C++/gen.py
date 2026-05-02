from random import randint, shuffle

n, m = randint(1, 3), randint(1, 3)
print(n, m)
print("\n".join([str(randint(0, 10)) + " " + str(randint(1, 10)) for _ in range(n)]))
for i in range(m):
    k = randint(0, n - 1)
    ds = [randint(1, n) for _ in range(k)]
    ds = list(set(ds))
    shuffle(ds)
    print(randint(0, 10), len(ds), " ".join(map(str, ds)))
