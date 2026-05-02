ss = [chr(i) for i in range(ord('a'), ord('a') + 26)]

ans = 0
for a in ss:
    for b in ss:
        for c in ss:
            for d in ss:
                for e in ss:
                    cs = a + b + c + d + e
                    p1 = cs.find('m')
                    if p1 == -1:
                        continue
                    p2 = cs.find('t', p1)
                    if p2 == -1:
                        continue
                    p3 = cs.find('s', p2)
                    if p3 == -1:
                        continue
                    ans += 1
print(ans)

# from math import lcm
#
#
# def cnt(a, b, c, n):
#     return max(0, n // lcm(a, b) - n // lcm(a, b, c))
#


# # import turtle as t
#
# rots = []
#
#
# # def turn(gr):
# #     t.right(gr)
# #
# #
# # def go(l):
# #     t.forward(l * 10)
#
#
# def rec_sol(level):
#     global rots
#     if level == 0:
#         go(5)
#         return
#     rec_sol(level - 1)
#     for r in rots:
#         turn(r)
#         rec_sol(level - 1)
#
#
# def main():
#     global rots
#     s = "-120-240-240-120-"
#     rots = list(map(int, s.split('-')[1:-1]))
#     rec_sol(int(input()))
#
#
# # t.left(90)
# main()
# # t.mainloop()
#
# # def snow_koch(level):
# #     rec_sol(level)
# #     turn(-120)
# #     rec_sol(level)
# #     turn(-120)
# #     rec_sol(level)
#
#
# # snow_koch(int(input()))
