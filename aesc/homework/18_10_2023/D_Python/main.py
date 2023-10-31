from math import sqrt


def can_push(a, b, d, e):
    if min(a, b) <= min(d, e) and max(a, b) <= max(d, e):
        return True
    if a < b:
        a, b = b, a
    if d > e:
        d, e = e, d
    cos_a, sin_a = (a * a - b * b) / (a * a + b * b), 2 * a * b / (a * a + b * b)
    s_2 = sqrt(a * a + b * b - d * d) / 2
    res_x, res_y = s_2 * cos_a + d * sin_a / 2, s_2 * sin_a - d * cos_a / 2
    if s_2 * 2 > e or res_x * 2 > e or abs(res_y) * 2 > d:
        return False
    return True


def func(a, b, c, d, e):
    if can_push(a, b, d, e) or can_push(a, c, d, e) or can_push(b, c, d, e):
        return "YES"
    return "NO"


print(func(*map(int, input().split())))
