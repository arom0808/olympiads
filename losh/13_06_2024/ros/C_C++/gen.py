from random import randint

n, q = randint(1, 100), randint(1, 100)
print(n, q)
nums = [randint(1, 10) for _ in range(n)]
print(" ".join(map(str, nums)))
for _ in range(q):
    print(randint(1, n), randint(1, 10))
