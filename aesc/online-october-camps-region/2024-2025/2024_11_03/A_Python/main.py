from sys import setrecursionlimit, stdout

a, b, v, l, r, h = 0, 0, 0, 0, 0, 0


def print_h_tree():
    global h
    if h == 0:
        return
    h -= 1
    print_h_tree()
    h += 1
    stdout.write(str(h))
    stdout.write(' ')
    h -= 1
    print_h_tree()
    h += 1


def rec_down():
    global a, b, l, r, v, h
    if a > r or l > b:
        return
    if a <= l and r <= b:
        print_h_tree()
        return
    if a < v:
        # h = h - 1
        # l = l
        r = v - 1
        v = (v + l - 1) >> 1
        h -= 1
        rec_down()
        h += 1
        v = r + 1
        r = (v << 1) - l
        # h = h + 1
    if a <= v <= b:
        stdout.write(str(h))
        stdout.write(' ')
    if b > v:
        l = v + 1
        v = (v + r + 1) >> 1
        h -= 1
        rec_down()
        h += 1
        v = l - 1
        l = (v << 1) - r
        # dv = v
        # v = (r - v + 1) >> 1
        # a -= dv
        # b -= dv
        # l = 1
        # r -= dv
        # h -= 1
        # dv -= v
        # rec_down()
        # h += 1
        # v += dv
        # r += v
        # l = (v << 1) - r
        # a += v
        # b += v


#

def main():
    global a, b, l, r, v, h
    n = int(input())
    a = int(input())
    b = int(input())
    setrecursionlimit(300000)
    v = 2 ** (n - 1)
    l = 1
    r = (v << 1) - 1
    h = n
    rec_down()


main()
