def dig(c):
    if '0' <= c <= '9':
        return ord(c) - ord('0')
    return ord(c) - ord('A') + 10


def translate_int_from_p(p_int, p):
    res, p_pow = 0, 1
    for c in reversed(p_int):
        res += dig(c) * p_pow
        p_pow *= p
    return res


def translate_fract_part_from_p(p_fract_part, p):
    res, p_pow = 0, 1 / p
    for c in p_fract_part:
        res += dig(c) * p_pow
        p_pow /= p
    return res


def translate_from_p(p_num: str, p):
    if any(map(lambda c: (c not in '.-') and (not (0 <= dig(c) < p)), p_num)):
        return 'WRONG INPUT'
    sign = (-1 if p_num[0] == '-' else 1)
    p_num = p_num.strip('-').split('.')
    return "{:.8f}".format(sign * (
            translate_int_from_p(p_num[0], p) + (translate_fract_part_from_p(p_num[1], p) if len(p_num) > 1 else 0)))


def main():
    p_num, p = input(), int(input())
    dec_num = translate_from_p(p_num, p)
    if ' ' in dec_num:
        print(dec_num)
    else:
        print("{s1}({p})={s2}(10)".format(s1=p_num, p=p, s2=dec_num))


main()
