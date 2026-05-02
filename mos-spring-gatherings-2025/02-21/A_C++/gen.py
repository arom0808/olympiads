from random import randint

t = randint(1, 1)
print(t)
print(" ".join([str(randint(1, 500)) for _ in range(t)]))
