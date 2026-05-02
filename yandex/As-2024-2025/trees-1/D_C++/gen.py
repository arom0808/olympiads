from random import randint

n = randint(1, 6)
print(n)
print(" ".join([str(randint(1, 10)) for _ in range(n)]))
p = [randint(i + 1, n - 1) for i in range(n - 1)]
print("\n".join([str(i + 1) + ' ' + str(p[i] + 1) for i in range(n - 1)]))
