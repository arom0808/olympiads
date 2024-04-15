n = int(input())
m = n
while m > 0:
    print(n - m, m)
    m = (m - 1) & n
print(n - m, m)
