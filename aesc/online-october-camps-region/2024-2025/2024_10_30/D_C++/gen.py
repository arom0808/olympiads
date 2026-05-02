from random import randint

n, k, m = randint(1, 5), randint(1, 5), randint(1, 5)
print(n, k, m)
print(" ".join([str(randint(1, k)) for _ in range(n)]))
for _ in range(m):
    t = randint(1, 2)
    if t == 1:
        print(t, randint(1, n), randint(1, k))
    else:
        print(t)
