from random import randint


def randchr():
    return chr(ord('a') + randint(0, 5))


n = randint(1, 5)
print("".join([randchr() for _ in range(n)]))
print(randint(1, n * n))
