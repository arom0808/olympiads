from random import randint


def rchr():
    return chr(ord('a') + randint(0, 5))


print("".join([rchr() for _ in range(randint(1, 10))]))
