def translate_int_to_bin(dec_num):
    dec_num, p_num = int(dec_num), []
    while True:
        p_num.append(dec_num % 2)
        dec_num //= 2
        if not dec_num:
            break
    return ''.join(map(str, reversed(p_num)))


def translate_fract_part_to_bin(dec_fract_part):
    num, d_pow, res = int(dec_fract_part), 10 ** len(dec_fract_part), []
    while True:
        num *= 2
        res.append(str(num // d_pow))
        num %= d_pow
        if num == 0:
            break
        if len(res) == 20:
            res.append('...')
            break
    return ''.join(res)


def main():
    dec_num = input()
    sign = '-' if dec_num[0] == '-' else ''
    dec_num = dec_num.strip('-').split('.')
    print('=', sign, translate_int_to_bin(dec_num[0]),
          ('.' + translate_fract_part_to_bin(dec_num[1]) if len(dec_num) > 1 else ''), '(2)', sep='')


main()
