digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def translate_to_system(dec_num, P):
    p_num = []
    while True:
        p_num.append(digits[dec_num % P])
        dec_num //= P
        if not dec_num:
            break
    return "".join(reversed(p_num))


def main():
    p, dec_num = int(input()), int(input())
    print("{dec_num}(10)={p_num}({p})".format(dec_num=dec_num, p=p, p_num=translate_to_system(dec_num, p)))


main()
