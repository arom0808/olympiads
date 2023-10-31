def solve(a, b, c, d, e, f):
    delta, delta_x, delta_y = a * d - b * c, e * d - b * f, a * f - e * c
    if delta != 0:
        return "2 {s1:.2f} {s2:.2f}".format(s1=delta_x / delta, s2=delta_y / delta)
    if a == b == c == d == e == f == 0:
        return "2XY"
    if (a == b == 0 and e != 0) or (c == d == 0 and f != 0):
        return "0"
    if delta_x == 0:
        if a == c == 0:
            return "1X {0:.2f}".format((f / d) if b == 0 else (e / b))
        if b == d == 0:
            if delta_y == 0:
                return "1Y {0:.2f}".format((f / c) if a == 0 else (e / a))
            return "0"
        return "1"
    return "0"


def main():
    print(solve(*map(int, input().split())))


main()
