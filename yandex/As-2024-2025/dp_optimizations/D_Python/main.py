s = "лена ела еле-еле лена ела так от лени"
cc = {}
for c in s:
    if c in cc:
        cc[c] += 1
    else:
        cc[c] = 1

aa = sorted([(c, cc[c]) for c in cc], key=lambda x: x[1])
print(aa)
for i, rr in enumerate(aa):
    print('\'' + rr[0] + "\'" + " - " + str(i))
aa = [(i, rr[1]) for i, rr in enumerate(aa)]
nfi = len(aa)
while len(aa) > 1:
    el1, el2 = aa[0], aa[1]
    aa = [(nfi, el1[1] + el2[1])] + aa[2:]
    aa = sorted(aa, key=lambda x: x[1])
    print(nfi, "->", el1[0], el2[0])
    nfi += 1

# maxn, maxk = 10 ** 5 + 1, 21
# inf = 10 ** 18
# arr = []
# dp = [[0] * maxn for _ in range(maxk)]
# opt = [[0] * maxn for _ in range(maxk)]
#
#
# def ans_by_cnt(cnt):
#     if cnt < 2:
#         return 0
#     return cnt * (cnt - 1) // 2
#
#
# class SMS:
#     l, r = 0, 0
#     cans = 0
#     cnts = [0] * maxn
#
#     def add_el(self, i):
#         self.cans -= ans_by_cnt(self.cnts[arr[i]])
#         self.cnts[arr[i]] += 1
#         self.cans += ans_by_cnt(self.cnts[arr[i]])
#
#     def del_el(self, i):
#         self.cans -= ans_by_cnt(self.cnts[arr[i]])
#         self.cnts[arr[i]] -= 1
#         self.cans += ans_by_cnt(self.cnts[arr[i]])
#
#     def shift_to(self, nl, nr):
#         while self.l > nl:
#             self.l -= 1
#             self.add_el(self.l)
#         while self.r < nr:
#             self.add_el(self.r)
#             self.r += 1
#         while self.l < nl:
#             self.del_el(self.l)
#             self.l += 1
#         while self.r > nr:
#             self.r -= 1
#             self.del_el(self.r)
#
#
# def main():
#     n, k = map(int, input().split())
#     arr = list(map(int, input.split()))
