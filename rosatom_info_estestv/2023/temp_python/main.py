[a, b] = [int(s) for s in input().split(' ')]
while a != b:
    if a < b:
        b -= a
    else:
        a -= b
print(a)
