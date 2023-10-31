from math import ceil


def translate_from_p_to_dec(p_num, p):
    res, p_pow = 0, 1
    while p_num != 0:
        res += (p_num % 10) * p_pow
        p_num //= 10
        p_pow *= p
    return res


def get_min_p(dec_num, rev_dec_num):
    l, r = 2, dec_num
    dnl = len(str(dec_num))
    while l < r:
        m = ceil((l + r) / 2)
        nl = len(str(translate_from_p_to_dec(rev_dec_num, m)))
        if nl > dnl:
            r = m - 1
        elif nl < dnl:
            l = m + 1
        else:
            r = m - 1
    return l


def get_max_p(dec_num, rev_dec_num):
    l, r = 2, dec_num
    dnl = len(str(dec_num))
    while l < r:
        m = (l + r) // 2
        nl = len(str(translate_from_p_to_dec(rev_dec_num, m)))
        if nl > dnl:
            r = m - 1
        elif nl < dnl:
            l = m + 1
        else:
            l = m + 1
    return l


def main():
    dec_num = int(input())
    rev_dec_num = int(str(dec_num)[::-1])
    min_p, max_p = get_min_p(dec_num, rev_dec_num), get_max_p(dec_num, rev_dec_num)
    for p in range(min_p, max_p + 1):
        if translate_from_p_to_dec(rev_dec_num, p) == dec_num:
            print(p)


main()
