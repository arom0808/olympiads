from random import randint

n, m = randint(1, 10), randint(1, 2)

print(n, m)
print(" ".join([str(randint(1, m)) for _ in range(n)]))
