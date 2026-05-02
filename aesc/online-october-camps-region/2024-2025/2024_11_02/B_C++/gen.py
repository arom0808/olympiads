from random import randint

[g, r, b] = [randint(1, 5) for _ in range(3)]
print(" ".join(map(str, [g, r, b])))
print("\n".join([" ".join([str(randint(0,5)) for _ in range(sz)]) for sz in [g, r, b]]))