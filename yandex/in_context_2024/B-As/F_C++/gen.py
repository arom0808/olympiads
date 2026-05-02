from random import randint

n = randint(4, 7)
print(n)
print(" ".join([str(randint(1, 8)) for _ in range(n)]))
