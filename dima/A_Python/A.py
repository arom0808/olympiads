def main():
    f = open('truth_lie.txt', 'r')
    s = f.read()
    cts = {}
    for i in range(1, len(s)):
        if s[i - 1] != 'T':
            continue
        if s[i] in cts:
            cts[s[i]] = cts[s[i]] + 1
        else:
            cts[s[i]] = 1
    rrr = {}
    max_cnt = 0
    for key in cts:
        if cts[key] > max_cnt:
            max_cnt = cts[key]
        if cts[key] in rrr:
            rrr[cts[key]].append(key)
        else:
            rrr[cts[key]] = [key]
    print(sorted(rrr[max_cnt])[0])


main()
