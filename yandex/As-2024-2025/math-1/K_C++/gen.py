from random import randint

n = randint(1, 20)
print(n)
print(" ".join([str(randint(-20, 20)) for _ in range(n)]))
