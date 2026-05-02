from random import randint

t, n, p, k, a = 0, 0, 0, 0, 0
p_id = 0
field: [[int]] = []
ncx, ncy, ncs = -1, -1, -1


def gen_nc():
    global ncs, ncx, ncy
    ncs = randint(1, max(min(10, (n - 1) // 2), 1))
    ncx = randint(ncs - n - 1, n - ncs + 1)
    ncy = randint(ncs - n - 1, n - ncs + 1)


def try_make_move():
    global ncs, ncx, ncy
    for x in range(ncx, ncx + ncs):
        y = -x + ncx + ncy + ncs - 1
        if field[x + a][y + a] == 0:
            return x, y
        y = x + ncy - ncx - ncs + 1
        if field[x + a][y + a] == 0:
            return x, y
    for x in range(ncx - ncs + 1, ncx):
        y = x + ncy - ncx + ncs - 1
        if field[x + a][y + a] == 0:
            return x, y
        y = -x + ncx + ncy - ncx + 1
        if field[x + a][y + a] == 0:
            return x, y
    ncs = -1


def make_move():
    global ncs, ncx, ncy
    if ncs == -1:
        gen_nc()
    x, y = try_make_move()
    while ncs == -1:
        gen_nc()
        x, y = try_make_move()
    return x, y


def main():
    global t, n, p, k, a, p_id, field
    t, n, p, k, a = map(int, input().split())
    p_id = int(input())
    field = [[-1 for j in range(a * 2 + 1)] for i in range(a * 2 + 1)]
    for i in range(2 * n + 1):
        for j, val in enumerate(map(int, input().split())):
            field[i - n + a][j - n + a] = val
    while True:
        num, x, y = map(int, input().split())
        if num == -1 and x == -1 and y == -1:
            n += 1
            for i in range(-n, n + 1):
                field[a - n][a + i] = field[a + n][a + i] = field[a + i][a - n] = field[a + i][a + n] = 0
            num, x, y = map(int, input().split())
            while num != -1:
                field[x + a][y + a] = -1
                num, x, y = map(int, input().split())
        elif num == -2 and x == -2 and y == -2:
            mx, my = make_move()
            print(mx, my)
        elif num == -3 and x == -3 and y == -3:
            return
        else:
            field[x + a][y + a] = num


# main()
a = [list(map(int, input().split())) for i in range(27)]
print(a[13 + 2][13 - 3])
