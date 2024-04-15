def f1(x1, x2, x3, x4):
    return (not x1) and x2 and x3


def f2(x1, x2, x3, x4):
    return x1 and (not x2) and (not x3)


def f3(x1, x2, x3, x4):
    return (not x1) and x2 and x4


def f4(x1, x2, x3, x4):
    return x1 and (not x2) and x4


def f5(x1, x2, x3, x4):
    return (not x1) and (not x3) and (not x4)


def f6(x1, x2, x3, x4):
    return (not x1) and x3 and x4


def f7(x1, x2, x3, x4):
    return x1 and (not x3) and x4


def f8(x1, x2, x3, x4):
    return (not x2) and (not x3) and (not x4)


def f9(x1, x2, x3, x4):
    return (not x2) and x3 and x4


def f10(x1, x2, x3, x4):
    return x2 and (not x3) and x4


def check_func(f):
    for b1 in [False, True]:
        for b2 in [False, True]:
            for b3 in [False, True]:
                for b4 in [False, True]:
                    v = f(b1, b2, b3, b4)
                    r = True
                    if ((not b1) and (not b2) and (not b3) and b4) or ((not b1) and (not b2) and b3 and (not b4)) or (
                            (not b1) and b2 and b3 and (not b4)) or (b1 and (not b2) and b3 and (not b4)) or (
                            b1 and b2 and (not b3) and (not b4)) or (b1 and b2 and b3):
                        r = False
                    if v != r:
                        return False
    return True


f_strs = ['(!x1 & x2 & x3)  ', '(x1 & !x2 & !x3) ', '(!x1 & x2 & x4)  ', '(x1 & !x2 & x4)  ', '(!x1 & !x3 & !x4)',
          '(!x1 & x3 & x4)  ', '(x1 & !x3 & x4)  ', '(!x2 & !x3 & !x4)', '(!x2 & x3 & x4)  ', '(x2 & !x3 & x4)  ']


def var_to_str(var):
    strs = []
    for i in range(10):
        if var[i]:
            strs.append(f_strs[i])
    return ' | '.join(strs)


def main():
    min_len = 100
    min_cnt = 0
    min_vars = []
    for a1 in [False, True]:
        for a2 in [False, True]:
            for a3 in [False, True]:
                for a4 in [False, True]:
                    for a5 in [False, True]:
                        for a6 in [False, True]:
                            for a7 in [False, True]:
                                for a8 in [False, True]:
                                    for a9 in [False, True]:
                                        for a10 in [False, True]:
                                            if not (a1 or a2 or a3 or a4 or a5 or a6 or a7 or a8 or a9 or a10):
                                                continue
                                            l = int(a1) + int(a2) + int(a3) + int(a4) + int(a5) + int(a6) + int(
                                                a7) + int(a8) + int(a9) + int(a10)
                                            if l > min_len:
                                                continue
                                            f = lambda x1, x2, x3, x4: (f1(x1, x2, x3, x4) if a1 else False) or (
                                                f2(x1, x2, x3, x4) if a2 else False) or (
                                                                           f3(x1, x2, x3, x4) if a3 else False) or (
                                                                           f4(x1, x2, x3, x4) if a4 else False) or (
                                                                           f5(x1, x2, x3, x4) if a5 else False) or (
                                                                           f6(x1, x2, x3, x4) if a6 else False) or (
                                                                           f7(x1, x2, x3, x4) if a7 else False) or (
                                                                           f8(x1, x2, x3, x4) if a8 else False) or (
                                                                           f9(x1, x2, x3, x4) if a9 else False) or (
                                                                           f10(x1, x2, x3, x4) if a10 else False)
                                            if check_func(f):
                                                if l < min_len:
                                                    min_len = l
                                                    min_cnt = 1
                                                    min_vars = [[a1, a2, a3, a4, a5, a6, a7, a8, a9, a10]]
                                                elif l == min_len:
                                                    min_cnt += 1
                                                    min_vars.append([a1, a2, a3, a4, a5, a6, a7, a8, a9, a10])
    print(min_len * 3, min_cnt)
    for var in min_vars:
        print(var_to_str(var))


main()
