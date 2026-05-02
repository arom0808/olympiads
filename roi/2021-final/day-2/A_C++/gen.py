from random import randint

gend = 0


def rch():
    global gend
    d = randint(0, 30)
    if d < 26 or gend >= 3:
        d = randint(0, 25)
        return chr(ord('A') + d)
    gend += 1
    return '?'


print(10)
for i in range(10):
    n = randint(1, 20)
    gend = 0
    print("".join([rch() for _ in range(n)]))
