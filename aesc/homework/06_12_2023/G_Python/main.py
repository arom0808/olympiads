n = int(input())
cnt = 0

for i in range(1, n // 3 + 1):
    cnt += (n - i) // 2 - i + 1

print(cnt)
