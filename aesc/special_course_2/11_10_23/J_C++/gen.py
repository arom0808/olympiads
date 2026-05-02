from random import randint

n, q = randint(1, 5), randint(1, 2)
print(n, q)
arr = [chr(ord('a') + randint(0, 25)) for i in range(n)]
print(''.join(arr))
for i in range(q):
    a = randint(1, n)
    b = randint(a, n)
    c = randint(0, 1)
    print(a, b, c)
