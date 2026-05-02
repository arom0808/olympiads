from random import randint

n, d, t = randint(1, 5), randint(1, 5), randint(1, 10)
print(n, d, t)

print(" ".join([str(randint(1, 10)) for _ in range(n)]))
