n = int(input())
pre_sum, i = 1, 1
fr_res = []
while i <= n:
    fr_res.append(i)
    i += pre_sum
    pre_sum += i - pre_sum
res = (sum(fr_res), 0, 0)
ok_sum = 0
for from_first in range(max(len(fr_res) - 4, 0), len(fr_res)):
    ok_sum += fr_res[from_first]
    for other_nums in range(fr_res[from_first],
                            min((res[0] - ok_sum) // (len(fr_res) - from_first) + 2, fr_res[from_first] + ok_sum + 1)):
        last_ok = ok_sum + other_nums * (len(fr_res) - from_first - 1)
        if last_ok >= n and res[0] > ok_sum + other_nums * (len(fr_res) - from_first - 1):
            res = (ok_sum + other_nums * (len(fr_res) - from_first - 1), (len(fr_res) - from_first - 1), other_nums)
print(" ".join(map(str, fr_res[0:len(fr_res) - res[1]] + [res[2]] * res[1])))

# min_sum, min_arr = 1e9, []
# for a in range(1, 25):
#     for b in range(a, 25):
#         for c in range(b, 25):
#             for d in range(c, 25):
#                 for e in range(d, 25):
#                     ok = [False] * 30
#                     for i in range(0, 2 ** 5):
#                         pos = a * (i & 1) + b * ((i >> 1) & 1) + c * ((i >> 2) & 1) + d * ((i >> 3) & 1) + e * (
#                                 (i >> 4) & 1)
#                         if pos < len(ok):
#                             ok[pos] = True
#                     if False in ok:
#                         continue
#                     if a + b + c + d + e < min_sum:
#                         min_sum = a + b + c + d + e
#                         min_arr = [sorted([a, b, c, d, e])]
#                     elif a + b + c + d + e == min_sum:
#                         min_arr.append(sorted([a, b, c, d, e]))
# min_arr.sort()
# for ma in min_arr:
#     print(" ".join(map(str, ma)))
