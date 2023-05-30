# print(sum([int(s) % 2 == 0 for s in input()]))
# n = int(input())
# a = [1 / (i * (i + 3)) for i in range(1, n + 1)]
# b = str(round(sum(a), 3))
# print(b + ('0' * (3 - len(b.split('.')[1]))))

# print(*sum([k.split(')') for k in input().split('(')], [])[1::2])

# nums = [int(s) for s in input().split(' ')]
# first, last = -1, -1
# for i in range(len(nums)):
#     if abs(nums[i]) % 2 == 0:
#         if abs(nums[i] / 2) % 2 == 1:
#             if first == -1:
#                 first = i
#             elif last == -1:
#                 last = i
#                 break
#
# if first == -1 or last == -1:
#     print(0)
# else:
#     n_s = sum(nums[first + 1:last])
#     for i in range(1, len(nums), 2):
#         nums[i] = n_s
#     print(' '.join([str(s) for s in nums]))

def get_sum_o_f(c_i, o, f, c_N, matr):
    cur_res = 0
    if o > 0:
        for c_j in range(0, o):
            cur_res += matr[c_i][c_j]
    if f < c_N - 1:
        for c_j in range(f + 1, c_N):
            cur_res += matr[c_i][c_j]
    return cur_res


N = int(input())
matrix = [[int(s) for s in input().split(' ')] for _ in range(N)]
[p, k] = [int(s) for s in input().split(' ')]

res = 0
for i in range(0, p):
    res += get_sum_o_f(i, k - (p - i), k + (p - i), N, matrix)
for j in range(N):
    if j != k:
        res += matrix[p][j]
for i in range(p + 1, N):
    res += get_sum_o_f(i, k - (i - p), k + (i - p), N, matrix)
print(res)
