from random import randint

n, m = randint(1, 100), randint(1, 100)
k = randint(1, n + m)
print(n, m, k)
print(" ".join([str(randint(0, 10000000)) for _ in range(n)]))
print(" ".join([str(randint(0, 10000000)) for _ in range(m)]))
