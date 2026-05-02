from random import randint

n = randint(2, 20)

rics = []
rics.append(randint(0, n - 2))

pops = 0
while len(rics) < 2 or pops < 20:
    r = randint(rics[-1], n - 1)
    if ((r - rics[-1]) & 1) and (len(rics) == 1 or r - rics[-1] != rics[-1] - rics[-2]):
        rics.append(r)
    pops += 1

print(n, len(rics))
print(" ".join(map(str, rics)))
