from math import sqrt


def X(k):
    res = 0
    for i in range(k, 0, -1):
        res = sqrt(3 * i + res)
    return res


print('{:.20f}'.format(X(int(1e7))))

# tt = [[-1] * 13 for _ in range(13)]
# table = [[0] * 13 for _ in range(13)]
# last_colored = (0, 0)
# timer = 1
#
#
# def color(x, y):
#     global table, last_colored, timer, tt
#     table[x][y] = timer
#     timer += 1
#     last_colored = (x, y)
#     if y + 1 < 13 and tt[x][y + 1] == 0 and table[x][y + 1] == 0:
#         color(x, y + 1)
#     if x + 1 < 13 and tt[x + 1][y] == 0 and table[x + 1][y] == 0:
#         color(x + 1, y)
#     if y - 1 >= 0 and tt[x][y - 1] == 0 and table[x][y - 1] == 0:
#         color(x, y - 1)
#     if x - 1 >= 0 and tt[x - 1][y] == 0 and table[x - 1][y] == 0:
#         color(x - 1, y)
#
#
# for i in range(13):
#     if i == 1 or i == 11:
#         for j in range(5, 8):
#             tt[i][j] = 0
#     elif i == 2 or i == 10:
#         for j in range(3, 10):
#             tt[i][j] = 0
#     elif i == 3 or i == 4 or i == 9 or i == 8:
#         for j in range(2, 11):
#             tt[i][j] = 0
#     elif i == 5 or i == 6 or i == 7:
#         for j in range(1, 12):
#             tt[i][j] = 0
# ans = 0
# for si in range(13):
#     for sj in range(13):
#         if tt[si][sj] == -1:
#             continue
#         timer = 1
#         table = [[0] * 13 for _ in range(13)]
#         color(si, sj)
#         print(last_colored)
#         if last_colored == (3, 10):
#             print(si, sj)
#             ans += 1
#
# print()
# print(ans)
# def imp(a, b):
#     return (not a) or b
#
#
# def X(a, b, c, d, e, f, g, h):
#     return imp(imp(not imp(imp(b, imp(e, imp(not a, imp(not c, not d)))), f),
#                    not imp(imp(not a, imp(e, imp(d, imp(not c, not b)))), not g)),
#                not imp(imp(e, imp(not a, imp(not c, imp(b, not d)))), not h))
#
#
# def Y(a, b, c, d, e, f, g, h):
#     return imp(not imp(imp(b, imp(e, imp(not a, imp(not c, not d)))), f),
#                imp(not imp(imp(not a, imp(e, imp(d, imp(not c, not b)))), not g),
#                    not imp(imp(e, imp(not a, imp(not c, imp(b, not d)))), not h)))
#
#
# def CF(a, b, c, d, e, f, g, h):
#     return imp(d, imp(not a, imp(b, imp(e, c))))
#
#
# for a in [False, True]:
#     for b in [False, True]:
#         for c in [False, True]:
#             for d in [False, True]:
#                 for e in [False, True]:
#                     for f in [False, True]:
#                         for g in [False, True]:
#                             for h in [False, True]:
#                                 if not CF(a, b, c, d, e, f, g, h):
#                                     continue
#                                 if not f and g and not h:
#                                     # if not imp(not X(a, b, c, d, e, f, g, h), Y(a, b, c, d, e, f, g, h)):
#                                     print(int(a), int(b), int(c), int(d), int(e), int(f), int(g), int(h))
#                                     print(imp(not X(a, b, c, d, e, f, g, h), Y(a, b, c, d, e, f, g, h)))

# dp = []
#
#
# def gen_dp_arr(level, n):
#     if level == n:
#         return [-1] * (n + 2)
#     return [gen_dp_arr(level + 1, n) for _ in range(n + 2)]
#
#
# def get_ch_val(cnts, level, n):
#     if level == n:
#         return 1 - get_dp_val(dp, cnts, 0, n)
#     cv = 0
#     if cnts[level] != 0:
#         cnts[level] -= 1
#     cv |= get_ch_val(cnts, level + 1, n)
#     if cnts[level] != 0:
#         cnts[level] += 1
#     return cv
#
#
# def get_dp_val(dpv, cnts, level, n, pre_sum=0):
#     if level == n - 1:
#         if dpv[cnts[level]] != -1:
#             return dpv[cnts[level]]
#         pre_sum += cnts[level]
#         if pre_sum == 0:
#             dpv[cnts[level]] = 0
#             return dpv[cnts[level]]
#         dpv[cnts[level]] = get_ch_val(cnts, 0, n)
#         return dpv[cnts[level]]
#     return get_dp_val(dpv[cnts[level]], cnts, level + 1, n, pre_sum + cnts[level])
#
#
# def init_dp(ccnts, level, n):
#     if level == n:
#         get_dp_val(dp, ccnts, 0, n)
#         return
#     for i in range(n):
#         ccnts[level] = i + 1
#         init_dp(ccnts, level + 1, n)
#
#
# def gen_dp(n):
#     global dp
#     dp = gen_dp_arr(0, n - 1)
#     ccnts = [0] * n
#     init_dp(ccnts, 0, n)
#
#
# gen_dp(2)
# pass
