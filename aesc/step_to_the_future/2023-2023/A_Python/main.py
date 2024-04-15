v, m, z = map(int, input().split())
if v > z:
    print(3)
elif m >= v:
    print(0)
else:
    print(((z - v) // (v - m) + 1) * 7 + 3)
