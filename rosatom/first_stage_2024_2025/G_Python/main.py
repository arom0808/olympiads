from sys import stdin

maxn, inf = int(3e5) + 1, int(2e9)
N = 1 << 19


class ST:
    def __init__(self):
        self.tree = [inf] * (N * 2)

    def init(self, arr):
        for i in range(len(arr)):
            self.tree[N + i] = arr[i][1]
        for i in range(N - 1, 0, -1):
            self.tree[i] = min(self.tree[i << 1], self.tree[(i << 1) | 1])

    def min_val(self, l, r):
        l += N
        r += N
        ans = inf
        while l < r:
            if l & 1:
                ans = min(ans, self.tree[l])
                l += 1
            if r & 1:
                r -= 1
                ans = min(ans, self.tree[r])
            l >>= 1
            r >>= 1
        return ans


n = 0
asp, bsp, csp = [], [], []
all_colors = []
a_st_col_pos, b_st_col_pos, c_st_col_pos = [], [], []
ast, bst, cst = ST(), ST(), ST()


def min_price(cur_st_col_pos, cur_st, col_id, max_col_id):
    return cur_st.min_val(cur_st_col_pos[col_id], cur_st_col_pos[max_col_id + 1])


def min_full_price(pos, max_color_id):
    if all_colors[max_color_id] < all_colors[asp[pos][0]]:
        return inf
    return (asp[pos][1] + min_price(b_st_col_pos, bst, asp[pos][0], max_color_id) +
            min_price(c_st_col_pos, cst, asp[pos][0], max_color_id))


def get_ans(x):
    d = int(1e9)
    max_col_id = len(all_colors)
    for i in range(n):
        while max_col_id < len(all_colors) and all_colors[max_col_id] < all_colors[asp[i][0]] + d:
            max_col_id += 1
        while True:
            max_col_id -= 1
            if max_col_id < 0 or min_full_price(i, max_col_id) > x:
                break
        max_col_id += 1
        if max_col_id < len(all_colors):
            d = min(d, all_colors[max_col_id] - all_colors[asp[i][0]])
    return d


def get_zipped(fzn, val):
    l, r = -1, len(fzn) - 1
    while r - l != 1:
        mid = (l + r) >> 1
        if fzn[mid] < val:
            l = mid
        else:
            r = mid
    return r


def init_st_col_pos(cur_cs, cur_st_col_pos):
    next_col = 0
    for i in range(n):
        if cur_cs[i][0] >= next_col:
            while next_col <= cur_cs[i][0]:
                cur_st_col_pos[next_col] = i
                next_col += 1
    while next_col <= len(all_colors):
        cur_st_col_pos[next_col] = n
        next_col += 1


def input_arr():
    global all_colors
    cur_min_price = inf
    cur_sp = list(zip(map(int, stdin.readline().rstrip('\n').split()), map(int, stdin.readline().rstrip('\n').split())))
    for el in cur_sp:
        cur_min_price = min(cur_min_price, el[1])
        all_colors.add(el[0])
    return cur_sp, cur_min_price


def solve():
    global n, asp, bsp, csp, all_colors, a_st_col_pos, b_st_col_pos, c_st_col_pos, ast, bst, cst
    n, x = map(int, stdin.readline().rstrip('\n').split())
    all_colors = set()
    asp, a_min_price = input_arr()
    bsp, b_min_price = input_arr()
    csp, c_min_price = input_arr()
    if a_min_price + b_min_price + c_min_price > x:
        print(-1)
        return
    all_colors = list(all_colors)
    all_colors.sort()
    asp.sort()
    bsp.sort()
    csp.sort()
    for i in range(n):
        asp[i] = (get_zipped(all_colors, asp[i][0]), asp[i][1])
        bsp[i] = (get_zipped(all_colors, bsp[i][0]), bsp[i][1])
        csp[i] = (get_zipped(all_colors, csp[i][0]), csp[i][1])
    a_st_col_pos, b_st_col_pos, c_st_col_pos = ([0] * (len(all_colors) + 1),
                                                [0] * (len(all_colors) + 1),
                                                [0] * (len(all_colors) + 1))
    init_st_col_pos(asp, a_st_col_pos)
    init_st_col_pos(bsp, b_st_col_pos)
    init_st_col_pos(csp, c_st_col_pos)
    ast.init(asp)
    bst.init(bsp)
    cst.init(csp)
    bans = inf
    for i in range(3):
        bans = min(bans, get_ans(x))
        asp, bsp, csp = bsp, csp, asp
        a_st_col_pos, b_st_col_pos, c_st_col_pos = b_st_col_pos, c_st_col_pos, a_st_col_pos
        ast, bst, cst = bst, cst, ast
    print(bans)


solve()

