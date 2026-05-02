from random import randint

n = randint(1, 100)
print(n)
print(" ".join([str(randint(1, 10)) for _ in range(n)]))
