from random import randint

n, s = randint(2, 5), randint(1, 3)
m = 0
acts = []
for i in range(s):
    ns = 0
    while ns < n - 1:
        ns = randint(ns, n - 1)
        if ns == n - 1:
            continue
        ne = randint(ns + 1, n - 1)
        acts.append([i + 1, ns + 1, ne + 1])
        ns = ne
        m += 1
print(n, s, m)
for act in acts:
    print(' '.join(map(str, act)))
q = 1
a = randint(0, n - 2)
b = randint(a + 1, n - 1)
print(q)
print(a + 1, b + 1)
