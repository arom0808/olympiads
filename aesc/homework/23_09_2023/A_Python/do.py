def power_mod(x, N, P):
    result = 1
    x = x % P  # Переводим x в остаток от деления на P

    while N > 0:
        # Если N нечетное, умножаем result на x и берем остаток от деления на P
        if N % 2 == 1:
            result = (result * x) % P

        # Возводим x в квадрат и берем остаток от деления на P
        x = (x * x) % P

        # Делим N на 2 (округленное в меньшую сторону)
        N = N // 2

    return result


fi = open('in.txt', 'r')
fo = open('out.txt', 'w')
for line in fi.readlines():
    [x, n, p] = [int(i) for i in line.split(' ')]
    fo.write(str(power_mod(x, n, p)))
    fo.write('\n')

fi.close()
fo.close()
