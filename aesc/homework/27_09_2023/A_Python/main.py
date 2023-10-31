def max_digit(pre_num, result):
    pre_num *= 10
    for digit in range(10):
        if (pre_num + digit) * digit > result:
            return digit - 1
    return 9


def get_sqrt(num):
    parts = []
    while num != 0:
        parts.append(num % 100)
        num //= 100
    ln, dif, res = 0, 0, 0
    for part in reversed(parts):
        dif = dif * 100 + part
        fd = max_digit(ln, dif)
        dif -= (ln * 10 + fd) * fd
        ln = ln * 10 + fd * 2
        res = res * 10 + fd
    return res


def main():
    num = int(input())
    sq = get_sqrt(num)
    print(sq if sq * sq == num else -1)


main()
