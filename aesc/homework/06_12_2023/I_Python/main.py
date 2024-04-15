from math import sqrt

m = int(input())

ans, cur, k = 0, sqrt(m), 1
while cur - ans > 1e-7:
    ans, cur, k = cur, 0, k + 1
    for i in range(k, 0, -1):
        cur = sqrt(i * m + cur)

print('{:6f}'.format(ans))
