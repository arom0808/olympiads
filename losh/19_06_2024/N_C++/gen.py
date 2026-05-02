from random import randint

hl, hr, n = randint(0, 100), randint(0, 100), randint(0, 10)
print(hl, hr, n)
tc = randint(0, n)
bc = n - tc
lb = -1
for i in range(tc):
    a = randint(lb + 1, max(lb + 1, 100000 - (n - i) * 10))
    b = randint(a + 1, max(a + 1, 100000 - (n - i) * 5))
    lb = b
    print(randint(1, 10), 'T', a, b)
lb = -1
for i in range(bc):
    a = randint(lb + 1, max(lb + 1, 100000 - (n - i - tc) * 10))
    b = randint(a + 1, max(a + 1, 100000 - (n - i - tc) * 5))
    lb = b
    print(randint(1, 10), 'F', a, b)
