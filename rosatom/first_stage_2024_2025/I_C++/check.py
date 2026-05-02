def main():
    i_f = open("input.txt", "r")
    n, k = map(int, i_f.readline().rstrip('\n').split())
    arr = [s.rstrip('\n') for s in i_f.readlines()]
    o_f = open("output.txt", "r")
    ans_str = o_f.readline().rstrip('\n')
    ans_seq = [int(v) - 1 for v in o_f.readline().rstrip('\n').split()]
    if len(ans_seq) != n - k + 1:
        print("-1a")
        return
    res_str = [arr[i][k - 1] for i in ans_seq]
    res_str = arr[ans_seq[0]][0:k - 1] + ''.join(res_str)
    if ans_str != res_str:
        print("-1b")
        return
    sset = set(ans_seq)
    if len(sset) != len(ans_seq):
        print("-1c")
        return
    print("0")


main()
