from math import log2

s = "всех скороговорок не перескороговоришь, не перевыскороговоришь"

alphabet = {}

for c in s:
    if c not in alphabet:
        alphabet[c] = 0
    alphabet[c] += 1

print("Алфавит:", alphabet)

print("Кол-во информации при равномерном кодировании:", log2(len(alphabet)) * len(s), "бит")

probs = {}

for c in alphabet:
    probs[c] = alphabet[c] / len(s)

inf_cnt = 0

for c in alphabet:
    inf_cnt -= probs[c] * log2(probs[c])

inf_cnt *= len(s)

print("Кол-во информации при кодировании Шеннона:", inf_cnt, "бит")

# # def main():
# #     n, x = int(input()), int(input())
# #     a, b = 10 ** n - 1, 10 ** (n - 1) - 1
# #     x = 2 ** x
# #     print(a // x - b // x)
#
#
# def a(n, x):
#     u, v = 10 ** n - 1, 10 ** (n - 1) - 1
#     return u // (1 << x) - v // (1 << x) + (1 if n==1 else 0)
#
#
# def b(n, x):
#     rr = 0
#     for i in range(10 ** (n - 1), 10 ** n):
#         if i % (1 << x) == 0:
#             rr += 1
#     if n == 1:
#         rr += 1
#     return rr
#
#
# print(a(int(input()), int(input())))
#
# # def tt():
# #     for n in range(1, 19):
# #         print(a(n, 1))
# #         # print(b(n, 1))
# #         # if b(n, 1) != a(n, 1):
# #         #     print(n)
# #         #     print(a(n, 1))
# #         #     print(b(n, 1))
# #         #     break
# #
# #
# # tt()
