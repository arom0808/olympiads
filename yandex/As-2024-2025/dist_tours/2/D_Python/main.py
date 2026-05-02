from sys import stdin, stdout
from typing import Optional


class Node:
    max_val: int
    max_pos: int
    change: int

    def __init__(self, mv=0, mp=0, c=0):
        self.max_val, self.max_pos, self.change = mv, mp, c


class ST:
    tree: [Optional[Node]]
    size: int

    def upd_from_child(self, v, l, r):
        if r - l <= 1:
            return
        if self.tree[v * 2].max_val > self.tree[v * 2 + 1].max_val:
            self.tree[v].max_val, self.tree[v].max_pos = self.tree[v * 2].max_val, self.tree[v * 2].max_pos
        else:
            self.tree[v].max_val, self.tree[v].max_pos = self.tree[v * 2 + 1].max_val, self.tree[v * 2 + 1].max_pos

    def _build(self, v, l, r, arr):
        if r - l == 1:
            self.tree[v] = Node(arr[l], l, 0)
            return
        mid = (l + r) // 2
        self._build(v * 2, l, mid, arr)
        self._build(v * 2 + 1, mid, r, arr)
        self.tree[v] = Node()
        self.upd_from_child(v, l, r)

    def __init__(self, arr: [int]):
        self.size = len(arr)
        self.tree = [None for _ in range(self.size * 4)]
        self._build(1, 0, self.size, arr)

    def push(self, v, l, r):
        if self.tree[v].change == 0:
            return
        if r - l > 1:
            self.tree[v * 2].max_val += self.tree[v].change
            self.tree[v * 2 + 1].max_val += self.tree[v].change
            self.tree[v * 2].change += self.tree[v].change
            self.tree[v * 2 + 1].change += self.tree[v].change
        self.tree[v].change = 0

    def _add(self, v, l, r, a, b, val):
        if l >= b or a >= r:
            return
        if a <= l and r <= b:
            self.tree[v].max_val += val
            self.tree[v].change += val
            return
        self.push(v, l, r)
        mid = (l + r) // 2
        self._add(v * 2, l, mid, a, b, val)
        self._add(v * 2 + 1, mid, r, a, b, val)
        self.upd_from_child(v, l, r)

    def _max_v_p(self, v, l, r, a, b):
        if a <= l and r <= b:
            return self.tree[v].max_val, self.tree[v].max_pos
        mid = (l + r) // 2
        if b <= mid:
            return self._max_v_p(v * 2, l, mid, a, b)
        if a >= mid:
            return self._max_v_p(v * 2 + 1, mid, r, a, b)
        return max(self._max_v_p(v * 2, l, mid, a, b), self._max_v_p(v * 2 + 1, mid, r, a, b))

    def add(self, a, b, val):
        self._add(1, 0, self.size, a, b, val)

    def max_v_p(self, a, b):
        return self._max_v_p(1, 0, self.size, a, b)[1]


def main():
    n = int(stdin.readline().rstrip('\n'))
    da1ps = list(map(int, stdin.readline().rstrip('\n').split(' ')))
    da1 = da1ps[:]
    da2 = da1[:]
    for i in range(n - 1, 0, -1):
        da1[i] -= da1[i - 1]
        da2[i] -= da2[i - 1] * 2
    st = ST(da2)
    p = [0] * n
    for pi in range(n, 0, -1):
        mp = st.max_v_p(0, n)
        p[mp] = pi
        st.add(mp + 1, n, da1[mp])
        st.add(mp, mp + 1, -da1ps[mp])
    stdout.write(" ".join(map(str, p)))
    stdout.write("\n")


main()
