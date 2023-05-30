W = int(input())
h = 31
while 12 * h * h * (h - 30) < (W + 50) * 1000:
    h += 1
print(6 * h, 2 * h, h)
