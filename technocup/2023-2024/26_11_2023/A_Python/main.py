a, b, c = sorted([int(input()) for _ in range(3)])
if c - b == b - a and b * b == a * c:
    print('B', a, b, c)
elif c - b == b - a:
    print('A', a, b, c)
elif b * b == a * c:
    print('G', a, b, c)
else:
    print('No')
