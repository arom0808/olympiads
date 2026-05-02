def main():
    a, b = map(int, input().split())
    cnts = []
    i = 2
    while i * i <= a:
        if a % i == 0:
            cnts.append(1)
            a //= i
            while a % i == 0:
                cnts[-1] += 1
                a //= i
        i += 1
    if a > 1:
        cnts.append(1)
    cnt = 1
    for fc in cnts:
        cnt *= fc * b + 1
    if cnt % 2 == 0:
        print(b * (cnt // 2) % 998244353)
    else:
        print((b * (cnt // 2) + (b // 2)) % 998244353)


main()
