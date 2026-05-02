from random import randint

n = randint(1, 10)
print(n)
print(" ".join([str(randint(1, 100)) for _ in range(n)]))
m = randint(1, 10)
print(m)
for i in range(m):
    l = randint(1, n)
    r = randint(l, n)
    if randint(0, 1):
        k = randint(1, n - r + 1)
        print(1, l, r, k)
    else:
        print(0, l, r, randint(1, 100))
