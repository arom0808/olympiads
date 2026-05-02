from random import randint


def rc():
    c = randint(0, 14)
    if c < 10:
        return chr(ord('0') + c)
    if c == 10:
        return '+'
    if c == 11:
        return '*'
    return '0'


n = randint(5000, 10000)
print("".join([rc() for _ in range(n)]))
