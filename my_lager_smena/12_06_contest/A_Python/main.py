a = [0, 1, 3, 6, 10, 15, 21, 28, 36]
q = int(input())
for i in range(q):
    l, r = map(int, input().split(' '))
    full_r = r // 9 * 45 + a[r % 9]
    full_l = (l - 1) // 9 * 45 + a[(l - 1) % 9]
    print(full_r - full_l)
