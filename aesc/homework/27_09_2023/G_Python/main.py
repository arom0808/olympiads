def factorize(sier, prime, cb, num):
    i = 0
    while i * i <= num and num >= len(sier):
        if i >= len(prime):
            return
        if prime[i] == 0:
            return
        if prime[i] == 1:
            return
        if num % prime[i] == 0:
            cb(prime[i])
            num //= prime[i]
        else:
            i += 1
    while num != 1:
        if num >= len(sier):
            return
        if sier[num] == 0:
            return
        cb(sier[num])
        num //= sier[num]


def b_add(b_divs, num):
    if num in b_divs:
        b_divs[num] += 1
    else:
        b_divs[num] = 1


def h_add(b_divs, h_divs, num):
    if num in b_divs:
        if num in h_divs:
            h_divs[num] += 1
        else:
            h_divs[num] = 1


def main():
    sier, prime = [0] * int(1e6), []
    for i in range(2, len(sier)):
        if sier[i] == 0:
            sier[i] = i
            prime.append(i)
        for pr_num in prime:
            if pr_num > sier[i] or i * pr_num >= len(sier):
                break
            sier[i * pr_num] = pr_num
    n, b = map(int, input().split())
    b_divs, h_divs = {}, {}
    factorize(sier, prime, lambda pr_num: b_add(b_divs, pr_num), b)
    nums = map(int, input().split())
    for num in nums:
        factorize(sier, prime, lambda pr_num: h_add(b_divs, h_divs, pr_num), num)
    res = int(1e9)
    for b_div in b_divs.items():
        if b_div[0] in h_divs:
            res = min(res, h_divs[b_div[0]] // b_div[1])
        else:
            res = 0
    print(res)


main()
