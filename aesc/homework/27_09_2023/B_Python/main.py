def is_prime_div_of_num(num, pr_div, mpd):
    while num != 1:
        if mpd[num] == pr_div:
            return True
        num //= mpd[num]
    return False


def main():
    n = int(input())
    nums = list(map(int, input().split()))
    mpd, prime = [0] * (max(nums) + 1), []
    for i in range(2, len(mpd)):
        if mpd[i] == 0:
            mpd[i] = i
            prime.append(i)
        for pr_num in prime:
            if pr_num > mpd[i] or i * pr_num >= len(mpd):
                break
            mpd[i * pr_num] = pr_num
    max_len = 0
    for pr_num in prime:
        cur_len = 0
        for num in nums:
            if is_prime_div_of_num(num, pr_num, mpd):
                cur_len += 1
            else:
                cur_len = 0
            if cur_len > max_len:
                max_len = cur_len
    print(max_len)


main()
