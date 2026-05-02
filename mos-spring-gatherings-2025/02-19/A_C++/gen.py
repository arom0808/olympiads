from random import randint

n, m, k = randint(1, 6), randint(1, 6), randint(0, 6)
print(n, m, k)

for i in range(n):
    print(''.join([str(randint(0, 1)) for _ in range(m)]))
