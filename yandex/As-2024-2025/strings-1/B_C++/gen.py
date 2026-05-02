from random import randint


def rand_str(l):
    return ''.join([chr(ord('a') + randint(0, 25)) for _ in range(l)])


ss = rand_str(20)
print(ss)
n = 5
print(n)
for _ in range(5):
    print(rand_str(randint(1, 2)))
