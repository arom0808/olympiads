from random import randint

n = randint(1, 10)

print("".join([chr(ord('a') + randint(0, 4)) for _ in range(n)]))
