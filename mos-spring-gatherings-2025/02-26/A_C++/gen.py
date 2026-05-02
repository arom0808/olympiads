from random import randint

print(1)
n = randint(1, 40)
print(n)
print(''.join(['L' if randint(0, 1) else 'R' for _ in range(n)]))
