m = int(input())
for n in range(1 << m):
    for i in range(m - 1, -1, -1):
        print((n >> i) & 1, end='')
    print()
