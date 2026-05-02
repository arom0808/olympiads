ff = open("cnk.txt", "w")


def fact(x):
    if x <= 1:
        return 1
    return x * fact(x - 1)


def cnk(n, k):
    return fact(n) // fact(k) // fact(n - k)


mod = 1000000007

for n in range(0, 351):
    for k in range(0, n + 1):
        ff.write(f"cnk[{n}][{k}]=")
        ff.write(str(cnk(n, k) % mod))
        ff.write(";\n")

ff.close()
