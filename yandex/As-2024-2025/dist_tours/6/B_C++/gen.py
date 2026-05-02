from random import randint

n = randint(1, 100)
m = randint(1, n)
q = n

print(n, m, q)
hs = set()
while len(hs) < m:
    hs.add(randint(1, n))

print(" ".join(map(str, sorted(list(hs)))))
print(" ".join([str(i+1) for i in range(n)]))