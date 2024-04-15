n, a, b, c = [int(input()) for _ in range(4)]
f, s = n // a, (n - b + 1) // (b - c) + ((n - b + 1) % (b - c) != 0) if (n - b + 1) > 0 else 0
s += (n - s * (b - c)) // a
print(max(f, s))
