from random import randint

t = randint(1, 2)

print(t)
for __ in range(t):
    n = randint(1, 3)
    print(n)
    arr = [randint(0, (1 << 3) - 1) for _ in range(n)]
    print(" ".join(map(str, arr)))
    q = randint(1, 3)  #
    print(q)
    for i in range(q):
        x = randint(3, 5)
        if x == 3:
            print(x, randint(0, (1 << 3) - 1))
        else:
            print(x, randint(1, n))
