from random import randint

s = [chr(ord('a') + randint(0, 25)) for _ in range(randint(1, 10))]
print("".join(s))
n = randint(1, 4)
print(n)
bw = [[chr(ord('a') + randint(0, 25)) for _ in range(randint(1, len(s)))] for __ in range(n)]
for ee in bw:
    print("".join(ee))
q = randint(1, 3)
print(q)
for _ in range(q):
    l = randint(1, len(s))
    r = randint(l, len(s))
    print(l, r)
