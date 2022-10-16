import random

n, m = random.randint(2, 100), random.randint(2, 100)
table = [[0 if random.randint(0, 5) == 0 else 1 for i in range(n)] for i in range(m)]
for i in range(random.randint(1, 5)):
    napr = False if random.randint(0, 1) == 0 else True
    if not napr:
        str_n = random.randint(0, m - 1)
        table[str_n] = [0 for i in range(n)]
    else:
        col_n = random.randint(0, n - 1)
        for j in range(m):
            table[j][col_n] = 0
print(len(table[0]), len(table))
print()
print(str(n) + " " + str(m))
for i in range(m):
    print(''.join(str(x) + ' ' for x in table[i]))
