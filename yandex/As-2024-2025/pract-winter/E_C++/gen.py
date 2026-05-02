from random import randint

n = randint(1, 15)
m = randint(1, n)
print(n, m)
print(" ".join([str(randint(1, (2 ** 10) - 1)) for _ in range(n)]))
