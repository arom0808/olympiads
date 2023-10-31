def get_n(a):
    p, res = 2, 1
    start_pow, new_pow = [0] * 200001, [0] * 200001
    while p * p <= a:
        if a % p == 0:
            res *= p
            new_pow[p] += 1
        while a % p == 0:
            start_pow[p] += 1
            a //= p
        p += 1

    res *= a

    for i in range(2, 100001):
        while new_pow[i] * res < start_pow[i]:
            res *= i
            new_pow[i] += 1
    return res


print(get_n(int(input())))
