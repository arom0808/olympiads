from math import sqrt, ceil

n = int(input())
m = ceil(sqrt(n) / 2)
arr = [0 for _ in range(m)]
arr[0] = 1
arr[1] = 2
for i in range(2, m):
    arr[i] = arr[i - 1] + arr[i - 1] + 1
print(" ".join(map(str, arr)))
