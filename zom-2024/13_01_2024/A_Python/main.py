def sum_to_d(d):
    if d == 0:
        return 0
    s, to_add, now_day = 0, 1, 0
    while now_day < d:
        now_day += to_add
        s += to_add * (to_add + 1) // 2
        to_add += 1
    to_add -= 1
    s -= to_add * (to_add + 1) // 2
    now_day -= to_add
    s += (d - now_day) * (d - now_day + 1) // 2
    return s


l, r = map(int, input().split())

print(sum_to_d(r) - sum_to_d(l - 1))
