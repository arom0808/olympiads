import random


def reverse_endian(num):
    ss = 2 ** 64 - 1
    res = 0
    for i in range(8):
        res |= (((num >> (i * 8)) << 56) & ss) >> (i * 8)
    return res


def main():
    a = open("C:\\Users\\banan\\projects\\olympiads\\rucode_final_2023_AB\\K_C++\\cmake-build-debug\\out.txt", "r")
    b = open("C:\\Users\\banan\\projects\\olympiads\\rucode_final_2023_AB\\K_C++\\cmake-build-debug\\in.txt", "r")
    t = b.read()
    b.close()
    b = open("C:\\Users\\banan\\projects\\olympiads\\rucode_final_2023_AB\\K_C++\\cmake-build-debug\\in.txt", "w")
    b.write("decode\n")
    b.write(a.readline())
    nums = [int(i) for i in a.readline().rstrip('\n').rstrip(' ').split(' ')]
    for i in range(len(nums)):
        if random.randint(0, 1) == 1:
            nums[i] = reverse_endian(nums[i])
    b.write(' '.join(map(str, nums)))
    b.write("\n\n")
    b.write(t)
    a.close()
    b.close()


main()
