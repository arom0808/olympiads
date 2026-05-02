from random import randint

n, m = randint(5, 10), randint(5, 10)
print(n, m)
arr = [randint(1, n) for i in range(n)]
print(" ".join(map(str, arr)))
for i in range(m):
    c = randint(0, 1)
    if c == 0:
        print(c, randint(1, n), randint(1, n))
    else:
        print(c, randint(1, n))
