from random import randint

n = randint(1000, 10000)
k = randint(2, min(n, 20))
print(n, k)
print(" ".join([str(randint(1, n)) for _ in range(n)]))
