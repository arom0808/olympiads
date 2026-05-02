from random import randint

n, k = randint(1, 5), randint(1, 2)

print(n, k)

print("\n".join([" ".join([str(randint(0, 2)) for _ in range(k)]) for __ in range(2 * n)]))

print("\n".join([str(randint(i + 1, n - 1) + 1) + " " + str(i + 1) for i in range(n - 1)]))
