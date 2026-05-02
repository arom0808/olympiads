n = int(input())
nums = list(map(int, input().split()))
res = []


def find_pos(num):
    for i in range(n):
        if nums[i] == num:
            return i


def pre_pos(pos):
    return n - 1 if pos == 0 else pos - 1


def can_shift_left(pos):
    return abs(nums[pre_pos(pos)] - nums[pos]) > 1


def main():
    for now_min_num in range(n, 1, -1):
        for now_shift_num in range(now_min_num, n + 1):
            pos = find_pos(now_shift_num)
            while can_shift_left(pos):
                res.append((nums[pre_pos(pos)], nums[pos]))
                nums[pre_pos(pos)], nums[pos] = nums[pos], nums[pre_pos(pos)]
                pos = pre_pos(pos)
    ok = True
    for i in range(n):
        if (nums[i] - nums[pre_pos(i)]) % n != 1:
            ok = False
    if ok and len(res) < 50000:
        for pairs in res:
            print(pairs[0], pairs[1])
        print(0)
    else:
        print(-1)


main()
