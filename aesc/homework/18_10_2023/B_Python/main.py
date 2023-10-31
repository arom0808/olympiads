def func(x1, y1, x2, y2, x3, y3):
    if x1 == x2 and y1 == y2:
        if x2 == x3 and y2 == y3:
            return 0
        return 1
    if (x2 == x3 and y2 == y3) or (x1 == x3 and y1 == y3):
        return 1
    if x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2) == 0:
        return 2
    if (x1 - x2) * (x3 - x2) + (y1 - y2) * (y3 - y2) > 0:
        if (x2 - x3) * (x1 - x3) + (y2 - y3) * (y1 - y3) > 0:
            if (x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1) > 0:
                return 3
            if (x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1) == 0:
                return 4
            return 5
        if (x2 - x3) * (x1 - x3) + (y2 - y3) * (y1 - y3) == 0:
            return 4
        return 5
    if (x1 - x2) * (x3 - x2) + (y1 - y2) * (y3 - y2) == 0:
        return 4
    return 5


print(func(*map(int, input().split())))
