a, b = map(int, input().split())
print(a * b // (1 if a + b == 0 else a + b))
