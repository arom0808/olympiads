n, m, k, c = [int(input()) for _ in range(4)]
a = m % k
res = n // k * (a * (m // k + (m % k != 0)) + (k - a) * (m // k))
for i in range(c - 1, c - 1 - (n % k), -1):
    res += (m - i % k) // k + ((m - i % k) % k != 0)
print(res)