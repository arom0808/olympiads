from random import randint

n = 5
m = 3
k = 2

print(n, m, k)

ps = [randint(i + 1, n - 1) for i in range(n - 1)]
print("\n".join([str(i + 1) + " " + str(ps[i] + 1) for i in range(n - 1)]))
ps.append(-1)
i = 0
while i < m:
    u = randint(0, n - 1)
    v = randint(0, n - 1)
    if ps[u] == v or ps[v] == u or u == v:
        continue
    print(u + 1, v + 1)
    i += 1
