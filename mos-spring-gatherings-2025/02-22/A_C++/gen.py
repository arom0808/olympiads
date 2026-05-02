from random import randint

n = randint(1, 5)
print(n)
ps = [-1 if i == 0 else randint(0, i - 1) for i in range(n)]
for i, u in enumerate(ps):
    if u != -1:
        print(i + 1, u + 1)

print(" ".join([str(randint(-5, 5)) for _ in range(n)]))
