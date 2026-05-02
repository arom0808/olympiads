from random import randint


def rch(s):
    return s[randint(0, len(s) - 1)]


n = randint(1, 1000)
k = randint(1, 10)

print(k)
print(" ".join([rch(str(i)) for i in range(n, n + k)]))
