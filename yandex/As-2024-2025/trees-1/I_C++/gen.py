from random import randint

n, q = randint(1, 8), randint(1, 5)

print(n, q)
print("\n".join([str(randint(i + 1, n - 1) + 1) + " " + str(i + 1) for i in range(n - 1)]))
for _ in range(q):
    t = randint(0, 2)
    if t == 0:
        print("up", randint(1, n))
    elif t == 1:
        print("when", randint(1, n))
    else:
        print("compare", randint(1, n), randint(1, n))
