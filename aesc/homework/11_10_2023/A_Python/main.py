n, m = [int(i) for i in input().split()]
print(((n - 1) % 7 + (m - 1) % 7) % 7 + 1)
