import random

o = open('in.txt', 'w')
for i in range(100000):
    x, n, p = random.randint(0, 2000000000), random.randint(0, 2000000000), random.randint(1, 2000000000)
    o.write(str(x))
    o.write(' ')
    o.write(str(n))
    o.write(' ')
    o.write(str(p))
    o.write('\n')

o.close()
