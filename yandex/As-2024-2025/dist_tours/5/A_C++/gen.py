from random import randint

o1, o2 = True, True
c1, c2 = 0, 0


def make_act(act):
    global o1, o2, c1, c2
    if act == 0:
        if not o1:
            act += 1
        else:
            print("a", end='')
            c1 += 1
            return True
    if act == 1:
        if not o2:
            act += 1
        else:
            print("b", end='')
            c2 += 1
            return True
    if act == 2:
        if (not o1) or c1 == 0:
            act += 1
        else:
            print("A", end='')
            c1 -= 1
            return True
    if act == 3:
        if (not o2) or c2 == 0:
            act += 1
        else:
            print("B", end='')
            c2 -= 1
            return True
    if act == 4:
        if (not o1) or ((not o2) and c1 != 0):
            act += 1
        else:
            print(">", end='')
            c2 += c1
            c1 = 0
            o1 = False
            return True
    if act == 5:
        if (not o2) or ((not o1) and c2 != 0):
            act += 1
        else:
            print("]", end='')
            c1 += c2
            c2 = 0
            o2 = False
            return True
    if act == 6:
        if o1:
            act += 1
        else:
            print("<", end='')
            c1 = c2 // 2
            c2 -= c1
            o1 = True
            return True
    if act == 7:
        if o2:
            act += 1
        else:
            print("[", end='')
            c2 = c1 // 2
            c1 -= c2
            o2 = True
            return True
    return False


def main():
    # rnm = {'a': 0, 'b': 1, 'A': 2, 'B': 3, '>': 4, ']': 5, '<': 6, '[': 7}
    # ss = "a>B<>]<aaA[a][AB>]<[><"
    # for c in ss:
    #     print()
    #     print(o1, o2)
    #     print(c1, c2)
    #     make_act(rnm[c])
    n = randint(20, 30)
    print(n)
    for i in range(n):
        act = randint(0, 7)
        if not make_act(act):
            make_act(0)
    print()


main()
